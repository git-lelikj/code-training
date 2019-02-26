/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;

class Shared_count_base
{
public:
    Shared_count_base():
        use_count_(1)
    {}
    
    Shared_count_base(const Shared_count_base& other):
        use_count_(other.use_count_)
    {}

    virtual void dispose() = 0;

    void add_ref()
    {
        ++use_count_;
    }
    
    void release()
    {
        if (!--use_count_) {
            dispose();
            delete this;
        }
    }
    
    size_t use_count() const { return use_count_; }
    
private:
    size_t use_count_ = 0;
};

template <typename T>
class Shared_count_impl_p: public Shared_count_base
{
public:
    Shared_count_impl_p(T* p):
        p_(p)
    {}
    
    virtual void dispose()
    {
        if (p_) delete p_;
    }
    
private:
    T* p_ = nullptr;
};

template<typename T, typename D>
class Shared_count_impl_pd: public Shared_count_base
{
public:
    Shared_count_impl_pd(T* p, D d):
        p_(p), deleter_(d)
    {}
    
    virtual void dispose()
    {
        if (p_) deleter_(p_);
    }

private:
    T* p_ = nullptr;
    D deleter_;
};

struct sp_array_deleter
{
    template<typename T>
    void operator()(T* p) { delete [] p; }
};

template <typename T>
class Shared_ptr
{
public:
    using element_type = typename remove_extent<T>::type;
    
    // constructor is a template to store original pointer type along with
    // deleter; T* and Y* must be convertible
    // TBD: check for convertible
    template<typename Y>
    explicit Shared_ptr(Y* p):
        ptr_(p)
    {
        sh_count_ = construct_shared_count(p, typename is_array<T>::type());
    }
    
    // constructor is a template to store original pointer type along with
    // deleter; T* and Y* must be convertible
    // TBD: check for convertible
    template<typename Y, typename D>
    Shared_ptr(Y* p, D d):
        ptr_(p)
    {
        sh_count_ = construct_shared_count(p, d);
    }
    
    Shared_ptr(const Shared_ptr& other):
        ptr_(other.ptr_), sh_count_(other.sh_count_)
    {
        if (sh_count_) 
            sh_count_->add_ref();
    }
    
    Shared_ptr& operator=(const Shared_ptr& other)
    {
#if 0        
        Shared_count_base* tmp = other.sh_count_;
        if (tmp != sh_count_) {
            ptr_ = other.ptr_;
            if (tmp) tmp->add_ref();
            if (sh_count_) sh_count_->release();
            sh_count_ = tmp;
        }
#endif
        Shared_ptr<T>(other).swap(*this);
        return *this;
    }
    
    Shared_ptr(Shared_ptr&& other):
        ptr_(other.ptr_), sh_count_(other.sh_count_)
    {
        other.sh_count_ = nullptr;
    }
    
    Shared_ptr& operator=(Shared_ptr&& other)
    {
#if 0        
        Shared_count_base* tmp = other.sh_count_;
        if (tmp != sh_count_) {
            ptr_ = other.ptr_;
            if (sh_count_) sh_count_->release();
            sh_count_ = tmp;
        }
        other.sh_count_ = nullptr;
#endif
        Shared_ptr<T>(move(other)).swap(*this);
        return *this;
    }
    
    void swap(Shared_ptr& other)
    {
        std::swap(ptr_, other.ptr_);
        std::swap(sh_count_, other.sh_count_);
    }
    
    T* operator->() const { return ptr_; }
    
    // use std::add_lvalue_reference to let T be void
    /*T&*/typename add_lvalue_reference<T>::type operator*() const { return *ptr_; }

    size_t use_count() const { return ( sh_count_ ? sh_count_->use_count() : 0 ); }
    
    ~Shared_ptr()
    {
        if (sh_count_) {
            sh_count_->release();
        }
    }
    
protected:
    template<typename Y>
    Shared_count_base* construct_shared_count(Y* p, false_type)
    {
        Shared_count_base* sc = nullptr;
        try {
            sc = new Shared_count_impl_p<Y>(p);
        }
        catch (...) {
            delete p;
            throw;
        }
        return sc;
    }
    
    template<typename Y>
    Shared_count_base* construct_shared_count(Y* p, true_type)
    {
#if 0        
        Shared_count_base* sc = nullptr;
        try {
            sc = new Shared_count_impl_pd<Y, decltype(sp_array_deleter{})>(p, sp_array_deleter{});
        }
        catch (...) {
            sp_array_deleter(p);
            throw;
        }
        return sc;
#endif
        return construct_shared_count(p, sp_array_deleter{});
    }
    
    template<typename Y, typename D>
    Shared_count_base* construct_shared_count(Y* p, D d)
    {
        Shared_count_base* sc = nullptr;
        try {
            sc = new Shared_count_impl_pd<Y, D>(p, d);
        }
        catch (...) {
            d(p);
            throw;
        }
        return sc;
    }
    
private:
    element_type* ptr_;
    Shared_count_base* sh_count_ = nullptr;
};

