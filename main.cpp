// -------------------------------------------------------------------------------------------------------
// Dynamic Programming
// -------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Longest Increasing Subsequence

//    Given a sequence, find the length of the longest increasing subsequence from a given sequence .
//    The longest increasing subsequence means to find a subsequence of a given sequence in which the subsequence's elements are in sorted order, lowest
//    to highest, and in which the subsequence is as long as possible. This subsequence is not necessarily contiguous, or unique.
//    Note: Duplicate numbers are not counted as increasing subsequence.
//    For example:
//     length of LIS for
//    { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is {10, 22, 33, 50, 60, 80}.
//    Input:
//    The first line contains an integer T, depicting total number of test cases.
//    Then following T lines contains an integer N depicting the size of array and next line followed by the value of array.
//    Output:
//    Print the Max length of the subsequence in a separate line.
//    Constraints:
//    1 ≤ T ≤ 100
//    1 ≤ N ≤ 1000
//    0 ≤ A[i] ≤ 300
//    Example:
//    Input
//    1
//    16
//    0 8 4 12 2 10 6 14 1 9 5 13 3 11 7 15
//    Output
//    6

// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        size_t input_size = nums.size();
        if (!input_size)
            return 0;
        if (input_size == 1)
            return 1;

        vector<int> lis_results(input_size, 0);
        int lis_length = 1;
        lis_results[0] = 1;

        for (int i = 1; i < input_size; ++i) {
            if (nums[i] == nums[i-1]) {
                lis_results[i] = lis_results[i-1];
                continue;
            }
            int lis_max = 1;
            for (int j = i - 1; j >= 0; --j) {
                if (nums[j] < nums[i]) {
                    lis_max = max(lis_max, lis_results[j] + 1);
                }
            }
            lis_results[i] = lis_max;
            lis_length = max(lis_length, lis_max);
        }
        return lis_length;
    }
};

