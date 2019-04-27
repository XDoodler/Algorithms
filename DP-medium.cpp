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

