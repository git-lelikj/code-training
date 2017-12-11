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
