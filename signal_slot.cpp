#include <bits/stdc++.h>
using namespace std;

template<
    typename Signature
>
class Slot
{
public:
    using Slot_function = function<Signature>;
    
    Slot() {}
    
    Slot(const Slot_function& f):
        slot_func_(f)
    {}
    
    Slot(const Slot& other) = default;
    Slot& operator=(const Slot& other) = default;
    Slot(Slot&& other) = default;
    Slot& operator=(Slot&& other) = default;
    
    Slot_function slot_func() const
    {
        return slot_func_;
    }
    
    template<typename... Args>
    auto operator()(Args... args)
    {
        return slot_func_(args...);
    }
    
    Slot& track(weak_ptr<void> tracked)
    {
        tracked_objects_.push_back(tracked);
        return *this;
    }
    
    bool expired() const
    {
        for (auto& t: tracked_objects_) {
            if (t.expired())
                return true;
        }
        return false;
    }
    
private:
    Slot_function slot_func_;
    vector<weak_ptr<void>> tracked_objects_;
};

template<
    typename Slot_signature
>
class Connection_body
{
public:
    using Slot_type = Slot<Slot_signature>;
    using Weak = weak_ptr<Connection_body<Slot_signature>>;
    using Shared = shared_ptr<Connection_body<Slot_signature>>;
    
    Connection_body()
    {}
    
    Connection_body(const Slot_type& slot):
        slot_(slot), connected_(true)
    {}
    
    Connection_body(const Connection_body& other) = default;
    Connection_body& operator=(const Connection_body& other) = default;
    Connection_body(Connection_body&& other) = default;
    Connection_body& operator=(Connection_body&& other) = default;
    
    void disconnect()
    {
        if (connected_)
            connected_ = false;
    }
    
    bool expired() const
    {
        return slot_.expired();
    }
    
    const Slot_type& slot() const { return slot_; }
    
    Slot_type& slot() { return slot_; }
    
    bool connected() const { return connected_; }
    
private:
    Slot_type slot_;
    bool connected_ = false;
};

template <
    typename Signature
>
class Connection
{
public:
    //using Body_weak = weak_ptr<Connection_body<Signature>>;
    //using Body_shared = shared_ptr<Connection_body<Signature>>;
    using Body_weak = typename Connection_body<Signature>::Weak;
    using Body_shared = typename Connection_body<Signature>::Shared;
    
    Connection()
    {}
    
    Connection(const Body_weak& body):
        weak_body_(body)
    {}
    
    Connection(const Connection& other):
        weak_body_(other.weak_body())
    {}
    
    Connection& operator=(const Connection& other)
    {
        if (this == &other)
            return *this;
        weak_body_ = other.weak_body();
        return *this;    
    }
    
    Connection(Connection&& other):
        weak_body_(move(other.weak_body()))
    {
        other.weak_body().reset();
    }
    
    Connection& operator=(Connection&& other)
    {
        if (this == &other)
            return *this;
        weak_body_ = move(other.weak_body());
        other.weak_body().reset();
        return *this;
    }
            
    Body_weak& weak_body() { return weak_body_; }
    const Body_weak& weak_body() const { return weak_body_; }
    
    void disconnect()
    {
        Body_shared body(weak_body_.lock());
        if (!body)
            return;
        body->disconnect();
    }
    
    bool connected() const
    {
        Body_shared body(weak_body_.lock());
        if (!body)
            return false;
        return body->connected();
    }

    bool expired() const
    {
        Body_shared body(weak_body_.lock());
        if (!body)
            return false;
        return body->expired();
    }
    
private:
    Body_weak weak_body_;
};


template<
    typename Signature
>
class Signal
{
public:
    using Connection_body_type = Connection_body<Signature>;
    using Connection_body_weak = typename Connection_body_type::Weak;
    using Connection_body_shared = typename Connection_body_type::Shared;
    using Connection_type = Connection<Signature>;
    using Slot_function_type = typename Slot<Signature>::Slot_function;
    using Slot_type = Slot<Signature>;
    
    Signal()
    {}
    
    Connection_type connect(const Slot_function_type& f)
    {
        Connection_body_shared new_body = make_shared<Connection_body_type>(Slot<Signature>{f});
        
        connections_.push_back(new_body);
        
        Connection_type c(new_body);
        return c;
    }

    Connection_type connect(const Slot_type& s)
    {
        Connection_body_shared new_body = make_shared<Connection_body_type>(s);
        
        connections_.push_back(new_body);
        
        Connection_type c(new_body);
        return c;
    }
    
    template<typename... Args>
    void operator()(Args... args)
    {
#if 0
        for (auto& c: connections_) {
            if ((*c).connected())
                (*c).slot()(args...);
        }
#endif
        for (auto it = connections_.begin(); it != connections_.end(); ) {
            auto& c = (*(*it));
            if (c.expired())
                c.disconnect();
            if (c.connected()) {
                c.slot()(args...);
                ++it;
            }
            else {
                it = connections_.erase(it);
            }
        }
    }
    
    size_t n_connections() const
    {
        return connections_.size();
    }
    
protected:
private:
    list<Connection_body_shared> connections_;
};


void f() { cout << "[f]: well done!\n"; }
void f1(int x, int y) { cout << "[f1]: x: " << x << ", y: " << y << endl;  }

struct X
{
    void f(int x, int y) { cout << "[X::f]: x: " << x << ", y: " << y << endl; }
};

struct A 
{
    void f() { cout << "[A::f]: well done!\n"; }    
};

struct B 
{
    void f() { cout << "[B::f]: well done!\n"; }    
};

int main()
{
#if 0
    {
        shared_ptr<Connection_body<void()>> b = make_shared<Connection_body<void()>>(Slot<void()>{&f});
        Connection<void()> c(b);
        
        cout << "connected: " << c.connected() << endl;
        c.disconnect();
        cout << "connected: " << c.connected() << endl;
    }
#endif
    {
        Signal<void()> s;
        
        auto c = s.connect(&f);
        s();
        cout << "connected: " << c.connected() << ", signal n connections: " << s.n_connections() << endl;
        
        c.disconnect();
        s();
        cout << "connected: " << c.connected() << ", signal n connections: " << s.n_connections() << endl;
        cout << "\n";
    }
    
    {
        Signal<void(int,int)> s;
        
        auto l_plus = [](int x, int y){ cout << "[l_plus]: sum: " << x + y << endl; };
        
        auto c1 = s.connect(&f1);
        auto c2 = s.connect(l_plus);
        auto c3 = s.connect([](int x, int y){ cout << "[l_mult]: dot: " << x * y << endl; });
        X x;
        using namespace std::placeholders;
        s.connect(bind(&X::f, x, _1, _2));
        
        s(1,2);
        cout << "signal n connections: " << s.n_connections() << endl;
        c2.disconnect();
        s(2,2);
        cout << "signal n connections: " << s.n_connections() << endl;
        c3.disconnect();
        s(3,2);
        cout << "signal n connections: " << s.n_connections() << endl;
        cout << "\n";
    }

    {
        Signal<void()> s;

        shared_ptr<A> a = make_shared<A>(); auto pa = a.get();
        shared_ptr<B> b = make_shared<B>(); auto pb = b.get();
        Signal<void()>::Slot_type sa = Signal<void()>::Slot_type([pa](){ pa->f(); });
        Signal<void()>::Slot_type sb = Signal<void()>::Slot_type([pb](){ pb->f(); });
        
        s.connect(sa.track(a));
        s.connect(sb.track(b));
        
        s();
        cout << endl;
        
        b.reset();
        
        s();
    }
    
    return 0;
}