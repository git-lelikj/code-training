// ---------------------------------------------------------------------------------------------------------------------------
// Active Object, Singleton, Factory
// ---------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <string>
#include <cassert>
#include "public.h"
#include "singleton.h"
#include "class_factory.h"
#include "active_object.h"
using namespace std;

namespace Common
{
    template<typename T, typename Base>
    shared_ptr<Base> create_singleton()
    {
        return dynamic_pointer_cast<Base>(T::get_instance());
    }
}

namespace Cls_factory_test
{
    using namespace Common;

//    enum CLSID_type {
//        CLSID_Class1 = 0,
//        CLSID_Class2
//    };

//    class ICommon
//    {
//    public:
//        virtual ~ICommon() {}
//    };

    class IInterface1: virtual public ICommon
    {
    public:
        virtual void f1() = 0;
    };

    class IInterface2: virtual public ICommon
    {
    public:
        virtual void f2() = 0;
    };

    class IInterface3: virtual public ICommon
    {
    public:
        virtual void f3() = 0;
    };

    class Class1: public IInterface1
    {
    public:
        void f1() { cout << "[Class1::f1]\n"; }
        ~Class1() { cout << "[Class1::~Class1]\n"; }
    };

    class Class2:   public IInterface2,
                    public IInterface3
    {
    public:
        void f2() { cout << "[Class2::f2]\n"; }
        void f3() { cout << "[Class2::f3]\n"; }
        ~Class2() { cout << "[Class2::~Class2]\n"; }
    };

    using Class_factory = Factory<CLSID_type, ICommon, std::function<std::shared_ptr<ICommon>(void)>>;
}

namespace Singleton_test
{
    using namespace Common;

    class IInterface: virtual public ICommon
    {
    public:
        virtual void f1() = 0;
    };

    class Class:    public Common::Shared_singleton<Class>,
                    public IInterface
    {
    public:
        ~Class() { cout << "[Class::~Class]\n"; }
        void f1() { cout << "[Class:f1]\n"; }
    private:
        Class() {}
        friend class Common::Shared_singleton<Class>;
    };
}

namespace AO_test
{
    using namespace Common;
    using Class_factory = Factory<CLSID_type, ICommon, std::function<std::shared_ptr<ICommon>(void)>>;

    class IInterface: virtual public ICommon
    {
    public:
        virtual void f1(int i, double d, string s) = 0;
    };

    class IControl: virtual public ICommon
    {
    public:
        virtual void init() = 0;
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void wait() = 0;
    };

    class Active:   public Active_object,
                    public IInterface
    {
    public:
        void f1(int i, double d, string s)
        {
            cout << "[Active::f1]: i: " << i << ", d: " << d << ", s: " << s << endl;
        }
    };

    class Proxy:    public IInterface,
                    public IControl
    {
    public:
        void init()
        {
            impl_ = unique_ptr<Active>(new Active);
            assert(impl_!=nullptr);
        }
        void start()
        {
            assert(impl_!=nullptr);
            impl_->start();
        }

        void stop()
        {
            assert(impl_!=nullptr);
            impl_->stop();
        }

        void wait()
        {
            assert(impl_!=nullptr);
            impl_->wait();
        }

        void f1(int i, double d, string s)
        {
            assert(impl_!=nullptr);
            impl_->send([=](){ this->impl_->f1(i, d, s); });
        }

    private:
        unique_ptr<Active> impl_;
    };

}