template<
    typename T,
    typename... Args
>
Shared_ptr<T> Make_shared(Args... args)
{
    Shared_ptr<T> s(new T(args...));
    return s;
}

namespace test1
{
    struct A
    {
        A() { cout << "[A::A]\n"; }
        ~A() { cout << "[A::~A]\n"; }
        void f() { cout << "[A::f]\n"; }
    };
    
    struct B
    {
        B() { cout << "[B::B]\n"; }
        ~B() { cout << "[B::~B]\n"; }
        void f() { cout << "[B::f]\n"; }
    };
    
    struct C
    {
        C() { cout << "[C::C]\n"; }
        void f() { cout << "[C::f]\n"; }
    private:
        ~C() { cout << "[C::~C]\n"; }
        friend void dispose_C(C*);
    };
    
    void dispose_C(C* p)
    {
        cout << "[dispose_C]\n";
        if (p) delete p;
    }
    
    struct D
    {
        D() { cout << "[D::D]\n"; }
        void f() { cout << "[D::f]\n"; }
        static void dispose(D* p) { cout << "[D::dispose]\n"; delete p; }
    private:
        ~D() { cout << "[D::~D]\n"; }
    };
    
    struct E
    {
        E(int i, string s):
            i_(i), s_(s)
        { 
            cout << "[E::E]: i: " << i_ << ", s: " << s_ << endl; 
        }
        void f() { cout << "[E::f]\n"; }
        ~E() { cout << "[E::~E]\n"; }
    private:
        int i_ = 0;
        string s_;
    };
}

namespace test2
{
    struct A
    {
        A() { cout << "[A::A]\n"; }
        ~A() { cout << "[A::~A]\n"; }
        
        void a() { cout << "[A::a]\n"; }
        virtual void f() { cout << "[A::f]\n"; }
    };
    
    struct B: public A
    {
        B() { cout << "[B::B]\n"; }
        ~B() { cout << "[B::~B]\n"; }
        
        void b() { cout << "[B::b]\n"; }
        virtual void f() { cout << "[B::f]\n"; }
    };
}


int main()
{
    
{
    using namespace test1;
    {
        Shared_ptr<A> s1(new A{});
        Shared_ptr<A> s2(s1);
        cout << "s1 use count: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
    }
    cout << endl;
    {
        Shared_ptr<A> s1(new A{});
        Shared_ptr<A> s2(new A{});
        cout << "s1 use count: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
        s2 = s1;
        cout << "s1 use count: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
    }
    cout << endl;
    {
        Shared_ptr<A> s1(new A{});
        Shared_ptr<A> s2(move(s1));
        cout << "s1 use count: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
    }
    cout << endl;
    {
        Shared_ptr<A> s1(new A{});
        Shared_ptr<A> s2(new A{});
        cout << "s1 use count: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
        s2 = move(s1);
        cout << "s1 use count: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
    }
    cout << endl;
    {
        Shared_ptr<A> s1(new A{});
        Shared_ptr<B> s2(new B{});
        s1->f();
        (*s2).f();
    }
    cout << endl;
    {
        Shared_ptr<C> s1(new C{}, dispose_C);
        s1->f();
    }
    cout << endl;
    {
        Shared_ptr<D> s1(new D{}, D::dispose);
        s1->f();
    }
    cout << endl;
    {
        auto s = Make_shared<E>(5, "lada");
    }
}
    
{
    using namespace test2;
    {
        int* pi = new int{5};
        char* pc = new char{3};
        
        //pi = pc; // error
        
        void* pv = pc;
        void* pv2 = pi;
        
        A* pa = new A{};
        B* pb = new B{};
        
        pa = pb;
        
        void* pv3 = pa;
    }
    
    {
        shared_ptr<void> pv1(new int{5});
        shared_ptr<void> pv2(new B{});
        shared_ptr<A> pa(new B{});
        
        //pv2->b(); // error
        //pv2->f(); // error
        static_pointer_cast<B>(pv2)->b();
        static_pointer_cast<B>(pv2)->f();
        cout << endl;
        
        pa->a();
        pa->f();
        cout << endl;
        //pa->b(); // error
        static_pointer_cast<B>(pa)->b();
        static_pointer_cast<B>(pa)->f();
    }
    cout << endl;    
    {
        Shared_ptr<A> pa(new B{});
        pa->a();
        pa->f();
    }
    cout << endl;    
    {
        Shared_ptr<void> pi(new int{5});
        Shared_ptr<void> pa1(new B{});
    }
    
    cout << endl;
    {
        //shared_ptr<A []> ia(new A[3]);
        Shared_ptr<A[]> ia(new A[3]);
    }
}

    return 0;
}
