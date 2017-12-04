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
