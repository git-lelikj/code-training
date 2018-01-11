// ---------------------------------------------------------------------------------------------------------------------------------------
//    C++ Class Template Specialization
//    You are given a main function which reads the enumeration values for two different types as input, then prints out the corresponding enumeration names.
//    Write a class template that can provide the names of the enumeration values for both types. If the enumeration value is not valid, then print unknown.
//    Input Format
//    The first line contains , the number of test cases.
//    Each of the  subsequent lines contains two space-separated integers. The first integer is a color value, , and the second integer is a fruit value, .
//    Constraints
//    Output Format
//    The locked stub code in your editor prints  lines containing the color name and the fruit name corresponding to the input enumeration index.
//    Sample Input
//    2
//    1 0
//    3 3
//    Sample Output
//    green apple
//    unknown unknown
//    Explanation
//    Since , there are two lines of output.
//    The two input index values,  and , correspond to green in the color enumeration and apple in the fruit enumeration. Thus, we print green apple.
//    The two input values,  and , are outside of the range of our enums. Thus, we print unknown unknown.
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <string>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

template <typename T> struct Traits;

// Define specializations for the Traits class template here.
template <> struct Traits<Fruit>
{
    static string name(int index)
    {
        switch (index) {
        case static_cast<int>(Fruit::apple):    return "apple"; break;
        case static_cast<int>(Fruit::orange):   return "orange"; break;
        case static_cast<int>(Fruit::pear):     return "pear"; break;
        default:                                return "unknown"; break;
        }
    }
};

template <> struct Traits<Color>
{
    static string name(int index)
    {
        switch (index) {
        case static_cast<int>(Color::red):    return "red"; break;
        case static_cast<int>(Color::green):  return "green"; break;
        case static_cast<int>(Color::orange): return "orange"; break;
        default:                              return "unknown"; break;
        }
    }
};

