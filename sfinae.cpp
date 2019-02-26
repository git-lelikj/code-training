#include <bits/stdc++.h>
using namespace std;

template<
    typename T,
    //typename enable_if<!is_class<T>::value && !is_integral<T>::value, int>::type = 0 // c++11
    //enable_if_t<!is_class_v<T> && !is_integral_v<T>, int> = 0
    enable_if_t<!is_class_v<T> && !is_integral_v<T>>* = nullptr
>
void do_smthng(const T& t)
{
    cout << "[do_smthng]: generic version: " << t << endl;
}

template<
    typename T,
    //typename enable_if<is_integral<T>::value, int>::type = 0 // c++11
    //enable_if_t<is_integral_v<T>, int> = 0
    enable_if_t<is_integral_v<T>>* = nullptr
>
void do_smthng(const T& t)
{
    cout << "[do_smthng]: integral version: " << t << endl;
}

template<
    typename T,
    //typename enable_if<is_class<T>::value, int>::type = 0 // c++11
    //enable_if_t<is_class_v<T>, int> = 0
    enable_if_t<is_class_v<T>>* = nullptr
>
void do_smthng(const T& t)
{
    cout << "[do_smthng]: class version: " << t << endl;
}

struct A {};

ostream& operator<<(ostream& os, const A& a)
{
    os << "[A]";
    return os;
}

template <typename Base, typename T>
using Convertible = enable_if_t<is_convertible_v<Base*, T*>>;

template <
    typename Base, typename T,
    //typename enable_if<is_convertible<Base*, T*>::value, int>::type = 0 // c++11
    // enable_if_t<is_convertible_v<Base*, T*>, int> = 0
    // typename = enable_if_t<is_convertible_v<Base*, T*>>
    typename = Convertible<Base, T>
>
void foo(Base* b, T* t)
{
    cout << "[foo]: convertible: " << *t << " -> " << *b << endl;
}

struct B: public A {};

ostream& operator<<(ostream& os, const B& b)
{
    os << "[B]";
    return os;
}

int main()
{
    {
        do_smthng(42);
        do_smthng('a');
        do_smthng("abc");
        do_smthng(3.14);
        do_smthng(A{});        
    }
    cout << endl;
    {
        //foo(new int{5}, new string{"abc"});
        foo(new int{5}, new int{6});
        
        A* a = new A{};
        B* b = new B{};
        a = b;
        
        foo(new B{}, new A{});
    }
}