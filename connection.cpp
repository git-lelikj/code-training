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
    
private:
    Slot_function slot_func_;
};

template<
    typename Slot_signature
>
class Connection_body
{
public:
    using Slot_type = Slot<Slot_signature>;
    
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
    using Connection_body_weak = weak_ptr<Connection_body<Signature>>;
    using Connection_body_shared = shared_ptr<Connection_body<Signature>>;
    
    Connection(const Connection_body_weak& body):
        weak_body_(body)
    {}
    
    void disconnect()
    {
        Connection_body_shared body(weak_body_.lock());
        if (!body)
            return;
        body->disconnect();
    }
    
    bool connected() const
    {
        Connection_body_shared body(weak_body_.lock());
        if (!body)
            return false;
        return body->connected();
    }
    
private:
    Connection_body_weak weak_body_;
};

#if 0
template<
    typename Signature
>
class Signal
{
public:
    Signal()
    {}
    
    Connection<Signature> connect(Slot<Signature>::Slot_function f)
    {
        Connection<Signature> c;
        return c;
    }
    
private:
    list<Connection<Signature>> connections_;
};
#endif

void f() { cout << "[f]: well done!"; }

int main()
{
    {
        shared_ptr<Connection_body<void()>> b = make_shared<Connection_body<void()>>(Slot<void()>{&f});
        Connection<void()> c(b);
        
        cout << "connected: " << c.connected() << endl;
        c.disconnect();
        cout << "connected: " << c.connected() << endl;
    }

    return 0;
}