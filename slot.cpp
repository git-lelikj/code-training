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

void f() { cout << "[f]: well done!\n"; }

struct A
{
    void operator()(int x, int y) { cout << "[A::()]: well done! x: " << x << ", y: " << y << endl; }
};

int f_plus(int x, int y) { cout << "[f_plus]: well done! x: " << x << ", y: " << y << endl; return x + y; }

int main()
{
    {
        Slot<void()> slot(&f);

        slot();
    }
    
    {
        A a;
        Slot<void(int,int)> slot(a);

        slot(3,5);
    }
    
    {
        auto lmbd = [](const string& s){ cout << "[lambda]: well done! s: " << s << endl; };
        Slot<void(const string& s)> slot(lmbd);
        
        slot("alrightythen");
    }
    
    {
        Slot<int(int,int)> slot(&f_plus);
        
        auto res = slot(3,5);
        cout << "return: " << res << endl;
    }
    
    {
        auto lmbd = [](const string& s){ cout << "[lambda]: well done! s: " << s << endl; return s + " alrightythen"; };
        Slot<string(const string&)> slot(lmbd);
        
        auto res = slot("Ace Ventura");
        cout << "return: " << res << endl;
    }
    
    {
        Slot<int(int,int)> slot1(&f_plus);
        Slot<int(int,int)> slot2(slot1);
        Slot<int(int,int)> slot3;
        
        auto res = slot2(2,10);
        cout << "return: " << res << endl;
        
        slot3 = slot2;
        res = slot3(3,55);
        cout << "return: " << res << endl;
        
        Slot<int(int,int)> slot4(move(slot1));
        res = slot4(4,66);
        cout << "return: " << res << endl;
        
        Slot<int(int,int)> slot5;
        slot5 = move(slot2);
        res = slot5(5,77);
        cout << "return: " << res << endl;
    }

    return 0;
}