int main() {

    int n_testcases = 0;
    cin >> n_testcases;

    int array_size = 0;
    int elem = 0;
    vector<int> input_array;
    Solution s;
    for (int test = 0; test < n_testcases; ++test) {
        cin >> array_size;
        vector<int> input_array;
        for (int elem_idx = 0; elem_idx < array_size; ++elem_idx) {
            cin >> elem;
            input_array.push_back(elem);
        }
        cout << s.lengthOfLIS(input_array) << endl;
    }

    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Binomial Coefficient

//    Find nCr for given n and r.
//    Input:
//    First line contains no of test cases T, for every test case 2 integers as inputs (n,r).
//    Output:
//    Compute and print the value in seperate line. Modulus your output to 10^9+7. If n
//    Constraints:
//    1<=T<=50
//    1<=n<=1000
//    1<=r<=800
//    Example:
//    Input:
//    1
//    3 2
//    Output:
//    3
// -------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Brute force solution
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
using namespace std;

int bin_coeff(int n, int r)
{
    if (r > n) return 0;
    if ((r == 0) || (n == r)) return 1;
    return bin_coeff(n - 1, r - 1) + bin_coeff(n - 1, r);
}

int main() {
    int num_tests = 0;
    cin >> num_tests;
    for (int test = 0; test < num_tests; ++test) {
        int n = 0, r = 0;
        cin >> n >> r;
//        cout << "test " << test << ": n: " << n << ", r: " << r << endl;
//        cout << "binomial coeff: " << bin_coeff(n, r) << endl;
        cout << bin_coeff(n, r) << endl;
    }
    return 0;
}
#endif
#if 0
// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Dynamic programming solution
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
using namespace std;

namespace
{
    constexpr uint64_t Modulo = 1000000007;
}

uint64_t bin_coeff(int n, int r)
{
    if (r > n) return 0;
    if ((r == 0) || (n == r)) return 1;
    // create matrix of solutions
    vector<vector<uint64_t>> solutions(n + 1, vector<uint64_t>(n + 1, 0));
    // initialize matrix of solutions
    for (size_t i = 1; i <= n; ++i) {
        solutions[i][0] = 1;
        solutions[i][i] = 1;
    }
    // main loop
    for (size_t i = 2; i <= n; ++i) {
        for (size_t j = 1; j <= (min((size_t)r, i-1)); ++j) {
            solutions[i][j] = (solutions[i-1][j-1] + solutions[i-1][j]) % Modulo;
        }
    }
    return solutions[n][r];
}

int main() {
    int num_tests = 0;
    cin >> num_tests;
    for (int test = 0; test < num_tests; ++test) {
        int n = 0, r = 0;
        cin >> n >> r;
//        cout << "test " << test << ": n: " << n << ", r: " << r << endl;
//        cout << "binomial coeff: " << bin_coeff(n, r) << endl;
        cout << bin_coeff(n, r) << endl;
    }
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Longest Common Subsequence
//    Given two sequences, find the length of longest subsequence present in both of them. Both the strings are of uppercase.
//    Input:
//    First line of the input contains no of test cases  T,the T test cases follow.
//    Each test case consist of 2 space separated integers A and B denoting the size of string str1 and str2 respectively
//    The next two lines contains the 2 string str1 and str2 .
//    Output:
//    For each test case print the length of longest  common subsequence of the two strings .
//    Constraints:
//    1<=T<=200
//    1<=size(str1),size(str2)<=100
//    Example:
//    Input:
//    2
//    6 6
//    ABCDGH
//    AEDFHR
//    3 2
//    ABC
//    AC
//    Output:
//    3
//    2
//    Explanation
//    LCS for input Sequences “ABCDGH” and “AEDFHR” is “ADH” of length 3.
//    LCS of "ABC" and "AC" is "AC" of length 2
// -------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Dynamic programming solution: GeeksforGeeks submission
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

size_t LCS(const string& x, const string& y)
{
    size_t size_x = x.size(), size_y = y.size();
    if (!size_x || !size_y)
        return 0;
    vector<vector<size_t>> dp_solutions(size_x+1, vector<size_t>(size_y+1, 0));
    for (size_t i=1; i <= size_x; ++i) {
        for (size_t j=1; j <= size_y; ++j) {
            if (x[i-1] == y[j-1])
                dp_solutions[i][j] = dp_solutions[i-1][j-1] + 1;
            else
                dp_solutions[i][j] = max(dp_solutions[i][j-1],dp_solutions[i-1][j]);
        }
    }
    return dp_solutions[size_x][size_y];
}

int main() {
    int num_tests = 0;
    cin >> num_tests;
    for (int test = 0; test < num_tests; ++test) {
        int size1 = 0, size2 = 0;
        string s1, s2;
        cin >> size1 >> size2;
        if (size1)
            cin >> s1;
        if (size2)
            cin >> s2;
        cout << LCS(s1, s2) << endl;
    }
    return 0;
}
#endif
// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Dynamic programming solution: + result reconstruction
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

using Lcs_return_type = pair<size_t, string>;
using Lcs_cell_type = pair<size_t, size_t>;

struct Lcs_solution_rec
{
    size_t length_ = 0;
    Lcs_cell_type route_;
};

Lcs_return_type LCS(const string& x, const string& y)
{
    size_t size_x = x.size(), size_y = y.size();
    if (!size_x || !size_y)
        return {0, ""};
    vector<vector<Lcs_solution_rec>> dp_solutions(size_x+1, vector<Lcs_solution_rec>(size_y+1, Lcs_solution_rec()));
    for (size_t i = 1; i <= size_x; ++i) {
        for (size_t j = 1; j <= size_y; ++j) {
            if (x[i-1] == y[j-1]) {
                dp_solutions[i][j].length_ = dp_solutions[i-1][j-1].length_ + 1;
                dp_solutions[i][j].route_ = {i-1, j-1};
            }
            else {
                if (dp_solutions[i][j-1].length_ > dp_solutions[i-1][j].length_) {
                    dp_solutions[i][j].length_ = dp_solutions[i][j-1].length_;
                    dp_solutions[i][j].route_ = {i, j-1};
                }
                else {
                    dp_solutions[i][j].length_ = dp_solutions[i-1][j].length_;
                    dp_solutions[i][j].route_ = {i-1, j};
                }
            }

        }
    }
    string lcs_result;
    for (size_t i = size_x, j = size_y; i > 0 && j > 0; ) {
        if (x[i-1] == y[j-1])
            lcs_result.insert(0, 1, x[i-1]);
        Lcs_solution_rec solution = dp_solutions[i][j];
        i = solution.route_.first;
        j = solution.route_.second;
    }
    return {dp_solutions[size_x][size_y].length_, lcs_result};
}

int main() {
    int num_tests = 0;
    cin >> num_tests;
    for (int test = 0; test < num_tests; ++test) {
        int size1 = 0, size2 = 0;
        string s1, s2;
        cin >> size1 >> size2;
        if (size1)
            cin >> s1;
        if (size2)
            cin >> s2;
        cout << "test " << test << ": s1: " << s1 << ", s2: " << s2 << endl;
        Lcs_return_type result = LCS(s1, s2);
        cout << "LCS length: " << result.first << ", result: " << result.second << endl;
    }
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Longest Repeating Subsequence
//    Given a string str, find length of the longest repeating subseequence such that the two subsequence don’t have same string character at same position, i.e., any i’th character in the two subsequences shouldn’t have the same index in the original string.
//    Input:
//    The first line of input contains an integer T denoting the number of test cases. Then T test cases follow. The first line of each test case contains an integer N denoting the length of string str.
//    The second line of each test case contains the string str consisting only of lower case english alphabets.
//    Output:
//    Print the length of the longest repeating subsequence for each test case in a new line.
//    Constraints:
//    1<= T <=100
//    1<= N <=1000
//    Example:
//    Input:
//    2
//    3
//    abc
//    5
//    axxxy
//    Output:
//    0
//    2
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <string>
#include <vector>
using namespace std;

size_t LRS(const string& x)
{
    size_t size_x = x.size();
    if (!size_x)
        return 0;
    vector<vector<size_t>> dp_solutions(size_x+1, vector<size_t>(size_x+1, 0));
    for (size_t i=1; i <= size_x; ++i) {
        for (size_t j=1; j <= size_x; ++j) {
            if ((x[i-1] == x[j-1]) && (i != j))
                dp_solutions[i][j] = dp_solutions[i-1][j-1] + 1;
            else
                dp_solutions[i][j] = max(dp_solutions[i][j-1],dp_solutions[i-1][j]);
        }
    }
    return dp_solutions[size_x][size_x];
}

int main() {
    int num_tests = 0;
    cin >> num_tests;
    for (int test = 0; test < num_tests; ++test) {
        int size1 = 0;
        string s1;
        cin >> size1;
        if (size1)
            cin >> s1;
        cout << LRS(s1) << endl;
    }
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Largest Sum Contiguous Subarray
//    Given an array containing both negative and positive integers. Find the contiguous sub-array with maximum sum.
//    Input:
//    The first line of input contains an integer T denoting the number of test cases. The description of T test cases follows. The first line of each test case contains a single integer N denoting the size of array. The second line contains N space-separated integers A1, A2, ..., AN denoting the elements of the array.
//    Output:
//    Print the maximum sum of the contiguous sub-array in a separate line for each test case.
//    Constraints:
//    1 ≤ T ≤ 200
//    1 ≤ N ≤ 1000
//    -100 ≤ A[i] <= 100
//    Example:
//    Input
//    2
//    3
//    1 2 3
//    4
//    -1 -2 -3 -4
//    Output
//    6
//    -1
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
using namespace std;

int main() {
    //code
    return 0;
}
#endif


// -------------------------------------------------------------------------------------------------------
// Greedy
// -------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------------------
// N meetings in one room (Activity Selection problem)
//    There is one meeting room in Flipkart. There are n meetings in the form of (S [ i ], F [ i ]) where S [ i ] is start time of meeting i and F [ i ] is finish time of meeting i
//    What is the maximum number of meetings that can be accommodated in the meeting room ?
//    Input:
//    The first line of input consists number of the test cases. The description of T test cases is as follows:
//    The first line consists of the size of the array, second line has the array containing the starting time of all the meetings each separated by a space, i.e., S [ i ]. And the third line has the array containing the finishing time of all the meetings each separated by a space, i.e., F [ i ].
//    Output:
//    In each separate line print the order in which the meetings take place separated by a space.
//    Constraints:
//    1 ≤ T ≤ 70
//    1 ≤ N ≤ 100
//    1 ≤ S[ i ], F[ i ] ≤ 100000
//    Example:
//    Input:
//    2
//    6
//    1 3 0 5 8 5
//    2 4 6 7 9 9
//    8
//    75250 50074 43659 8931 11273 27545 50879 77924
//    112960 114515 81825 93424 54316 35533 73383 160252
//    Output:
//    1 2 4 5
//    6 7 1
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Meeting
{
    int start_ = 0;
    int finish_ = 0;
    size_t index_ = 0;
};

using Meetings = vector<Meeting>;
using Result = vector<size_t>;

ostream& operator<<(ostream& os, const Meeting& m)
{
    os << "[" << m.start_ << "," << m.finish_ << "," << m.index_ << "]";
    return os;
}

ostream& operator<<(ostream& os, const Meetings& meetings)
{
    for (auto m: meetings) {
        os << m << " ";
    }
    return os;
}

ostream& operator<<(ostream& os, const Result& results)
{
    for (int i=0; i < results.size(); ++i) {
        os << results[i];
        if (i != results.size()-1)
            os << " ";
    }
    return os;
}

// algorithm for activity selection: based on Greedy algorithm:
// sort meetings by finish date acsending, each loop select first
// one to finish meeting, starting after current one finishes
int activity_selection_algo(Meetings meetings, Result& result)
{
    // sort by meeting finish ascending
    sort(meetings.begin(), meetings.end(), [](const Meeting& m1, const Meeting& m2){ return m1.finish_ < m2.finish_; });
//    cout << "sorted: " << meetings << endl;
    int max_meetings = 0;
    for (auto i = meetings.begin(); i != meetings.end(); ) {
        // add current meeting to results
        result.push_back(i->index_);
        ++max_meetings;
        // find first meeting starting later than current finishes
        auto j = i + 1;
        for (; (j != meetings.end()) && (j->start_ < i->finish_); ++j);
        i = j;
    }
//    cout << "max: " << max_meetings << endl;
//    cout << "results: " << result << endl;

    return 0;
}

int main() {
    size_t n_tests = 0;
    cin >> n_tests;
    for (size_t t = 0; t < n_tests; ++t) {
        size_t n_meetings = 0;
        cin >> n_meetings;
        Meetings meetings(n_meetings);
        for (size_t i = 0; i < n_meetings; ++i) {
            cin >> meetings[i].start_;
            meetings[i].index_ = i + 1;
        }
        for (size_t i = 0; i < n_meetings; ++i) {
            cin >> meetings[i].finish_;
        }
        Result result;
        int max_meetings = activity_selection_algo(meetings, result);
        cout << result << endl;
    }
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------
// Bit Array
// -------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <bitset>

using namespace std;

int main() {

    {
        bitset<1024> bits;
        cout << "size of bitset<1024>: " << sizeof(bits) << endl;
    }

    {
        uint16_t value = 0x5555;
        bitset<16> bits(value);
        cout << hex << "value " << value << " in binary: " << bits << endl;
        cout << "bit 0: " << bits[0] << endl;
        cout << "bit 1: " << bits[1] << endl;
        cout << "bit 2: " << bits[2] << endl;
        cout << "bit 3: " << bits[3] << endl;
        cout << "total bits: " << dec << bits.size() << ", n of 1s: " << bits.count() << ", n of 0s: " << bits.size() - bits.count() << endl;
    }

    {
        cout << "decimal of 111: " << bitset<8>("111").to_ulong() << endl;
    }

    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------
// Find Duplicates of array using bit array
//    You have an array of N numbers, where N is at most 32,000. The array may have duplicates entries and you do not know what N is.
//    With only 4 Kilobytes of memory available, how would print all duplicates elements in the array ?.
//    Examples:
//    Input : arr[] = {1, 5, 1, 10, 12, 10}
//    Output : 1 10
//    1 and 10 appear more than once in given
//    array.
//    Input : arr[] = {50, 40, 50}
//    Output : 50
// -------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <bitset>

using namespace std;

namespace
{
    constexpr size_t NUM_OF_BITS = 1024 * 4 * 8;
}

int main() {

    size_t N = 0;
    cin >> N;
    if (N > NUM_OF_BITS) {
        cout << "N is too large: " << N << endl;
        return -1;
    }


    bitset<NUM_OF_BITS> bitset_array;
    for (size_t i = 0; i < N; ++i) {
        int input_value = 0;
        cin >> input_value;
        if (bitset_array[input_value]) {
            cout << input_value << " ";
        }
        else
            bitset_array.set(input_value);
    }
    cout << endl;

    return 0;
}
#endif
