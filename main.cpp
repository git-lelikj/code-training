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
//    Given a string str, find length of the longest repeating subseequence such that the two subsequence dont have same string character at same position, i.e., any ith character in the two subsequences shouldnt have the same index in the original string.
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
// Largest Sum Contiguous Subarray (Kadane's Algorithm)
//    Given an array containing both negative and positive integers. Find the contiguous sub-array with maximum sum.
//    Input:
//    The first line of input contains an integer T denoting the number of test cases. The description of T test cases follows.
//    The first line of each test case contains a single integer N denoting the size of array.
//    The second line contains N space-separated integers A1, A2, ..., AN denoting the elements of the array.
//    Output:
//    Print the maximum sum of the contiguous sub-array in a separate line for each test case.
//    Constraints:
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
#include <vector>
#include <algorithm>
using namespace std;

vector<int> input_array(size_t num_elements)
{
    vector<int> a(num_elements, 0);
    for (size_t i = 0; i < num_elements; ++i) {
        cin >> a[i];
    }
    return a;
}

int max_subarray_sum(const vector<int>& a)
{
    if (!a.size())
        return 0;
    int max_ending_here = a[0];
    int max_total = a[0];
    for (size_t i = 1; i < a.size(); ++i) {
        max_ending_here = max(a[i], a[i] + max_ending_here);
        max_total = max(max_total, max_ending_here);
    }
    return max_total;
}

