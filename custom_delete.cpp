#include <bits/stdc++.h>
using namespace std;

void f(int x, int y) { cout << "[f]: x: " << x << ", y: " << y << endl; }

struct A
{
    A() { cout << "[A::A]\n"; }
    
    void destroy() { delete this; }
    
private:
    ~A() { cout << "[A::~A]\n"; }
};

int main()
{
    {
        shared_ptr<void> s = shared_ptr<void>(static_cast<void*>(0), bind(f, 3, 5));
    }

    {
        shared_ptr<A> sa = shared_ptr<A>(new A(), mem_fn(&A::destroy));
    }
    
    {
        auto sa = shared_ptr<A>(new A(), [](A* p){ p->destroy(); });
    }
    
    return 0;
}