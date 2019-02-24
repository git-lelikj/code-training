/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <bits/stdc++.h>
using namespace std;

class Slot
{
public:
    Slot()
    {}
    
    Slot& track(weak_ptr<void> p)
    {
        tracked_.push_back(p);
        return *this;
    }
    
    bool expired()
    {
        for (auto& t: tracked_) {
            if (t.expired())
                return true;
        }
        return false;
    }

private:
    vector<weak_ptr<void>> tracked_;
};

struct A {};
struct B {};

int main()
{
    Slot s;
    
    shared_ptr<int> i = make_shared<int>(5);
    shared_ptr<A> a = make_shared<A>();
    shared_ptr<B> b = make_shared<B>();
    
    s.track(i);
    s.track(a);
    s.track(b);
    
    cout << "expired: " << s.expired() << endl;
    
    a.reset();
    
    cout << "expired: " << s.expired() << endl;

    return 0;
}