int main(int argc, char *argv[])
{
    using namespace Common;
    using namespace Cls_factory_test;
    using namespace Singleton_test;
    using namespace AO_test;
#if 0
    cout << "[main]: class factory test =============================================\n";
    {
        Class_factory factory;

        cout << (factory.register_class(CLSID_Class1, &create_shared<Class1, ICommon>) == false?"[main]: failed to register CLSID_Class1\n":"[main]: registered CLSID_Class1\n");
        cout << (factory.register_class(CLSID_Class2, &create_shared<Class2, ICommon>) == false?"[main]: failed to register CLSID_Class2\n":"[main]: registered CLSID_Class2\n");
    //    cout << (factory.register_class(CLSID_Class1, &create_shared<Class1, ICommon>) == false?"[main]: failed to register CLSID_Class1\n":"[main]: registered CLSID_Class1\n");
        {
            std::shared_ptr<IInterface1> c = factory.create_object<IInterface1>(CLSID_Class1);
            if (c) {
                cout << "[main]: calling Class1::f1...\n";
                c->f1();
                cout << "[main]: ptr use_count: " << c.use_count() << endl;
            }
            else
                cout << "[main]: cant create pointer to interface: Class1::IInterface1\n";
        }
        {
            std::shared_ptr<IInterface2> c = factory.create_object<IInterface2>(CLSID_Class1);
            if (c) {
                cout << "[main]: calling Class1::f2...\n";
                c->f2();
                cout << "[main]: ptr use_count: " << c.use_count() << endl;
            }
            else
                cout << "[main]: cant create pointer to interface: Class1::IInterface2\n";
        }
        {
            std::shared_ptr<IInterface2> i2 = factory.create_object<IInterface2>(CLSID_Class2);
            if (i2) {
                cout << "[main]: calling Class2::f2...\n";
                i2->f2();
                cout << "[main]: ptr use_count: " << i2.use_count() << endl;
                cout << "[main]: query Class2::IInterface3...\n";
                shared_ptr<IInterface3> i3 = query_interface<IInterface3>(i2);
                if (i3) {
                    cout << "[main]: calling Class2::f3...\n";
                    i3->f3();
                    cout << "[main]: ptr i2 use_count: " << i2.use_count() << endl;
                    cout << "[main]: ptr i3 use_count: " << i3.use_count() << endl;
                }
                else
                    cout << "[main]: cant query Class2::IInterface3\n";
            }
            else
                cout << "[main]: cant create pointer to interface: Class2::IInterface2\n";
        }
        {
            std::shared_ptr<IInterface3> c = factory.create_object<IInterface3>(CLSID_Class2);
            if (c) {
                cout << "[main]: calling Class2::f3...\n";
                c->f3();
                cout << "[main]: ptr use_count: " << c.use_count() << endl;
            }
            else
                cout << "[main]: cant create pointer to interface: Class2::IInterface3\n";
        }

        {
            shared_ptr<IInterface1> i1 = factory.create_object<IInterface1>(CLSID_Class1);
            shared_ptr<IInterface2> i2 = factory.create_object<IInterface2>(CLSID_Class2);
            shared_ptr<IInterface3> i3 = query_interface<IInterface3>(i2);
        }
    }
    cout << "[main]: singleton test =============================================\n";
    {
//        Class* c = new Class;
        shared_ptr<Class> s1 = Class::get_instance();
        cout << "[main]: Class use count s1: " << s1.use_count() << endl;
        shared_ptr<Class> s2 = Class::get_instance();
        cout << "[main]: Class use count s1: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
    }

    cout << "[main]: proceeding...\n";
    {
        shared_ptr<Class> s1 = Class::get_instance();
        cout << "[main]: Class use count s1: " << s1.use_count() << endl;
        shared_ptr<Class> s2 = Class::get_instance();
        cout << "[main]: Class use count s1: " << s1.use_count() << ", s2 use count: " << s2.use_count() << endl;
    }

    cout << "[main]: singleton + factory test =============================================\n";
    {
        Class_factory factory;

        cout << (factory.register_class(CLSID_Class1, &create_singleton<Class, ICommon>) == false?"[main]: failed to register CLSID_Class1\n":"[main]: registered CLSID_Class1\n");

        {
            shared_ptr<IInterface> i1 = factory.create_object<IInterface>(CLSID_Class1);
            cout << "[main]: i1 use_count: " << i1.use_count() << ", calling f1...\n";
            i1->f1();
            shared_ptr<IInterface> i2 = factory.create_object<IInterface>(CLSID_Class1);
            cout << "[main]: i2 use_count: " << i2.use_count() << ", calling f1...\n";
            i2->f1();
        }
    }
#endif
#if 0
    cout << "[main]: active object test =============================================\n";
    {
        cout << "[main]: start AO test, main thread id: " << this_thread::get_id() << endl;
        Active_object ao;
        ao.start();
        this_thread::sleep_for(chrono::seconds(5));
        ao.send([](){ cout << "[mr]: called\n"; });
        this_thread::sleep_for(chrono::seconds(10));
        ao.stop();
        ao.wait();
    }
#endif
    cout << "[main]: active object test =============================================\n";
    {
        cout << "[main]: start AO test, main thread id: " << this_thread::get_id() << endl;

        auto factory = Class_factory::get_instance();
        cout << (factory->register_class(CLSID_Class1, &create_shared<AO_test::Proxy, ICommon>) == false?"[main]: failed to register CLSID_Class1\n":"[main]: registered CLSID_Class1\n");

        shared_ptr<AO_test::IInterface> i = factory->create_object<AO_test::IInterface>(CLSID_Class1);
        shared_ptr<AO_test::IControl> ictrl = query_interface<AO_test::IControl>(i);

        ictrl->init();
        ictrl->start();

        this_thread::sleep_for(chrono::seconds(5));
        cout << "[main]: calling ao interface...\n";
        i->f1(5, 3.14, "alrightythen");
        this_thread::sleep_for(chrono::seconds(10));

//        ictrl->stop();

        ictrl->wait();
    }
    cout << "[main]: end\n";
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------
// LIS
// ---------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
using namespace std;

namespace brute_force
{
//    struct Lis_rec
//    {
//        int val_;
//        int lis_;
//    };

    int lis_impl(const vector<int>& v, int i, int j)
    {
        cout << "[lis_impl]: i,j: " << i << "," << j << endl;
        if (j <= i)
            return 1;
        int lis = 0;
        for (int k = j-1; k >= i; --k) {
            if (v[k] < v[j])
                lis = max(lis, lis_impl(v, i, k));
        }
        return ++lis;
    }
}

namespace dp
{
    struct Lis_rec
    {
        int val_;
        int lis_;
    };

    int lis_impl(const vector<int>& v)
    {
        if (v.size() <= 1)
            return 1;
        vector<Lis_rec> dp(v.size(), {0, 0});
        size_t i = 0;
        for (const auto& e: v)
            dp[i++].val_ = e;
//        cout << "[lis_impl]: dp: ";
//        for (const auto& e: dp)
//            cout << "[" << e.val_ << "," << e.lis_ << "] ";
//        cout << endl;
        dp[0].lis_ = 1;
        int res_lis = 1;
        for (size_t j = 1; j < v.size(); ++j) {
            int lis = 1;
            for (size_t k = 0; k < j; ++k) {
                if (dp[j].val_ > dp[k].val_)
                    lis = max(lis, dp[k].lis_ + 1);
            }
            dp[j].lis_ = lis;
            res_lis = max(res_lis, lis);
        }
        cout << "[lis_impl]: dp: ";
        for (const auto& e: dp)
            cout << "[" << e.val_ << "," << e.lis_ << "] ";
        cout << endl;
        return res_lis;
    }
}

int lis(const vector<int>& v)
{
    using namespace dp;
    return lis_impl(v);
}

int main()
{
    int N = 0;
    cin >> N;
    vector<int> a(N, 0);
    for (size_t i=0; i<N; ++i)
        cin >> a[i];
    cout << "input: ";
    for (const auto& e: a)
        cout << e << " ";
    cout << endl;
    int res = lis(a);
    cout << "Resulting LIS: " << res << endl;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------
// LCS
// ---------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace brute_force
{

int lcs(const string& p, const string& q, int i, int j)
{
    if ((i < 0) || (j < 0))
        return 0;
    if (p[i] == q[j])
        return lcs(p, q, i-1, j-1) + 1;
    else {
        return max(lcs(p, q, i-1, j), lcs(p, q, i, j-1));
    }
}

}

namespace dp
{

int lcs(const string& p, const string& q)
{
    int n = p.size(), m = q.size();
    if (!n || !m)
        return 0;
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for (size_t i=0; i<=n; ++i)
        dp[i][0] = 0;
    for (size_t j=0; j<=m; ++j)
        dp[0][j] = 0;
    for (size_t i=1; i<=n; ++i)
        for (size_t j=1; j<=m; ++j) {
            if (p[i-1] == q[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    return dp[n][m];
}

}

int main()
{
    using namespace dp;
    string p, q;
    cin >> p >> q;
    cout << "input: p,q: " << p << "," << q << endl;
    int lcs_res = lcs(p, q);
    cout << "lcs: " << lcs_res << endl;
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------
// Knapsack 0:1
// ---------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace brute_force
{

int knapsack01_impl(const vector<int>& val, const vector<int>& wt, int W, size_t n)
{
    if (n==0 || W<=0)
        return 0;
    if (wt[n-1] > W)
        return knapsack01_impl(val, wt, W, n-1);
    return max(knapsack01_impl(val, wt, W-wt[n-1], n-1)+val[n-1], knapsack01_impl(val, wt, W, n-1));
}

}

namespace dp
{

int knapsack01_impl(const vector<int>& val, const vector<int>& wt, int W, size_t n)
{
    vector<vector<int>> dp(n, vector<int>(W, 0));
}

}

int knapsack01(const vector<int>& val, const vector<int>& wt, int W)
{
    using namespace brute_force;
    if (!val.size() || val.size()!=wt.size() || W<=0)
        return 0;
    return knapsack01_impl(val, wt, W, val.size());
}

int main()
{
    int N = 0;
    cin >> N;
    int W = 0;
    cin >> W;
    vector<int> val(N, 0);
    vector<int> wt(N, 0);
    for (size_t i=0; i<N; ++i)
        cin >> val[i];
    for (size_t i=0; i<N; ++i)
        cin >> wt[i];
    int res = knapsack01(val, wt, W);
    cout << "knapsack 0:1 : " << res << endl;
    return 0;
}