int main()
{
    size_t T = 0;
    cin >> T;
    for (size_t t = 0; t < T; ++t) {
        size_t N = 0;
        cin >> N;
        vector<int> a = input_array(N);
        cout << max_subarray_sum(a) << endl;
    }
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// 0 - 1 Knapsack Problem
//    You are given weights and values of N items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
//    Note that we have only one quantity of each item, In other words, given two integer arrays val[0..N-1] and wt[0..N-1] which represent values and
//    weights associated with N items respectively. Also given an integer W which represents knapsack capacity,
//    find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W.
//    You cannot break an item, either pick the complete item, or dont pick it (0-1 property).
//    Input:
//    The first line of input contains an integer T denoting the number of test cases. Then T test cases follow. Each test case consists of four lines.
//    The first line consists of N the number of items. The second line consists of W, the maximum capacity of the knapsack. In the next  line are N space
//    separated positive integers denoting the values of the N items and in the fourth line are N space separated positive integers denoting the weights of the
//    corresponding items.
//    Output:
//    Print the maximum possible value you can get with the given conditions that you can obtain for each test case in a new line.
//    Constraints:
//    Example:
//    Input:
//    1
//    3
//    4
//    1 2 3
//    4 5 1
//    Output:
//    3
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
using namespace std;

int knapsack01(size_t n_items, int target_weight, const vector<int>& wt, const vector<int>& v, vector<int>& result_items)
{
    vector<vector<int>> dp(n_items + 1, vector<int>(target_weight + 1));
    for (size_t i = 1; i <= n_items; ++i) {
        for (size_t w = 1; w <= target_weight; ++w) {
            if (wt[i-1] <= w) {
                dp[i][w] = max(dp[i-1][w], dp[i-1][w-wt[i-1]] + v[i-1]);
            }
            else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    return dp[n_items][target_weight];
}

int main() {
    size_t n_tests = 0;
    cin >> n_tests;
    for (size_t t = 0; t < n_tests; ++t) {
        size_t n_items = 0;
        int W = 0;
        cin >> n_items >> W;
        vector<int> values(n_items);
        for (size_t i = 0; i < n_items; ++i) {
            cin >> values[i];
        }
        vector<int> weights(n_items);
        for (size_t i = 0; i < n_items; ++i) {
            cin >> weights[i];
        }

        vector<int> result_items;
        int optimal_weight = knapsack01(n_items, W, weights, values, result_items);
        cout << optimal_weight << endl;
    }
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Egg Dropping Puzzle
//    The following is a description of the instance of this famous puzzle involving n=2 eggs and a building with k=36 floors.
//    Suppose that we wish to know which stories in a 36-story building are safe to drop eggs from, and which will cause the eggs to break on landing.
//    We make a few assumptions:
//    ..An egg that survives a fall can be used again.
//    ..A broken egg must be discarded.
//    ..The effect of a fall is the same for all eggs.
//    ..If an egg breaks when dropped, then it would break if dropped from a higher floor.
//    ..If an egg survives a fall then it would survive a shorter fall.
//    ..It is not ruled out that the first-floor windows break eggs, nor is it ruled out that the 36th-floor do not cause an egg to break.
//    In this problem you have to find minimum trials to solve for n eggs and k floors.
//    For more description on this problem see wiki page
//    Input:
//    The first line contains an integer T, depicting total number of test cases.
//    Then following T lines contains 2 integers n and k.
//    Output:
//    Print the minimum trials required to solve the problem.
//    Constraints:
//    1<=T<=30
//    1<=n<=10
//    1<=k<=50
//    Example:
//    Input:
//    1
//    2 10
//    Output:
//    4
// -------------------------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------------------------
//  Geeks for Geeks original submission
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int min_egg_dropping(int n_eggs, int n_floors)
{
    if (n_floors == 1 || n_floors == 0)
        return n_floors;
    if (n_eggs == 0)
        return 0;
    if (n_eggs == 1)
        return n_floors;

//    cout << "floors: " << n_floors << ", eggs: " << n_eggs << endl;

    vector<vector<int>> dp(n_eggs+1, vector<int>(n_floors+1));
    for (size_t i = 1; i <= n_eggs; ++i)
        dp[i][1] = 1;
    for (size_t j = 1; j <= n_floors; ++j)
        dp[1][j] = j;

    for (size_t i = 2; i <= n_eggs; ++i) {
        for (size_t j = 2; j <= n_floors; ++j) {
            int min_of_max = numeric_limits<int>::max();
            for (size_t x = 1; x <= j; ++x) {
                min_of_max = min(min_of_max, max(dp[i][j-x], dp[i-1][x-1]) + 1);
//                cout << "i: " << i << ", j: " << j << ", x: " << x << ", min_of_max: " << min_of_max << endl;
            }
            dp[i][j] = min_of_max;
        }
    }

    return dp[n_eggs][n_floors];
}

int main() {
    size_t n_tests = 0;
    cin >> n_tests;
    for (size_t t = 0; t < n_tests; ++t) {
        int n_floors = 0, n_eggs = 0;
        cin >> n_eggs >> n_floors;
        cout << min_egg_dropping(n_eggs, n_floors) << endl;
    }
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------------------------------------------------------
//  Geeks for Geeks original submission + solution reconstruction
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

namespace
{
    struct dp_node
    {
        int dp_value_ = 0;
        size_t optimal_solution_ = 0;
    };
}

int min_egg_dropping(int n_eggs, int n_floors, vector<size_t>& optimal_solution)
{
    if (n_floors == 1 || n_floors == 0)
        return n_floors;
    if (n_eggs == 0)
        return 0;
    if (n_eggs == 1)
        return n_floors;

//    cout << "floors: " << n_floors << ", eggs: " << n_eggs << endl;

    vector<vector<dp_node>> dp(n_eggs+1, vector<dp_node>(n_floors+1));
    for (size_t i = 1; i <= n_eggs; ++i)
        dp[i][1].dp_value_ = 1;
    for (size_t j = 1; j <= n_floors; ++j)
        dp[1][j].dp_value_ = j;

    for (size_t i = 2; i <= n_eggs; ++i) {
        for (size_t j = 2; j <= n_floors; ++j) {
            int min_of_max = numeric_limits<int>::max();
            for (size_t x = 1; x <= j; ++x) {
                size_t max_val = max(dp[i][j-x].dp_value_, dp[i-1][x-1].dp_value_) + 1;
                if (max_val < min_of_max) {
                    min_of_max = max_val;
                    dp[i][j].optimal_solution_ = x;
                }
            }
            dp[i][j].dp_value_ = min_of_max;
        }
    }

    // reconstruct optimal solution
    size_t optimal_floor = n_floors;
    for (size_t egg = n_eggs; egg > 0; --egg) {
        optimal_solution.push_back(dp[egg][optimal_floor].optimal_solution_);
        optimal_floor = dp[egg][optimal_floor].optimal_solution_;
    }
    reverse(optimal_solution.begin(), optimal_solution.end());

    return dp[n_eggs][n_floors].dp_value_;
}

int main() {
    size_t n_tests = 0;
    cin >> n_tests;
    for (size_t t = 0; t < n_tests; ++t) {
        int n_floors = 0, n_eggs = 0;
        cin >> n_eggs >> n_floors;
        vector<size_t> optimal_solution;
        cout << min_egg_dropping(n_eggs, n_floors, optimal_solution) << endl;
        cout << "optimal solution:\n";
        for (auto s: optimal_solution)
            cout << s << " ";
        cout << endl;
    }
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------------------------------------------------------
// Weighted Job Scheduling
//    Given N jobs where every job is represented by following three elements of it.
//    Start Time
//    Finish Time
//    Profit or Value Associated
//    Find the maximum profit subset of jobs such that no two jobs in the subset overlap.
//    Example:
//    Input: Number of Jobs n = 4
//           Job Details {Start Time, Finish Time, Profit}
//           Job 1:  {1, 2, 50}
//           Job 2:  {3, 5, 20}
//           Job 3:  {6, 19, 100}
//           Job 4:  {2, 100, 200}
//    Output: The maximum profit is 250.
//    We can get the maximum profit by scheduling jobs 1 and 4.
//    Note that there is longer schedules possible Jobs 1, 2 and 3
//    but the profit with this schedule is 20+50+100 which is less than 250
// -------------------------------------------------------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

namespace
{
    struct Job
    {
        int start_ = 0;
        int finish_ = 0;
        int profit_ = 0;
    };
}

istream& operator>>(istream& is, Job& job)
{
    is >> job.start_ >> job.finish_ >> job.profit_;
    return is;
}

ostream& operator<<(ostream& os, const Job& job)
{
    os << job.start_ << "," << job.finish_ << "," << job.profit_;
    return os;
}

ostream& operator<<(ostream& os, const vector<Job>& jobs)
{
    for (auto j: jobs) {
        os << j << endl;
    }
    return os;
}

vector<Job> input_jobs(size_t n_jobs)
{
    vector <Job> result;
    for (size_t i = 0; i < n_jobs; ++i) {
        Job job;
        cin >> job;
        result.push_back(job);
    }
    return result;
}

int find_first_not_overlapped(const vector<Job>& jobs, size_t i)
{
    if (i <= 0)
        return -1;
    if (i >= jobs.size())
        return jobs.size() - 1;
    for (int j = i - 1; j >= 0; --j) {
        if (jobs[j].finish_ <= jobs[i].start_)
            return j;
    }
    return -1;
}

int max_wjs_profit(vector<Job> jobs)
{
    size_t n_jobs = jobs.size();
    if (n_jobs == 0)
        return 0;
    if (n_jobs == 1)
        return jobs[0].profit_;
    // sort jobs acc.to finish time
    sort(jobs.begin(), jobs.end(),
         [](const Job& l, const Job& r) { return l.finish_ < r.finish_; }
    );
    vector<int> dp_solutions(n_jobs);
    dp_solutions[0] = jobs[0].profit_;
    for (int i = 1; i < n_jobs; ++i) {
        int j = find_first_not_overlapped(jobs, i);
        assert(j >= -1 && j < i);
        dp_solutions[i] = max(dp_solutions[i-1], ( (j == -1) ? jobs[i].profit_ : dp_solutions[j] + jobs[i].profit_ ));
//        cout << "i: " << i << ", first not over: " << j << ", dp[i]: " << dp_solutions[i] <<  endl;
    }
    return dp_solutions[n_jobs-1];
}

int main() {

    size_t n_jobs = 0;
    cin >> n_jobs;
    vector<Job> jobs = input_jobs(n_jobs);
    cout << "max wjs profit: " << max_wjs_profit(jobs) << endl;

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

// -------------------------------------------------------------------------------------------------------
// Hashing
// -------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------
// Print a Binary Tree in Vertical Order
//    Given a binary tree, your task is to complete the function verticalOrder which takes one argument the root of the binary tree and
//    prints the node of the binary tree in vertical order .
//              1
//           /     \
//         2       3
//       /        /
//    4       5
//    The nodes of the above tree printed in vertical order will be
//    4
//    2
//    1 5
//    3
//    Your output should be 4 $2 $1 5 $3 $
//    Note: Each vertical line will be separated by a "$" without quotes.
//    Input:
//    The task is to complete the method which takes one argument, root of Binary Tree. There are multiple test cases. For each test case, this method will be called individually.
//    Output:
//    The function should print nodes in vertical order where  each vertical line is separated by a "$" without quotes.
//    Constraints:
//    1 <=T<= 30
//    1 <= Number of nodes<= 20
//    Example:
//    Input:
//    2
//    2
//    1 2 R 1 3 L
//    4
//    10 20 L 10 30 R 20 40 L 20 60 R
//    Output:
//    3 $1 $2 $
//    40 $20 $10 60 $30 $
// -------------------------------------------------------------------------------------------------------
/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/
#if 0
#include <iostream>
#include <map>

using namespace std;

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct Node
{
    int data;
    Node* left;
    Node* right;
};
/* Should print vertical order such that each vertical line
   is separated by $ */

using Vertical_tree = multimap<int, int>;

void verticalOrder_impl(Node* node, Vertical_tree& vt, int cur_level)
{
    vt.insert({cur_level, node->data});
    if (node->left)
        verticalOrder_impl(node->left, vt, cur_level-1);
    if (node->right)
        verticalOrder_impl(node->right, vt, cur_level+1);
}

void verticalOrder(Node *root)
{
    if (root == nullptr)
        return;
    Vertical_tree vt;
    verticalOrder_impl(root, vt, 0);
    for (auto it = vt.begin(), prev_it = it; it != vt.end(); ++it) {
        if (prev_it->first != it->first) {
            cout << "$";
            prev_it = it;
        }
        cout << it->second << " ";
    }
    cout << "$";
}

int main()
{
    Node* root = new Node;
    root->data = 1;
    Node* left = new Node;
    left->data = 2;
    Node* right = new Node;
    right->data = 3;
    root->left = left;
    root->right = right;
    Node* left_left = new Node;
    left_left->data = 4;
    left->left = left_left;
    Node* right_left = new Node;
    right_left->data = 5;
    right->left = right_left;

    verticalOrder(root);

    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------
// Array Subset of another array
// -------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> input_array(size_t n)
{
    vector<int> in_array;
    for (size_t i = 0; i < n; ++i) {
        int elem = 0;
        cin >> elem;
        in_array.push_back(elem);
    }
    return in_array;
}

bool is_subset(const vector<int>& arr_1, const vector<int>& arr_2)
{
    unordered_set<int> hash(arr_1.begin(), arr_1.end());
    for (auto elem: arr_2) {
        if (hash.find(elem) == hash.end())
            return false;
    }
    return true;
}

int main()
{
    size_t T = 0;
    cin >> T;
    for (size_t t = 0; t < T; ++t) {
        size_t n_1 = 0, n_2 = 0;
        cin >> n_1 >> n_2;
        vector<int> arr_1 = input_array(n_1);
        vector<int> arr_2 = input_array(n_2);
        cout << ( is_subset(arr_1, arr_2) ? "Yes\n" : "No\n" );
    }
}
#endif

// -------------------------------------------------------------------------------------------------------
// Find Itinerary from a given list of tickets
// -------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<string, string> input_tickets(size_t n_tickets)
{
    unordered_map<string, string> tickets;
    for (size_t i = 0; i < n_tickets; ++i) {
        string src, dest;
        cin >> src >> dest;
        tickets.insert({src, dest});
    }
    return tickets;
}

void print_itinerary(const unordered_map<string, string>& tickets)
{
    // build hash of destinations
    unordered_set<string> destinations;
    for (auto ticket: tickets) {
        destinations.insert(ticket.second);
    }
    // find itinerary start: first source not present in destinations
    auto it = tickets.begin();
    for (; it != tickets.end(); ++it) {
        if (destinations.find(it->first) == destinations.end())
            break;
    }
    if (it == tickets.end())
        cout << "Error: loop in itinerary?\n";
    for (; it != tickets.end();) {
        cout << it->first << "->" << it->second << ", ";
        it = tickets.find(it->second);
    }
    cout << endl;
}

int main()
{
    size_t n_tickets = 0;
    cin >> n_tickets;
    unordered_map<string, string> tickets = input_tickets(n_tickets);
    print_itinerary(tickets);
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------
// Clone a Binary Tree
// -------------------------------------------------------------------------------------------------------
/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/
#if 0
#include <iostream>
#include <unordered_map>

using namespace std;

/* A binary tree node has data, pointer to left child
   and a pointer to right child
   */
struct Node
{
    int data;
    Node* left;
    Node* right;
    Node *random;
};

Node* create_node(int data)
{
    Node* node = new Node;
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->random = nullptr;
}

using Hash_nodes = unordered_map<int, Node*>;

ostream& operator<<(ostream& os, const Hash_nodes& hash)
{
    for (auto entry: hash) {
        cout << dec << entry.first << "->0x" << hex << (std::uint64_t)entry.second << endl;
    }
    return os;
}

void clone_impl(Node* src, Node*& dst, Hash_nodes& hash_nodes)
{
    if (src==nullptr)
        return;
    dst = create_node(src->data);
    hash_nodes.insert({dst->data, dst});
    clone_impl(src->left, dst->left, hash_nodes);
    clone_impl(src->right, dst->right, hash_nodes);
}

void random_ptr_impl(Node* src, Node* dst, const Hash_nodes& hash_nodes)
{
    if ((src == nullptr) || (dst == nullptr))
        return;
    if (src->random != nullptr) {
        auto it = hash_nodes.find(src->random->data);
        if (it != hash_nodes.end()) {
            dst->random = it->second;
        }
    }
    random_ptr_impl(src->left, dst->left, hash_nodes);
    random_ptr_impl(src->right, dst->right, hash_nodes);
}

/* The function should clone the passed tree and return
   root of the cloned tree */
Node* cloneTree(Node* tree)
{
    Hash_nodes hash_nodes;
    Node* clone_root = nullptr;
    // clone the tree, dont process random pointers, populate hash data->Node*
    clone_impl(tree, clone_root, hash_nodes);
    // populate random node pointers based on hash
    random_ptr_impl(tree, clone_root, hash_nodes);
}

int main()
{
    Node* root = create_node(1);
    Node* l = create_node(2);
    Node* r = create_node(3);
    Node* ll = create_node(4);
    Node* lr = create_node(5);
    Node* rr = create_node(6);
    l->left = ll;
    l->right = lr;
    r->right = rr;
    root->left = l;
    root->right = r;

    Node* clone = cloneTree(root);

    return 0;
}
#endif

#if 0
#include <iostream>
#include <memory>

using namespace std;

struct A;
struct B;

struct A
{
    A() { cout << "A::A()\n"; }
    ~A() { cout << "A::~A()\n"; }
    shared_ptr<B> b_ = nullptr;
};

struct B
{
    B() { cout << "B::B()\n"; }
    ~B() { cout << "B::~B()\n"; }
    weak_ptr<A> a_;
};

int main()
{
    shared_ptr<A> a = make_shared<A>();
    shared_ptr<B> b = make_shared<B>();
    a->b_ = b;
    b->a_ = a;
    cout << "counts a: " << a.use_count() << ", b: " << b.use_count() << ", a.b_: " << a->b_.use_count() << ", b.a_: " << b->a_.use_count() << endl;
}
#endif

#if 0
#include <iostream>
#include <memory>

using namespace std;

int main()
{
    int a[] = {1,2,3,4,5,6};

    cout << a[1+3] << "," << (1+3)[a] << endl;
}
#endif
#if 0
// -------------------------------------------------------------------------------------------------------
// Anagram
// -------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
using namespace std;

bool is_permutation(const string& s1, const string& s2)
{
    if (!s1.size() || !s2.size() || s1.size() != s2.size())
        return false;
    array<int, 255> char_count{};
    for (auto one_char: s1)
        ++char_count[static_cast<int>(one_char)];
//    cout << "before\n";
//    for (auto count: char_count) {
//        cout << count;
//    }
//    cout << endl;
    for (auto one_char: s2) {
        if (--char_count[static_cast<int>(one_char)] < 0)
            return false;
    }
//    cout << "after\n";
//    for (auto count: char_count) {
//        cout << count;
//    }
//    cout << endl;
    return ( find_if(char_count.begin(), char_count.end(), [](int count){ return (count ? true : false); }) != char_count.end() ? false : true );
}

int main() {
    size_t T = 0;
    cin >> T;
    for (size_t i = 0; i < T; ++i) {
        string s1, s2;
        cin >> s1 >> s2;
        cout << (is_permutation(s1, s2) ? "YES" : "NO") << endl;
    }
	return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------
// Endianess check
// -------------------------------------------------------------------------------------------------------
#if 0
#include <iostream>
using namespace std;
int main() {
    int four_bytes = 0x01020304;
    char* p = (char*)(&four_bytes);
    cout << "Endianess: " << ( *(char*)(&four_bytes) == 0x01 ? "BIG" : "LITTLE" ) << endl;
    return 0;
}
#endif

// -------------------------------------------------------------------------------------------------------
// Key Pair: Array, pair sum
// -------------------------------------------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

bool test_key_sum(const vector<int>& v, int sum)
{
    unordered_map<int, size_t> hash;
    for (auto i: v) {
        auto it = hash.find(i);
        if (it == hash.end())
            hash.insert({i, 1});
        else
            ++it->second;
    }
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i]> sum)
            continue;
        auto it = hash.find(sum - v[i]);
        size_t count = (v[i] == sum - v[i] ? 2 : 1);
        if (it != hash.end() && it->second >= count)
            return true;
    }
    return false;
}

int main() {
    int T = 0;
    cin >> T;
    for (size_t t = 0; t < T; ++t) {
        int N = 0, X = 0;
        cin >> N >> X;
        vector<int> c(N, 0);
        for (size_t i = 0; i < N; ++i) {
            cin >> c[i];
        }
        cout << (test_key_sum(c, X) ? "YES" : "NO") << endl;
    }
    return 0;
}
