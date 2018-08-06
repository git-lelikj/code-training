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
#if 0
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
    vector<vector<int>> dp(W+1, vector<int>(n+1, 0));
    for (size_t i=1; i<=W; ++i)
        for (size_t j=1; j<=n; ++j) {
            if (wt[j-1] > i) {
                dp[i][j] = dp[i][j-1];
            }
            else {
                dp[i][j] = max(dp[i-wt[j-1]][j-1] + val[j-1], dp[i][j-1]);
            }
        }
    return dp[W][n];
}

}

int knapsack01(const vector<int>& val, const vector<int>& wt, int W)
{
    using namespace dp;
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
#endif

// ---------------------------------------------------------------------------------------------------------------------------
// Disjoint sets (Union-find)
// ---------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include "data_struct.h"

using namespace  std;
using namespace Common;

int main()
{
    Disjoint_sets ds(10);

    map<int, size_t> set_count = ds.count_sets();
    cout << "[main]: initial set counts:\n";
    for (const auto& e: set_count) { cout << "[" << e.first << ":" << e.second << "] "; } cout << endl;

    ds.union_elements(2, 3);
    ds.union_elements(2, 4);
    ds.union_elements(5, 7);
    ds.union_elements(5, 8);
    ds.union_elements(2, 5);
    ds.union_elements(0, 1);
    ds.union_elements(6, 9);
    set_count = ds.count_sets();
    cout << "[main]: after join:\n";
    for (const auto& e: set_count) { cout << "[" << e.first << ":" << e.second << "] "; } cout << endl;

    return 0;
}
#endif
// ---------------------------------------------------------------------------------------------------------------------------
// Disjoint sets (Union-find): Hackerrank: Nuclear Rods Problem
// ---------------------------------------------------------------------------------------------------------------------------
//    The recovery costs per sortie proportional to square root of number of fused rods recovered.
//    Find the minimal cost to recover all the radioactive rods by completing
//    the given function.
//    The first parameter integer n specifies the number of rods. The second
//    parameter pairs is an array of pairs of rods that are fused together. Each
//    item in the array contains exactly two integers, P and Q separated by a
//    space (" "), which means that the rod numbered P is fused to the rod
//    numbered Q. *Note - Each item in the array is a string which needs to be
//    parsed to P and Q
//    Output
//    2
//    Constraints
//    2 ≤ N ≤ 100,000
//    1 ≤ P, Q ≤ N
//    P ≠ Q
//    Sample Input
//    4
//    2
//    1 2
//    1 4
//    Sample Output
//    3
#if 0
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include "data_struct.h"

using namespace  std;
using namespace Common;

int main()
{
    int N = 0, P = 0;
    cin >> N >> P;
    vector<pair<int,int>> fused;
    for (size_t i=0; i < P; ++i) {
        pair<int,int> p;
        cin >> p.first >> p.second;
        fused.push_back(p);
    }
    Disjoint_sets ds(N);
    for (const auto& f: fused) {
        ds.union_elements(f.first-1, f.second-1);
    }
    map<int, size_t> set_count = ds.count_sets();
    cout << "[main]: set counts after fuse:\n";
    for (const auto& e: set_count) { cout << "[" << e.first << ":" << e.second << "] "; } cout << endl;
    int costs = 0;
    for (const auto& e: set_count) {
        costs += ceil(sqrt(e.second));
    }
    cout << "[main]: min recovery costs: " << costs << endl;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------
// Disjoint sets (Union-find): Geeks: Find cycle in graph
// ---------------------------------------------------------------------------------------------------------------------------

//    Given a undirected graph  your task is to complete the method isCycle  to detect if there is a cycle in the undirected graph or not. You should not read any input from stdin/console.
//    There are multiple test cases. For each test case, this method will be called individually.
//    Input (only to be used for Expected Output):
//    The first line of the input contains an integer 'T' denoting the number of test cases. Then 'T' test cases follow. Each test case consists of two lines.
//    Description of  test cases is as follows:
//    The First line of each test case contains two integers 'N' and 'M'  which denotes the no of vertices and no of edges respectively.
//    The Second line of each test case contains 'M'  space separated pairs u and v denoting that there is a bidirectional  edge from u to v .

//    Output:
//    The method should return true if there is a cycle else it should return false.

//    Constraints:
//    1 <=T<= 100
//    1<=N,M<=100
//    0 <=u,v<= N-1

//    Example:
//    Input:
//    2
//    2 2
//    0 1 0 0
//    4 3
//    0 1 1 2 2 3

//    Output:
//    1
//    0
#if 0
#include <iostream>
#include "data_struct.h"

using namespace std;
using namespace Common;

int main()
{
    int N = 0, M = 0;
    cin >> N >> M;
    Disjoint_sets ds(N);
    for (size_t i = 0; i < M; ++i) {
        int u = 0, v = 0;
        cin >> u >> v;
        int parent_u = ds.find(u);
        int parent_v = ds.find(v);
        cout << "[main]: parent u:v: " << parent_u << ":" << parent_v << endl;
        if (parent_u == parent_v) {
            cout << "1\n";
            return 0;
        }
        ds.union_elements(u, v);
    }
    cout << "0\n";

    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------
// Hackerrank: Vaccination Problem
// ---------------------------------------------------------------------------------------------------------------------------
//    Vaccination Problem

//    The world health organization wants to establish a total of B vaccination clinics across N cities to immunization people against fatal diseases.
//    Every city must have at least 1 clinic, and a clinic can only vaccinate people in the same city where they live.
//    The goal is to minimize the number of vaccination kits needed in the largest clinic. For example suppose you have.

//    1.       2 cities and
//    2.       7 clinics to be opened
//    3.       200.000 is the population of first city
//    4.       50,000 is the population of second city
//    5.       Two clinics can open in the first city and
//    6.       Five in the second. This way
//    7.       100,000 people can be immunized in each of the two clinics in first city, and
//    8.       100.000 people can be immunized in the each clinic in the second city
//    9.       So the maximum number of people to be immunized in the largest clinic is 10,000

//    Input:
//    Two integers in the first line, N, the number of cities, and B, the total number of clinics to be opened
//    Each of the following N lines contains an integer ai, the population of city i

//    Output:
//    One integer representing the maximum number of people to be immunized in any single clinic

//    Constraints:
//    1<=N<=500,000
//    N<=B<=2,000,000
//    1<=ai<=5,000,000

//    Sample input:
//    2 7
//    200000
//    500000

//    Sample output:
//    100000
#if 0
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

struct Clinic_load
{
    int population_ = 0;
    int load_ = 0;
    int n_clinics_ = 0;

    explicit Clinic_load(int p):
        population_(p)
    {}

    void set_n_clinics(int n_clinics)
    {
        if (n_clinics <= 0)
            return;
        n_clinics_ = n_clinics;
        load_ = ceil((double)population_ / (double)n_clinics);
    }
};

int max_clinic_load(const vector<int>& populations, int n_clinics)
{

    if (populations.size() > n_clinics)
        return 0;
    auto pred = [](const Clinic_load& l, const Clinic_load& r){ return l.load_ < r.load_; };
    priority_queue<Clinic_load, vector<Clinic_load>, decltype(pred)> load(pred);
    // populate by 1:1 (city:clinic) load
    for (const auto& p: populations) {
        Clinic_load l(p);
        l.set_n_clinics(1);
        load.push(l);
    }
    // process the rest of unallocated clinics
    for (size_t i = 0; i < (n_clinics - populations.size()); ++i) {
        auto most_load = load.top();
        load.pop();
        most_load.set_n_clinics(most_load.n_clinics_+1);
        load.push(most_load);
    }
    // return most loaded clinic
    return (!load.empty() ? load.top().load_ : 0);
}

int main()
{
    int N = 0, B = 0;
    cin >> N >> B;
    vector<int> ai(N, 0);
    for (size_t i = 0; i < N; ++i) {
        cin >> ai[i];
    }
    cout << max_clinic_load(ai, B) << endl;
    return 0;
}
#endif
