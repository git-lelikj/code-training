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
#if 0
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
#endif
#if 0
// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp Sept 2015::Classes and Objects
// ---------------------------------------------------------------------------------------------------------------------------------------
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <array>
#include <numeric>
using namespace std;

class Student
{
public:
    constexpr static const size_t N_SCORES = 5;

    void input()
    {
        for (auto& score: scores) {
            cin >> score;
        }
    }

    int calculateTotalScore()
    {
        return accumulate(scores.begin(), scores.end(), 0);
    }

private:
    array<int, N_SCORES> scores;
};

int main() {
    int n; // number of students
    cin >> n;
    Student *s = new Student[n]; // an array of n students

    for(int i = 0; i < n; i++){
        s[i].input();
    }

    // calculate kristen's score
    int kristen_score = s[0].calculateTotalScore();
    cout << kristen_score << " ";

    // determine how many students scored higher than kristen
    int count = 0;
    for(int i = 1; i < n; i++){
        int total = s[i].calculateTotalScore();
        cout << total << " ";
        if(total > kristen_score){
            count++;
        }
    }
    cout << endl;

    // print result
    cout << count << endl;

    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp Sept 2015::C++ Class Templates
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

template<typename T>
class AddElements
{
public:
    AddElements(const T& e)
        : element_(e)
    {}

    T add(const T& e)
    {
        element_ += e;
        return element_;
    }

private:
    T element_;
};

template<>
class AddElements<string>
{
public:
    AddElements(const string& s)
        : element_(s)
    {}

    string concatenate(const string& s)
    {
        element_ += s;
        return element_;
    }

private:
    string element_;
};

int main () {
  int n,i;
  cin >> n;
  for(i=0;i<n;i++) {
    string type;
    cin >> type;
    if(type=="float") {
        double element1,element2;
        cin >> element1 >> element2;
        AddElements<double> myfloat (element1);
        cout << myfloat.add(element2) << endl;
    }
    else if(type == "int") {
        int element1, element2;
        cin >> element1 >> element2;
        AddElements<int> myint (element1);
        cout << myint.add(element2) << endl;
    }
    else if(type == "string") {
        string element1, element2;
        cin >> element1 >> element2;
        AddElements<string> mystring (element1);
        cout << mystring.concatenate(element2) << endl;
    }
  }
  return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Competitions::Code.cpp Sept 2015::Rectangle Area
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>

using namespace std;

class Rectangle
{
public:
    virtual void display()
    {
        cout << width_ << " " << height_ << endl;
    }

protected:
    int width_ = 0;
    int height_ = 0;
};

class RectangleArea: public Rectangle
{
public:
    void read_input()
    {
        cin >> width_ >> height_;
    }

    void display()
    {
        cout << width_ * height_ << endl;
    }
};

int main()
{
    /*
     * Declare a RectangleArea object
     */
    RectangleArea r_area;

    /*
     * Read the width and height
     */
    r_area.read_input();

    /*
     * Print the width and height
     */
    r_area.Rectangle::display();

    /*
     * Print the area
     */
    r_area.display();

    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: 2D Array - DS

//    Input Format
//    Each of the  lines of inputs  contains  space-separated integers .
//    Constraints
//    Output Format
//    Print the largest (maximum) hourglass sum found in .

//    Sample Input
//    1 1 1 0 0 0
//    0 1 0 0 0 0
//    1 1 1 0 0 0
//    0 0 2 4 4 0
//    0 0 0 2 0 0
//    0 0 1 2 4 0

//    Sample Output
//    19
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>
#include <limits>

using namespace std;

int hourglass(vector<vector<int>> arr, size_t i, size_t j) {
    if ((i < 0) || (i > 3) || (j < 0) || (j > 3))
        return -1;
    return (
        arr[i][j] + arr[i][j+1] + arr[i][j+2] +
        arr[i+1][j+1] +
        arr[i+2][j] + arr[i+2][j+1] + arr[i+2][j+2]
    );
}

// Complete the hourglassSum function below.
int hourglassSum(vector<vector<int>> arr) {
    int max_sum = numeric_limits<int>::min();
    for (size_t i = 0; i <= 3; ++i)
        for (size_t j = 0; j <= 3; ++j) {
            int sum = hourglass(arr, i, j);
            max_sum = max(max_sum, sum);
        }
    return max_sum;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> arr(6);
    for (int i = 0; i < 6; i++) {
        arr[i].resize(6);

        for (int j = 0; j < 6; j++) {
            cin >> arr[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int result = hourglassSum(arr);

    fout << result << "\n";

    fout.close();

    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Arrays: Left Rotation

//    Sample Input
//    5 4
//    1 2 3 4 5

//    Sample Output
//    5 1 2 3 4
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
#if 0
vector<int> rotLeft(vector<int> a) {
    int top = a[0];
    move(++a.begin(), a.end(), a.begin());
    a[a.size()-1] = top;
    return a;
}

// Complete the rotLeft function below.
vector<int> rotLeft(vector<int> a, int d) {
    if ((d <= 0) || (!a.size()) || (d == a.size()))
        return a;
    for (size_t i = 0; i < d; ++i)
        a = rotLeft(a);
    return a;
}
#endif

// Complete the rotLeft function below.
vector<int> rotLeft(vector<int> a, int d) {
    if ((d <= 0) || (!a.size()))
        return a;
    int new_first = d % a.size();
    if (!new_first)
        return a;
    rotate(a.begin(), a.begin()+new_first, a.end());
    return a;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split_string(a_temp_temp);

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    vector<int> result = rotLeft(a, d);

    for (int i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << " ";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Arrays: New Year Chaos

//    Sample Input
//    2
//    5
//    2 1 5 3 4
//    5
//    2 5 1 3 4

//    Sample Output
//    3
//    Too chaotic

// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the minimumBribes function below.
void minimumBribes(vector<int> q) {
    if (!q.size()) {
        cout << "0\n";
        return;
    }
    for (int i = 0; i < q.size(); ++i) {
        if (q[i] - (i + 1) > 2) {
            cout << "Too chaotic\n";
            return;
        }
    }
    int result = 0;
    for (int i = 0; i < q.size() - 1; ++i) {
        bool stop = true;
        for (int j = 0; j < q.size() - 1 - i; ++j) {
            if (q[j] > q[j+1]) {
                swap(q[j], q[j+1]);
                ++result;
                stop = false;
            }
        }
        if (stop)
            break;
    }
    cout << result << endl;
}

int main()
{
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Arrays: Minimum Swaps 2

//    Sample Input 0

//    4
//    4 3 1 2
//    Sample Output 0

//    3

// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);
#if 0
int partition(vector<int>& arr, int lo, int hi, int& n_swaps)
{
    int pivot = arr[hi];
    int i = lo - 1;
    for (int j = lo; j <= hi - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
            if (i != j)
                ++n_swaps;
        }
    }
    ++i;
    swap(arr[i], arr[hi]);
    if (i != hi)
        ++n_swaps;
    return i;
}

int quickSort(vector<int>& arr, int lo, int hi)
{
    int n_swaps = 0;
    if (hi <= lo)
        return 0;
    int p = partition(arr, lo, hi, n_swaps);
    n_swaps += quickSort(arr, lo, p - 1);
    n_swaps += quickSort(arr, p + 1, hi);
    return n_swaps;
}

// Complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {
    if (!arr.size())
        return 0;
    else
        return quickSort(arr, 0, arr.size() - 1);
}
#endif

// Complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {
    if (arr.size() <= 1)
        return 0;
    else {
        int swaps = 0;
        for (size_t i = 0; i < arr.size(); ++i) {
            if ((arr[i] <= 0) || (arr[i] > arr.size()))
                continue;
            while (arr[i] != i + 1) {
                swap(arr[i], arr[arr[i] - 1]);
                ++swaps;
            }
        }
        return swaps;
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split_string(arr_temp_temp);

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    int res = minimumSwaps(arr);

    fout << res << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Arrays: Array Manipulation

//    Starting with a 1-indexed array of zeros and a list of operations, for each operation add a value to each of the array element between two given indices, inclusive. Once all operations have been performed, return the maximum value in your array.

//    For example, the length of your array of zeros . Your list of queries is as follows:

//        a b k
//        1 5 3
//        4 8 7
//        6 9 1
//    Add the values of  between the indices  and  inclusive:

//    index->	 1 2 3  4  5 6 7 8 9 10
//        [0,0,0, 0, 0,0,0,0,0, 0]
//        [3,3,3, 3, 3,0,0,0,0, 0]
//        [3,3,3,10,10,7,7,7,0, 0]
//        [3,3,3,10,10,8,8,8,1, 0]
//    The largest value is  after all operations are performed.

// ---------------------------------------------------------------------------------------------------------------------------------------

// Note: this solution is no-op, too complicated, see discussion for optimal solution
#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

struct Range
{
    int start_ = 0;
    int end_ = 0;
    int len_ = 0;
    u_int weight_ = 0;

    Range(int start, int end, int weight):
        start_(start), end_(end), weight_(weight)
    {
        len_ = (end_ > start_ ? (end_ - start_ + 1) : 0);
    }

};

bool operator<(const Range& l, const Range& r)
{
    return l.start_ < r.start_;
}

ostream& operator<<(ostream& os, const Range& r)
{
    os << "[" << r.start_ << ":" << r.end_ << "," << r.len_ << "," << r.weight_ << "]";
    return os;
}

using Ranges = set<Range>;

vector<Ranges::iterator> get_intersection(const Ranges& ranges, const Range& range)
{
    vector<Ranges::iterator> result;
    auto ins_point = ranges.equal_range(range);
//    if (ins_point.first == ranges.begin())
//        return result;
//    if (ins_point.first == ranges.end()) {
//        result.push_back(--ins_point.first);
//    }
//    else {
        auto it = (ins_point.first->start_ == range.start_ ? ins_point.first : --(ins_point.first) );
//        cout << "[get_intersection]: it start: " << *it << endl;
        for (;
             (it != ranges.end()) &&
             (it->start_ <= range.end_)
             ;
             ++it) {
            if (range.start_ <= it->end_ ) {
//                cout << "[get_intersection]: push it: " << *it << endl;
                result.push_back(it);
            }
//        }
    }
    return result;
}

// Complete the arrayManipulation function below.
long arrayManipulation(int n, vector<vector<int>> queries) {
    Ranges ranges;
    ranges.insert(Range(0, n - 1, 0));
    long result_weight = 0;
    for (const auto& q: queries) {
        Range r(q[0]-1, q[1]-1, q[2]);
        auto inter = get_intersection(ranges, r);

        cout << "[arrayManipulation]: ranges: ";
        for (const auto& r: ranges)
            cout << r << " ";
        cout << endl;

        cout << "[arrayManipulation]: input range: " << r << endl;

        cout << "[arrayManipulation]: intersection: ";
        for (const auto& i: inter)
            cout << *i << " ";
        cout << endl;

        vector<Range> inter_replace;
        for (auto& i: inter) {
            if (i->start_ >= r.start_ && i->end_ <= r.end_) {
                Range r1(i->start_, i->end_, i->weight_ + r.weight_);
                inter_replace.push_back(r1);
                result_weight = max(result_weight, (long)(i->weight_ + r.weight_));
            }
            else if (i->start_ < r.start_ && i->end_ <= r.end_) {
                Range r1(i->start_, r.start_ - 1, i->weight_);
                Range r2(r.start_, i->end_, i->weight_ + r.weight_);
                inter_replace.push_back(r1);
                inter_replace.push_back(r2);
                result_weight = max(result_weight, (long)(i->weight_ + r.weight_));
            }
            else if (i->start_ == r.start_ && i->end_ > r.end_) {
                Range r1(i->start_, r.end_, i->weight_ + r.weight_);
                Range r2(r.end_ + 1, i->end_, i->weight_);
                inter_replace.push_back(r1);
                inter_replace.push_back(r2);
                result_weight = max(result_weight, (long)(i->weight_ + r.weight_));
            }
            else if (i->start_ > r.start_ && i->end_ > r.end_) {
                Range r1(i->start_, r.end_, i->weight_ + r.weight_);
                Range r2(r.end_ + 1, i->end_, i->weight_);
                inter_replace.push_back(r1);
                inter_replace.push_back(r2);
                result_weight = max(result_weight, (long)(i->weight_ + r.weight_));
            }
            else if (i->start_ < r.start_ && i->end_ == r.end_) {
                Range r1(i->start_, r.start_ - 1, i->weight_);
                Range r2(r.start_, i->end_, i->weight_ + r.weight_);
                inter_replace.push_back(r1);
                inter_replace.push_back(r2);
                result_weight = max(result_weight, (long)(i->weight_ + r.weight_));
            }
            else if (i->start_ < r.start_ && i->end_ > r.end_) {
                Range r1(i->start_, r.start_ - 1, i->weight_);
                Range r2(r.start_, r.end_, i->weight_ + r.weight_);
                Range r3(r.end_ + 1, i->end_, i->weight_);
                inter_replace.push_back(r1);
                inter_replace.push_back(r2);
                inter_replace.push_back(r3);
                result_weight = max(result_weight, (long)(i->weight_ + r.weight_));
            }
        }

        cout << "[arrayManipulation]: intersection replacement: ";
        for (const auto& i: inter_replace)
            cout << i << " ";
        cout << endl;

        for (auto& i: inter)
            ranges.erase(i);

        for (auto& i: inter_replace)
            ranges.insert(i);
    }

    return result_weight;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nm_temp;
    getline(cin, nm_temp);

    vector<string> nm = split_string(nm_temp);

    int n = stoi(nm[0]);

    int m = stoi(nm[1]);

    vector<vector<int>> queries(m);
    for (int i = 0; i < m; i++) {
        queries[i].resize(3);

        for (int j = 0; j < 3; j++) {
            cin >> queries[i][j];
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    long result = arrayManipulation(n, queries);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Hash Tables: Ransom Note

//    Sample Input 0
//    6 4
//    give me one grand today night
//    give one grand today

//    Sample Output 0
//    Yes

// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the checkMagazine function below.
void checkMagazine(vector<string> magazine, vector<string> note) {
    unordered_multiset<string> magazine_hash;
    for (const auto& s: magazine)
        magazine_hash.insert(s);
    for (const auto& s: note) {
        auto it = magazine_hash.find(s);
        if (it != magazine_hash.end())
            magazine_hash.erase(it);
        else {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    return;
}

int main()
{
    string mn_temp;
    getline(cin, mn_temp);

    vector<string> mn = split_string(mn_temp);

    int m = stoi(mn[0]);

    int n = stoi(mn[1]);

    string magazine_temp_temp;
    getline(cin, magazine_temp_temp);

    vector<string> magazine_temp = split_string(magazine_temp_temp);

    vector<string> magazine(m);

    for (int i = 0; i < m; i++) {
        string magazine_item = magazine_temp[i];

        magazine[i] = magazine_item;
    }

    string note_temp_temp;
    getline(cin, note_temp_temp);

    vector<string> note_temp = split_string(note_temp_temp);

    vector<string> note(n);

    for (int i = 0; i < n; i++) {
        string note_item = note_temp[i];

        note[i] = note_item;
    }

    checkMagazine(magazine, note);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Hash Tables: Two Strings

//    Sample Input

//    2
//    hello
//    world
//    hi
//    world
//    Sample Output

//    YES
//    NO

// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>

using namespace std;

// Complete the twoStrings function below.
string twoStrings(string s1, string s2) {
    array<size_t, 255> letter_count = {};
    for (auto c: s1)
        ++letter_count[static_cast<size_t>(c)];
    for (auto c: s2) {
        if (letter_count[static_cast<size_t>(c)]) {
            return "YES";
        }
    }
    return "NO";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s1;
        getline(cin, s1);

        string s2;
        getline(cin, s2);

        string result = twoStrings(s1, s2);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Hash Tables: Sherlock and Anagrams

//    Sample Input 0
//    2
//    abba
//    abcd
//    Sample Output 0
//    4
//    0

//    Sample Input 1
//    2
//    ifailuhkqq
//    kkkk
//    Sample Output 1
//    3
//    10

//    Sample Input 2
//    1
//    cdcd
//    Sample Output 2
//    5

// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>
#include <boost/functional/hash.hpp>

using namespace std;

using Histogram = array<size_t, 26>;

struct Record
{
    int i_ = 0;
    double d_ = .0;
    string s_;
    Record(int i, double d, string s):
        i_(i), d_(d), s_(s)
    {}
};

bool operator==(const Record& l, const Record& r)
{
    return l.i_ == r.i_;
}

namespace std
{
    template<> struct hash<Record>
    {
        size_t operator()(const Record& r) const
        {
            size_t seed = 0;
            boost::hash_combine(seed, r.i_);
            boost::hash_combine(seed, r.d_);
            boost::hash_combine(seed, r.s_);
            return seed;
        }
    };
}
#if 0
struct Record_hash
{
    size_t operator()(const Record& r) const
    {
        return 0;
    }
};

struct Record_equal
{
    bool operator()(const Record& l, const Record& r) const
    {
        return l.i_ == r.i_;
    }
};
#endif
// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {

    if (!s.size())
        return 0;
#if 0
    // standalone fo hash/equal
    unordered_map<Record, int, Record_hash, Record_equal> rec_map;
    rec_map.insert({Record(1, 3.14, "abc"), 0});
    rec_map.insert({{1, 3.14, "def"}, 1});
#endif
#if 0
    // standalone lambda hash/equal
    auto hash = [](const Record& r) { return std::hash<int>{}(r.i_); };
    auto equal = [](const Record& l, const Record& r) { return l.i_ == r.i_; };
    unordered_map<Record, int, decltype(hash), decltype(equal)> rec_map(10, hash, equal);
    rec_map.insert({Record(1, 3.14, "abc"), 0});
    rec_map.insert({{1, 3.14, "def"}, 1});
#endif
    // builtin equal/std injected hash
    unordered_map<Record, int> rec_map;
    rec_map.insert({Record(1, 3.14, "abc"), 0});
    rec_map.insert({{1, 3.14, "def"}, 1});
    for (size_t i = 0; i < s.size(); ++i) {
        array<size_t, 26> histogram = {};
        for (size_t j = i; j < s.size() - 1; ++j) {
            ++histogram[s[j]-'a'];
            // TBD: hash histogram and store in hash table
        }
    }
    // TBD:sum all keys of histogram hash table
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
#endif
#if 0
#include <bits/stdc++.h>
#if 0
#include <boost/functional/hash.hpp>
#endif

using namespace std;

using Histogram = array<size_t, 26>;

bool operator==(const Histogram& l, const Histogram& r)
{
    if (l.size() != r.size())
        return false;
    for (size_t i = 0; i < l.size(); ++i)
        if (l[i] != r[i])
            return false;
    return true;
}

ostream& operator<<(ostream& os, const Histogram& h)
{
    for (const auto& e: h)
        os << e << " ";
    return os;
}

namespace Util
{
    template<typename T>
    void hash_combine(size_t& seed, const T& t)
    {
        seed ^= std::hash<T>()(t) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    template<typename It>
    void hash_range(size_t& seed, const It& b, const It& e)
    {
        for (auto it = b; it != e; ++it)
            hash_combine(seed, *it);
    }
}

struct Histogram_hash
{
    size_t operator()(const Histogram& h) const
    {
        size_t seed = h.size();
#if 0
        boost::hash_range(seed, h.begin(), h.end());
#endif
        Util::hash_range(seed, h.begin(), h.end());
        return seed;
    }
};

namespace std
{

template<> struct hash<Histogram>
{
    size_t operator()(const Histogram& h) const
    {
        size_t seed = h.size();
#if 0
        boost::hash_range(seed, h.begin(), h.end());
#endif
        Util::hash_range(seed, h.begin(), h.end());
        return seed;
    }
};

}

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {

    if (!s.size())
        return 0;
    unordered_map<Histogram, size_t> histo_hash;
    for (size_t i = 0; i < s.size(); ++i) {
        array<size_t, 26> histogram = {};
        for (size_t j = i; j < s.size(); ++j) {
            ++histogram[s[j]-'a'];
//            cout << "[]: add histogram: " << histogram << endl;
            ++histo_hash[histogram];
        }
    }
//    cout << "[] histo hash: ";
//    for (const auto& h: histo_hash)
//        cout << "[" << h.first << "," << h.second << "] ";
//    cout << endl;
    int result = 0;
    for (const auto& h: histo_hash) {
        result += h.second * (h.second - 1) / 2;
    }
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Hash Tables: Count Triplets

//    Sample Input 0
//    4 2
//    1 2 2 4
//    Sample Output 0
//    2

//    Sample Input 1
//    6 3
//    1 3 9 9 27 81
//    Sample Output 1
//    6

//    Sample Input 2
//    5 5
//    1 5 5 25 125
//    Sample Output 2
//    4

// ---------------------------------------------------------------------------------------------------------------------------------------

// Note: solution below works i.o. R=1
#if 0
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct Mgm_record
{
    int count_  = 0;
    int count1_ = 0;
    int count2_ = 0;
    Mgm_record(int c, int c1, int c2):
        count_(c), count1_(c1), count2_(c2)
    {}
};

using Triplet_hash = unordered_map<long, Mgm_record>;

// Complete the countTriplets function below.
long countTriplets_impl(vector<long> arr, long r) {
    Triplet_hash triplet_hash;
    long triplet_count = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        auto it = triplet_hash.find(arr[i]);
        if (it == triplet_hash.end()) {
            // add new start of triplet
            triplet_hash.insert({arr[i], Mgm_record(1, 0, 0)});
            triplet_hash.insert({arr[i]*r, Mgm_record(0, 1, 0)});
        }
        else {
            if (it->second.count2_)
                triplet_count += it->second.count2_;
            ++it->second.count_;
            auto it2 = triplet_hash.find(arr[i]*r);
            if (it2 == triplet_hash.end()) {
                // add record for next in sequence
                triplet_hash.insert({arr[i]*r, Mgm_record(0, it->second.count_, it->second.count_* it->second.count1_)});
            }
            else {
                // update next record counters
                it2->second.count1_ = it->second.count_;
                it2->second.count2_ += it->second.count1_;
            }
        }
    }
    return triplet_count;
}

using Triplet_hash1 = unordered_map<long, int>;

long countTriplets_impl1(vector<long> arr, long r) {
    Triplet_hash1 triplet_hash;
    long triplet_count = 0;
    for (size_t i = 0; i < arr.size(); ++i) {
        ++triplet_hash[arr[i]];
    }
    for (const auto& e: triplet_hash) {
        cout << "[countTriplets_impl1]: first: " << e.first << ", second: " << e.second << endl;
        if (e.second < 3)
            continue;
        triplet_count += (e.second > 3 ? ((e.second-2) * (e.second-1))/2 : 1);
    }
    return triplet_count;
}

long countTriplets(vector<long> arr, long r) {
    if (r > 1)
        return countTriplets_impl(arr, r);
    else
        return countTriplets_impl1(arr, r);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nr_temp;
    getline(cin, nr_temp);

    vector<string> nr = split(rtrim(nr_temp));

    int n = stoi(nr[0]);

    long r = stol(nr[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<long> arr(n);

    for (int i = 0; i < n; i++) {
        long arr_item = stol(arr_temp[i]);

        arr[i] = arr_item;
    }

    long ans = countTriplets(arr, r);

    fout << ans << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Hash Tables: Frequency Queries
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

using Data_hash = unordered_map<int, size_t>;
using Count_hash = unordered_map<size_t, size_t>;

void replace_count(Count_hash& hash, size_t old_val, size_t new_val)
{
    auto old_it = hash.find(old_val);
    auto new_it = hash.find(new_val);
    if (old_it != hash.end()) {
        if (old_it->second > 1)
            --(old_it->second);
        else
            hash.erase(old_val);
    }
    if (new_it != hash.end()) {
        ++new_it->second;
    }
    else {
        hash.insert({new_val, 1});
    }
}

// Complete the freqQuery function below.
vector<int> freqQuery(vector<vector<int>> queries) {

    vector<int> results;
    Data_hash data_hash;
    Count_hash count_hash;
    for (auto const& query: queries) {

        cout << "[freqQuery]: data hash: ";
        for (auto e: data_hash) {
            cout << "[" << e.first << "," << e.second << "] ";
        }
        cout << endl;
        cout << "[freqQuery]: count hash: ";
        for (auto e: count_hash) {
            cout << "[" << e.first << "," << e.second << "] ";
        }
        cout << endl;
        if (query[0] == 1) {
            auto it = data_hash.find(query[1]);
            if (it != data_hash.end()) {
                size_t count = it->second;
                ++it->second;
                replace_count(count_hash, count, count + 1);
            }
            else {
                data_hash.insert({query[1], 1});
                ++count_hash[1];
            }
        }
        else if (query[0] == 2) {
            auto it = data_hash.find(query[1]);
            if (it != data_hash.end()) {
                size_t count = it->second;
                if (count > 1) {
                    --it->second;
                    replace_count(count_hash, count, count - 1);
                }
                else {
                    data_hash.erase(query[1]);
                    if (count_hash[1] > 1)
                        --count_hash[1];
                    else
                        count_hash.erase(1);
                }
            }
        }
        else if (query[0] == 3) {
            auto it = count_hash.find(query[1]);
            int result = ( it != count_hash.end() ? 1 : 0 );
            results.push_back(result);
        }
    }
    return results;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++) {
        queries[i].resize(2);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> ans = freqQuery(queries);

    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i];

        if (i != ans.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Sorting: Bubble Sort
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the countSwaps function below.
void countSwaps(vector<int> a) {

    size_t swaps = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a.size() - 1; ++j)
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                ++swaps;
            }
    }
    cout << "Array is sorted in " << swaps << " swaps\n";
    cout << "First Element: " << (a.size() ? a[0] : 0) << endl;
    cout << "Last element: " << (a.size() ? a[a.size() - 1] : 0) << endl;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split_string(a_temp_temp);

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    countSwaps(a);

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Sorting: Mark and Toys
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the maximumToys function below.
int maximumToys(vector<int> prices, int k) {
    int toys = 0;
    sort(prices.begin(), prices.end());
    int sum = 0;
    for (auto p: prices) {
        sum += p;
        if (sum <= k)
            ++toys;
        else
            break;
    }
    return toys;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string prices_temp_temp;
    getline(cin, prices_temp_temp);

    vector<string> prices_temp = split_string(prices_temp_temp);

    vector<int> prices(n);

    for (int i = 0; i < n; i++) {
        int prices_item = stoi(prices_temp[i]);

        prices[i] = prices_item;
    }

    int result = maximumToys(prices, k);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Sorting: Comparator
// ---------------------------------------------------------------------------------------------------------------------------------------
#if 0
class Checker{
public:
    // complete this method
    static int comparator(Player a, Player b)  {
        if (a.score < b.score)
            return -1;
        if (a.score > b.score)
            return 1;
        return ( a.name > b.name ? -1 : 1 );
    }
};
#endif

// ---------------------------------------------------------------------------------------------------------------------------------------
//    Interview prep: Sorting: Comparator
// ---------------------------------------------------------------------------------------------------------------------------------------
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

template <typename It>
double median(It begin, It end)
{
    double result = 0;
    sort(begin, end);
    //TBD
    return result;
}

// Complete the activityNotifications function below.
int activityNotifications(vector<int> expenditure, int d) {
    size_t n = expenditure.size();
    if (n <= d)
        return 0;
    auto wb = expenditure.begin();
    auto we = wb + d;
    for (size_t i = 0;
         i < (n - d);
         ++i, ++wb, ++we) {
        vector<int> temp;
        copy(wb, we, back_inserter(temp));
        cout << "[activityNotifications]: temp: ";
        for (auto e: temp)
            cout << e << " ";
        cout << endl;
//        double med = median();
    }
    return 0;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string nd_temp;
    getline(cin, nd_temp);

    vector<string> nd = split_string(nd_temp);

    int n = stoi(nd[0]);

    int d = stoi(nd[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split_string(expenditure_temp_temp);

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    fout << result << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
