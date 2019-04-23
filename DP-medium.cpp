int dp[100005];

int maxSubsetSum(vector<int> arr) {
    dp[0] = max(0, arr[0]);
    if (arr.size() == 1)
      return dp[0];
    for (int i = 1; i < arr.size(); i++) {
      dp[i] = max(dp[i - 2], max(dp[i - 1], dp[i - 2] + arr[i]));
    }
    int n = arr.size();
    return max(dp[n - 1], dp[n - 2]);
}

/*
Problem : https://www.hackerrank.com/challenges/max-array-sum/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming
Solution : https://www.hackerrank.com/challenges/max-array-sum/submissions/code/105428447?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming

Given an array of integers, find the subset of non-adjacent elements with the maximum sum. Calculate the sum of that subset.

For example, given an array arr=[2 , 1, 3 ,-4 , 5]  we have the following possible subsets:

Subset      Sum
[-2, 3, 5]   6
[-2, 3]      1
[-2, -4]    -6
[-2, 5]      3
[1, -4]     -3
[1, 5]       6
[3, 5]       8

output : 8
*/
