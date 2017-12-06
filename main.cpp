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
#include <iostream>
using namespace std;

int main() {
    //code
    return 0;
}