int main()
{
    int t = 0; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 4::C++ Variadics
//    A template parameter pack is a template parameter that accepts zero or more template arguments (non-types, types, or templates).
//    To read more about parameter pack, click here.
//    Create a template function named reversed_binary_value. It must take an arbitrary number of bool values as template parameters.
//    These booleans represent binary digits in reverse order. Your function must return an integer corresponding to the binary value of the digits
//    represented by the booleans. For example: reversed_binary_value<0,0,1>() should return 4.
//    Input Format
//    The first line contains an integer t, , the number of test cases. Each of the  subsequent t lines contains a test case. A test case is described as
//    2 space-separated integers, x and y, respectively.
//    x is the value to compare against.
//    y represents the range to compare: 64 x y  to 64 x y + 63.
//    Constraints
//    The number of template parameters passed to reversed_binary_value will be .
//    Output Format
//    Each line of output contains  binary characters (i.e., 's and 's). Each character represents one value in the range. The first character corresponds
//    to the first value in the range. The last character corresponds to the last value in the range. The character is  if the value in the range matches ;
//    otherwise, the character is .
//    Sample Input
//    2
//    65 1
//    10 0
//    Sample Output
//    0100000000000000000000000000000000000000000000000000000000000000
//    0000000000100000000000000000000000000000000000000000000000000000
//    Explanation
//    The second character on the first line is a , because the second value in the range  is  and  is .
//    The eleventh character on the second line is a , because the eleventh value in the range  is  and  is .
//    All other characters are zero, because the corresponding values in the range do not match .
// ---------------------------------------------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------------------------------------------------------
// Debug common solution
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
using namespace std;

template<int N, bool... digits>
struct Dbg
{
    static void test(int x, int y)
    {
//        cout << "[" << __PRETTY_FUNCTION__ << "]: sizeof digits: " << sizeof...(digits) << endl;
        Dbg<N-1, 0, digits...>::test(x, y);
        Dbg<N-1, 1, digits...>::test(x, y);
    }
};

template<bool... digits>
struct Dbg<0, digits...>
{
    static void test(int x, int y)
    {
        //TBD
        cout << "[" << __PRETTY_FUNCTION__ << "]: sizeof digits: " << sizeof...(digits) << endl;
    }
};

int main()
{
    Dbg<6>::test(0,0);

    return 0;
}
#endif
#if 0
#include <iostream>
using namespace std;

// Enter your code for reversed_binary_value<bool...>()

// ---------------------------------------------------------------------------------------------------------------------------------------
// Misc Tries
// ---------------------------------------------------------------------------------------------------------------------------------------

//template<bool digit>
//struct Impl
//{
//    static int reverse_binary_value_impl(size_t total_digits)
//    {
//        return (digit==true ? 1 << (total_digits - 1) : 0 );
//    }
//};
//template<bool digit, bool... digits>
//struct Impl
//{
//    static int reverse_binary_value_impl(size_t total_digits)
//    {
//        return Impl<digits...>::reverse_binary_value_impl(total_digits) | (digit==true ? 1 << (total_digits - (sizeof...(digits)+1)) : 0 );
//        return 0;
//    }
//};
//template<bool... digits>
//int reverse_binary_value()
//{
//    return reverse_binary_value_impl<digits...>(sizeof...(digits));
//}

//template<bool digit, bool... digits>
//struct Impl
//{
//    static int reverse_binary_value(size_t total_digits)
//    {
//        if (sizeof...(digits))
//            return Impl<digits...>::reverse_binary_value(total_digits) | (digit==true ? 1 << (total_digits - (sizeof...(digits)+1)) : 0 );
//        else
//            return (digit==true ? 1 << (total_digits - 1) : 0 );
//    }
//};
//template<bool... digits>
//int reverse_binary_value()
//{
//    return Impl<digits...>::reverse_binary_value(sizeof...(digits));
//}

//template<bool... digits>
//struct Impl<0, digits...>
//{
//    static int reverse_binary_value(size_t total_digits)
//    {
//        return (digit==true ? 1 << (total_digits - 1) : 0 );
//    }
//};
//template<int N, bool digit, bool... digits>
//struct Impl
//{
//    static int reverse_binary_value(size_t total_digits)
//    {
//        return Impl<N-1, digits...>::reverse_binary_value(total_digits) | (digit==true ? 1 << (total_digits - (sizeof...(digits)+1)) : 0 );
//    }
//};
//template<bool... digits>
//int reverse_binary_value()
//{
//    return Impl<sizeof...(digits), digits...>::reverse_binary_value(sizeof...(digits));
//}

// ---------------------------------------------------------------------------------------------------------------------------------------
// Hackerrank submission
// ---------------------------------------------------------------------------------------------------------------------------------------

//template<typename T>
//int reversed_binary_value_impl(size_t total_digits, const T& head)
//{
//    return (head==true ? 1 << (total_digits - 1) : 0 );
//}

//template<typename T, typename... Args>
//int reversed_binary_value_impl(size_t total_digits, const T& head, const Args&... tail)
//{
//    return reversed_binary_value_impl(total_digits, tail...) | (head==true ? 1 << (total_digits - (sizeof...(tail)+1)) : 0 );
//}

//template<bool... digits>
//int reversed_binary_value()
//{
//    return reversed_binary_value_impl(sizeof...(digits), digits...);
//}

// ---------------------------------------------------------------------------------------------------------------------------------------
// Niciest solution
// ---------------------------------------------------------------------------------------------------------------------------------------

template<bool last>
int reversed_binary_value_impl(size_t total_digits)
{
    return (last==true ? 1 << (total_digits - 1) : 0 );
}

template<bool first, bool second, bool... rest>
int reversed_binary_value_impl(size_t total_digits)
{
    return reversed_binary_value_impl<second, rest...>(total_digits) | (first==true ? 1 << (total_digits - (sizeof...(rest)+2)) : 0 );
}

template<bool... digits>
int reversed_binary_value()
{
    return reversed_binary_value_impl<digits...>(sizeof...(digits));
}

#if 0
int main()
{
    cout << "[reverse_binary_value]: result: " << reversed_binary_value<false, true, false, true, false, false>() << endl;
    return 0;
}
#endif

template <int n, bool...digits>
struct CheckValues {
    static void check(int x, int y)
    {
        CheckValues<n-1, 0, digits...>::check(x, y);
        CheckValues<n-1, 1, digits...>::check(x, y);
    }
};

template <bool...digits>
struct CheckValues<0, digits...> {
    static void check(int x, int y)
    {
        int z = reversed_binary_value<digits...>();
        std::cout << (z+64*y==x);
    }
};

int main()
{
    int t; std::cin >> t;

    for (int i=0; i!=t; ++i) {
        int x, y;
        cin >> x >> y;
        CheckValues<6>::check(x, y);
        cout << "\n";
    }
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 4::Print Pretty
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    int T; cin >> T;
    cout << setiosflags(ios::uppercase);
    cout << setw(0xf) << internal;
    while(T--) {
        double A; cin >> A;
        double B; cin >> B;
        double C; cin >> C;
        /* Enter your code here */
        cout << left << hex << showbase << nouppercase << static_cast<int64_t>(A) << endl;
        cout << setw(15) << right << dec << setfill('_') << setprecision(2) << fixed << showpos << B << endl;
        cout << setw(0) << left << setprecision(9) << scientific << uppercase << noshowpos << C << endl;
    }
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 4::Preprocessor Solution
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
using namespace std;

#define toStr(arg) #arg
#define io(container) cin >> v
#define FUNCTION(name, compare_op) void name(int& res, int arg) { res = ( res compare_op arg ? res : arg ); }
#define INF (0x7fffffff)
#define foreach(container, index) for(size_t i=0; i<container.size(); ++i)

#if !defined toStr || !defined io || !defined FUNCTION || !defined INF
#error Missing preprocessor definitions
#endif

FUNCTION(minimum, <)
/*
void minimum(int& res, int arg) { res = (res < arg ? res : arg); }
 */
FUNCTION(maximum, >)

int main(){
    int n; cin >> n;
    vector<int> v(n);
    foreach(v, i) {
        io(v)[i];
    }
    int mn = INF;
    int mx = -INF;
//    cout << "mn: " << mn << " mx: " << mx << endl;
    foreach(v, i) {
        minimum(mn, v[i]);
        maximum(mx, v[i]);
    }
    int ans = mx - mn;
    cout << toStr(Result =) <<' '<< ans;
    return 0;

}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 4::Inherited Code
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <string>
#include <sstream>
#include <exception>
using namespace std;

#if 0
class BadLengthException: public exception
{
public:
    const static size_t MAX_LEN = 255;

    BadLengthException(int bad_length)
    {
        snprintf(what_, MAX_LEN, "%d", bad_length);
    }

    const char* what() const noexcept
    {
        return what_;
    }

private:
    char what_[MAX_LEN];
};
#endif

class BadLengthException
{
public:
    BadLengthException(int bad_length):
        bad_length_(bad_length)
    {}

    int what() const noexcept
    {
        return bad_length_;
    }

private:
    int bad_length_ = 0;
};

bool checkUsername(string username) {
    bool isValid = true;
    int n = username.length();
    if(n < 5) {
        throw BadLengthException(n);
    }
    for(int i = 0; i < n-1; i++) {
        if(username[i] == 'w' && username[i+1] == 'w') {
            isValid = false;
        }
    }
    return isValid;
}

int main() {
    int T; cin >> T;
    while(T--) {
        string username;
        cin >> username;
        try {
            bool isValid = checkUsername(username);
            if(isValid) {
                cout << "Valid" << '\n';
            } else {
                cout << "Invalid" << '\n';
            }
        } catch (BadLengthException e) {
            cout << "Too short: " << e.what() << '\n';
        }
    }
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 4::Exceptional Server
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <exception>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
using namespace std;

class Server {
private:
    static int load;
public:
    static int compute(long long A, long long B) {
        load += 1;
        if(A < 0) {
            throw std::invalid_argument("A is negative");
        }
        vector<int> v(A, 0);
        int real = -1, cmplx = sqrt(-1);
        if(B == 0) throw 0;
        real = (A/B)*real;
        int ans = v.at(B);
        return real + A - B*ans;
    }
    static int getLoad() {
        return load;
    }
};
int Server::load = 0;

int main() {
    int T; cin >> T;
    while(T--) {
        long long A, B;
        cin >> A >> B;

        /* Enter your code here. */

        try {
            int res = Server::compute(A, B);
            cout << res << endl;
        }
        catch (std::bad_alloc& e) {
            cout << "Not enough memory\n";
        }
        catch (std::exception& e) {
            cout << "Exception: " << e.what() << endl;
        }
        catch (...) {
            cout << "Other Exception\n";
        }
    }
    cout << Server::getLoad() << endl;
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 4::Magic Spells
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell {
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell {
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell {
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell {
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
};
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
    Fireball* fireball = dynamic_cast<Fireball*>(spell);
    if (fireball!=nullptr) {
        fireball->revealFirepower();
        return;
    }
    Frostbite* frostbite = dynamic_cast<Frostbite*>(spell);
    if (frostbite!=nullptr) {
        frostbite->revealFrostpower();
        return;
    }
    Waterbolt* waterbolt = dynamic_cast<Waterbolt*>(spell);
    if (waterbolt!=nullptr) {
        waterbolt->revealWaterpower();
        return;
    }
    Thunderstorm* thuderstorm = dynamic_cast<Thunderstorm*>(spell);
    if (thuderstorm!=nullptr) {
        thuderstorm->revealThunderpower();
        return;
    }
    // generic spell, do LCS(spell->revealScrollName, SpellJournal::journal)
    string x = spell->revealScrollName(), y = SpellJournal::read();
    size_t n = x.size(), m = y.size();
    if (n==0 || m==0) {
        cout << 0 << endl;
        return;
    }
    vector<vector<size_t>> dp(m+1, vector<size_t>(n+1, 0));
    for (size_t i = 1; i <= m; ++i) {
        for (size_t j = 1; j <= n; ++j) {
            if (x[j-1] == y[i-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    cout << dp[m][n] << endl;
    return;
}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            }
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Variable Sized Arrays
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    size_t n = 0, q = 0;
    cin >> n >> q;
    vector<vector<uint>> a(n);
    for (size_t i = 0; i < n; ++i) {
        size_t m = 0;
        cin >> m;
        a[i].resize(m);
        for (size_t j = 0; j < m; ++j)
            cin >> a[i][j];
    }
    for (size_t query = 0; query < q; ++query) {
        size_t i = 0, j = 0;
        cin >> i >> j;
        cout << a[i][j] << endl;
    }
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Overload Operators
// ---------------------------------------------------------------------------------------------------------------------------------------
//Operator Overloading
#if 0
#include<iostream>

using namespace std;

class Complex
{
public:
    int a,b;
    void input(string s)
    {
        int v1=0;
        int i=0;
        while(s[i]!='+')
        {
            v1=v1*10+s[i]-'0';
            i++;
        }
        while(s[i]==' ' || s[i]=='+'||s[i]=='i')
        {
            i++;
        }
        int v2=0;
        while(i<s.length())
        {
            v2=v2*10+s[i]-'0';
            i++;
        }
        a=v1;
        b=v2;
    }
};
//Overload operators + and << for the class complex
//+ should add two complex numbers as (a+ib) + (c+id) = (a+c) + i(b+d)
//<< should print a complex number in the format "a+ib"

Complex operator+(const Complex& x, const Complex& y)
{
    Complex z;
    z.a = x.a + y.a;
    z.b = x.b + y.b;
    return z;
}

ostream& operator<<(ostream& os, const Complex& z)
{
    os << z.a << "+i" << z.b;
    return os;
}

int main()
{
    Complex x,y;
    string s1,s2;
    cin>>s1;
    cin>>s2;
    x.input(s1);
    y.input(s2);
    Complex z=x+y;
    cout<<z<<endl;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Box It!
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include<bits/stdc++.h>

using namespace std;


//Implement the class Box
//l,b,h are integers representing the dimensions of the box

// The class should have the following functions :

// Constructors:
// Box();
// Box(int,int,int);
// Box(Box);


// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)

class Box
{
public:
    Box()
    {}

    Box(int length, int breadth, int height):
        l(length), b(breadth), h(height)
    {}

    Box(const Box& b):
        l(b.l), b(b.b), h(b.h)
    {}

    int getLength() const
    {
        return l;
    }

    int getBreadth() const
    {
        return b;
    }

    int getHeight() const
    {
        return h;
    }

    long long CalculateVolume()
    {
        return static_cast<long long>(l) * static_cast<long long>(b) * static_cast<long long>(h);
    }

    friend bool operator<(const Box& l, const Box& r)
    {
        if (l.l < r.l)              return true;
        else if (l.l > r.l)         return false;
        else {
            if (l.b < r.b)          return true;
            else if (l.b > r.b)     return false;
            else {
                if (l.h < r.h)      return true;
                else                return false;
            }
        }
    }

private:
    int l = 0;
    int b = 0;
    int h = 0;
};

ostream& operator<<(ostream& os, const Box& b)
{
    os << b.getLength() << " " << b.getBreadth() << " " << b.getHeight();
    return os;
}

void check2()
{
    int n;
    cin>>n;
    Box temp;
    for(int i=0;i<n;i++)
    {
        int type;
        cin>>type;
        if(type ==1)
        {
            cout<<temp<<endl;
        }
        if(type == 2)
        {
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            temp=NewBox;
            cout<<temp<<endl;
        }
        if(type==3)
        {
            int l,b,h;
            cin>>l>>b>>h;
            Box NewBox(l,b,h);
            if(NewBox<temp)
            {
                cout<<"Lesser\n";
            }
            else
            {
                cout<<"Greater\n";
            }
        }
        if(type==4)
        {
            cout<<temp.CalculateVolume()<<endl;
        }
        if(type==5)
        {
            Box NewBox(temp);
            cout<<NewBox<<endl;
        }

    }
}

int main()
{
    check2();
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Accessing Inherited Functions
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include<iostream>

using namespace std;

class A
{
    public:
        A(){
            callA = 0;
        }
    private:
        int callA;
        void inc(){
            callA++;
        }

    protected:
        void func(int & a)
        {
            a = a * 2;
            inc();
        }
    public:
        int getA(){
            return callA;
        }
};

class B
{
    public:
        B(){
            callB = 0;
        }
    private:
        int callB;
        void inc(){
            callB++;
        }
    protected:
        void func(int & a)
        {
            a = a * 3;
            inc();
        }
    public:
        int getB(){
            return callB;
        }
};

class C
{
    public:
        C(){
            callC = 0;
        }
    private:
        int callC;
        void inc(){
            callC++;
        }
    protected:
        void func(int & a)
        {
            a = a * 5;
            inc();
        }
    public:
        int getC(){
            return callC;
        }
};

class D: public A, public B, public C
{

    int val;
    public:
    //Initially val is 1
     D()
     {
        val = 1;
     }


     //Implement this function
     void update_val(int new_val)
     {
         size_t n_2 = 0;
         for (int test_val = new_val; (test_val >= 2) && (test_val % 2 == 0); test_val /= 2, ++n_2);
         size_t n_3 = 0;
         for (int test_val = new_val; (test_val >= 3) && (test_val % 3 == 0); test_val /= 3, ++n_3);
         size_t n_5 = 0;
         for (int test_val = new_val; (test_val >= 5) && (test_val % 5 == 0); test_val /= 5, ++n_5);
         for (int i=0; i < n_2; ++i)    A::func(val);
         for (int i=0; i < n_3; ++i)    B::func(val);
         for (int i=0; i < n_5; ++i)    C::func(val);
     }

     //For Checking Purpose
     void check(int); //Do not delete this line.
};

void D::check(int new_val)
{
    update_val(new_val);
    cout << "Value = " << val << endl << "A's func called " << getA() << " times " << endl << "B's func called " << getB() << " times" << endl << "C's func called " << getC() << " times" << endl;
}


int main()
{
    D d;
    int new_val;
    cin >> new_val;
    d.check(new_val);

}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Virtual Functions
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include <string>

class Person
{
public:
    virtual void getdata()
    {
        cin >> name_ >> age_;
    }

    virtual void putdata()
    {
        cout << name_ << " " << age_ << " ";
    }

private:
    string name_;
    int age_ = 0;
};

class Professor: public Person
{
public:
    Professor():
        cur_id_(++running_id_)
    {}

    virtual void getdata()
    {
        Person::getdata();
        cin >> publications_;
    }

    virtual void putdata()
    {
        Person::putdata();
        cout << publications_ << " " << cur_id_ << endl;
    }

private:
    int publications_ = 0;
    int cur_id_ = 0;
    static int running_id_;
};

int Professor::running_id_ = 0;

class Student: public Person
{
public:
    Student():
        cur_id_(++running_id_)
    {}

    virtual void getdata()
    {
        Person::getdata();
        for (int i=0; i < 6; ++i)
            cin >> marks_[i];
    }

    virtual void putdata()
    {
        Person::putdata();
        cout << accumulate(begin(marks_), end(marks_), 0) << " " << cur_id_ << endl;
    }

private:
    int marks_[6] = {0,0,0,0,0,0};
    int cur_id_ = 0;
    static int running_id_;
};

int Student::running_id_ = 0;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Attending Workshops
//    Output to stdout is handled for you.

//    Your initialize function must return a pointer to an Available_Workshops object.
//    Your CalculateMaxWorkshops function must return maximum number of non-overlapping workshops the student can attend.
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include<bits/stdc++.h>

using namespace std;

#include <algorithm>

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
struct Workshop
{
    int start_time_ = 0;
    int duration_ = 0;
    int end_time_ = 0;
};

struct Available_Workshops
{
    int n_ = 0;
    Workshop* workshops_ = nullptr;
};

Available_Workshops* initialize(int start_time[], int duration[], int n)
{
    Available_Workshops* w = new Available_Workshops;
    w->n_ = n;
    w->workshops_ = new Workshop[n];
    for (size_t i = 0; i < n; ++i) {
        w->workshops_[i].start_time_ = start_time[i];
        w->workshops_[i].duration_ = duration[i];
        w->workshops_[i].end_time_ = start_time[i] + duration[i];
    }
    return w;
}

ostream& operator<<(ostream& os, const Workshop& w)
{
    os << "[" << w.start_time_ << "," << w.duration_ << "," << w.end_time_ << "]";
    return os;
}

ostream& operator<<(ostream& os, Available_Workshops* w)
{
    if (w==nullptr)
        return os;
    os << "size: " << w->n_ << endl;
    for (size_t i = 0; i < w->n_; ++i) {
        os << w->workshops_[i];
    }
    return os;
}

int CalculateMaxWorkshops(Available_Workshops* w)
{
    // sort in-place by end-time ascending
    sort(w->workshops_, w->workshops_ + w->n_, [](const Workshop& l, const Workshop& r) { return l.end_time_ < r.end_time_; });
//    cout << w << endl;
    int max_workshops = 0;
    // implemente greedy-algorithm: each loop pick workshop with closest end-time
    for (size_t i = 0; i < w->n_;) {
        ++max_workshops;
        size_t j = i + 1;
        for (; (j < w->n_) && (w->workshops_[j].start_time_ < w->workshops_[i].end_time_); ++j );
        i = j;
    }
    return max_workshops;
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
//    cout << ptr << endl;
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Attribute Parser
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <cmath>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <memory>
using namespace std;

namespace
{
    constexpr const char* Not_found_msg = "Not Found!";

    using Attributes = map<string, string>;

    struct Tag
    {
        struct Shared_ptr_cmp
        {
            bool operator()(const shared_ptr<Tag>& l, const shared_ptr<Tag>& r)
            {
                return (*l).name_ < (*r).name_;
            }
        };

        using Tags = set<shared_ptr<Tag>, Shared_ptr_cmp>;

        Tag(const string& name):
            name_(name)
        {}
        string name_;
        Attributes attributes_;
        Tags nested_tags_;
    };

    ostream& operator<<(ostream& os, const Tag& tag)
    {
        os << "<" << tag.name_ << ">";
        if (tag.attributes_.size()) {
            os << " attributes: ";
            for (auto a: tag.attributes_) {
                os << "(" << a.first << "," << a.second << ")";
            }
            os << endl;
        }
        if (tag.nested_tags_.size()) {
            os << " nested tags: ";
            for (auto t: tag.nested_tags_) {
                os << t->name_ << " ";
            }
            os << endl;
            for (auto t: tag.nested_tags_) {
                os << *t << endl;
            }
        }
        return os;
    }

    struct Query
    {
        vector<string> nested_tags_;
        string attribute_;
    };

    using Queries = vector<Query>;

    ostream& operator<<(ostream& os, const Query& q)
    {
        for (size_t i = 0; i < q.nested_tags_.size(); ++i) {
            os << q.nested_tags_[i];
            if (i != q.nested_tags_.size() - 1)
                os << ".";
        }
        os << "~" << q.attribute_;
        return os;
    }

    enum class Parsing_state
    {
        Start_tag,
        Tag_attribute,
    };

    shared_ptr<Tag> input_tags(size_t n_lines)
    {
        stack<shared_ptr<Tag>> tag_stack;
        tag_stack.push(make_shared<Tag>("root"));
        Parsing_state state = Parsing_state::Start_tag;
        for (size_t l = 0; l < n_lines; ++l) {
            string line;
            getline(cin, line);
            // strip <>
            line.erase(remove_if(line.begin(), line.end(), [](unsigned char x){ return (x == '<' || x == '>'); }), line.end());
            for (istringstream iss(line); iss;) {
                string token;
                iss >> token;
                if (!token.size())
                    continue;

                // end of tag, pop from stack
                if (token[0] == '/') {
                    if (!tag_stack.empty())
                        tag_stack.pop();
                    state = Parsing_state::Start_tag;
                }
                else {
                    switch (state) {
                    case Parsing_state::Start_tag:
                    {
                        // new tag name: add to parent set of tags, push to stack
                        auto tag = make_shared<Tag>(token);
                        tag_stack.top()->nested_tags_.insert(tag);
                        tag_stack.push(tag);
                        state = Parsing_state::Tag_attribute;
                    }
                        break;
                    case Parsing_state::Tag_attribute:
                    {
                        // read = and attribute value
                        string delim, attr_value;
                        iss >> delim >> attr_value;
                        // strip ""
                        attr_value.erase(remove_if(attr_value.begin(), attr_value.end(), [](unsigned char x){ return (x == '"'); }), attr_value.end());
                        // add attribute to tag in stack
                        tag_stack.top()->attributes_.insert({token, attr_value});
                        // stay on the same state
                    }
                        break;
                    default:
                        break;
                    }
                }
            }
            state = Parsing_state::Start_tag;
        }
        return tag_stack.top();
    }

    void input_queries(Queries& queries, size_t n_queries)
    {
        for (size_t l = 0; l < n_queries; ++l) {
            string line;
            getline(cin, line);
            Query q;
            for (size_t curr_pos = 0; curr_pos != string::npos; ) {
                size_t dot_pos = line.find('.', curr_pos);
                if (dot_pos == string::npos) {
                    size_t tilda_pos = line.find('~', curr_pos);
                    if (tilda_pos == string::npos) {
                        // wrong query: TBD
                        curr_pos = string::npos;
                        continue;
                    }
                    else {
                       q.nested_tags_.push_back(line.substr(curr_pos, tilda_pos - curr_pos));
                       q.attribute_ = line.substr(tilda_pos + 1);
                       curr_pos = string::npos;
                       continue;
                    }
                }
                else {
                    q.nested_tags_.push_back(line.substr(curr_pos, dot_pos - curr_pos));
                    curr_pos = dot_pos + 1;
                    continue;
                }
            }
            queries.push_back(q);
        }
    }

    string execute_query(shared_ptr<Tag> root_tag, const Query& query)
    {
        if (!query.nested_tags_.size())
            return Not_found_msg;
        shared_ptr<Tag> curr_tag = root_tag;
        for (auto q: query.nested_tags_) {
            auto it = curr_tag->nested_tags_.find(make_shared<Tag>(q));
            if (it == curr_tag->nested_tags_.end()) {
                return Not_found_msg;
            }
            else {
                curr_tag = *it;
            }
        }
        // curr_tag points to target tag, look for attribute
        auto it = curr_tag->attributes_.find(query.attribute_);
        if (it == curr_tag->attributes_.end())
            return Not_found_msg;
        else
            return it->second;
    }

}

int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    size_t n_lines = 0, n_queries = 0;
    cin >> n_lines >> n_queries;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Queries queries;
    shared_ptr<Tag> root_tag = input_tags(n_lines);
    input_queries(queries, n_queries);
    for (size_t q = 0; q < queries.size(); ++q) {
        string result = execute_query(root_tag, queries[q]);
        cout << result << endl;
    }
    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Bit Array
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Bit Array: Solution with std::bitset: hangs on compilation
// ---------------------------------------------------------------------------------------------------------------------------------------
int main() {
#if 0
    bitset<Num_of_bits> bitset_array;

    uint32_t N = 0, S = 0, P = 0, Q = 0;

    cin >> N >> S >> P >> Q;

    uint32_t prev_value = S % Num_of_bits;
    uint32_t curr_value = 0;
    for (size_t i = 1; i < N; ++i) {
        curr_value = (prev_value * P + Q) % Num_of_bits;
    }
#endif

    Bitset bitset(Num_of_bits);

    cout << "size of Bitset(1024): " << sizeof(bitset) << ", n_bytes: " << bitset.get_n_bytes() << endl;

    bitset.set_bit(0);
    bitset.set_bit(1);
    bitset.set_bit(15);

    cout << bitset << endl;

    cout << "bit 0: " << bitset.get_bit(0) << endl;
    cout << "bit 1: " << bitset.get_bit(1) << endl;
    cout << "bit 2: " << bitset.get_bit(2) << endl;
    cout << "bit 15: " << bitset.get_bit(15) << endl;

    return 0;
}
#endif
#if 0
// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Bit Array: Solution with handcrafted bitset: dynamic allocation - fails on testcases 5 and 8
// ---------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <bitset>
#include <memory>
#include <algorithm>
#include <iterator>
#include <iomanip>

using namespace std;

namespace
{
    constexpr uint32_t Num_of_bits = (1 << 31);

    class Bitset
    {
    public:
        Bitset(size_t n_bits)
            : n_bits_(n_bits)
        {
            n_bytes_ = n_bits / 8 + ( n_bits % 8 ? 1 : 0 );

            bit_rep_.reset(new uint8_t[n_bytes_]);
            fill(bit_rep_.get(), bit_rep_.get() + n_bytes_, 0);
        }

        size_t get_n_bytes() const
        {
            return n_bytes_;
        }

        bool get_bit(size_t bit_index) const
        {
            size_t byte_index = bit_index / 8;
            if (byte_index > n_bytes_) {
                return false;
            }
            return ( bit_rep_[byte_index] & (1 << (bit_index % 8)) ? true : false );
        }

        void set_bit(size_t bit_index)
        {
            size_t byte_index = bit_index / 8;
            if (byte_index > n_bytes_) {
                return;
            }
            bit_rep_[byte_index] |= (1 << (bit_index % 8));
        }

        uint8_t* get_raw_ptr() const
        {
            return bit_rep_.get();
        }

    private:
        size_t n_bits_ = 0;
        size_t n_bytes_ = 0;
        unique_ptr<uint8_t[]> bit_rep_ = nullptr;
    };

    uint64_t modulo(uint64_t value, uint64_t base)
    {
//        return (value - (uint64_t)(value / base) * base);
        return value & (base - 1);
    }
}

ostream& operator<<(ostream& os, const Bitset& b)
{
    uint8_t* raw_ptr = b.get_raw_ptr();
    for (int byte = b.get_n_bytes() - 1 ; byte >= 0; --byte) {
        os << hex << setw(2) << setfill('0') << +raw_ptr[byte] << " ";
    }
    os << dec;
    return os;
}

int main() {

    Bitset bitset_array(Num_of_bits);

    long long N = 0, S = 0, P = 0, Q = 0;

    cin >> N >> S >> P >> Q;

    long long prev_value = S & (0x7fffffff);
    long long curr_value = 0;
    size_t n_distinct_values = 0;
    for (size_t i = 0; i < N; ++i) {
        if (i == 0)
            curr_value = prev_value;
        else
//            curr_value = ((prev_value * P) + Q) % (long long)Num_of_bits;
            curr_value = (long long)((long long)((long long)(prev_value * P) + Q) & (long long)(0x7fffffff));
        cout << "curr value: " << curr_value << endl;
        if (bitset_array.get_bit(curr_value)==false) {
            ++n_distinct_values;
            bitset_array.set_bit(curr_value);
        }
        else {
            if (n_distinct_values > 0)
                --n_distinct_values;
        }
        prev_value = curr_value;
    }
    cout << n_distinct_values << endl;

    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp 3::Bit Array: XOR solution from discussions
// ---------------------------------------------------------------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long Int;

int main() {
    ios::sync_with_stdio(0);
    Int n, s, p, q, a, b;
    cin >> n >> s >> p >> q;
    a =  s & 0x7fffffff;
    Int cnt = 1;
    for(Int i = 1; i < n; ++i) {
        b = a*p+q;
        b &= 0x7fffffff;
        if(a^b)
            cnt++;
        a = b;
    }
    cout << cnt;
    return 0;
}
