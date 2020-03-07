#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	int arr[n + 1];
	for (int i = 1; i <= n; ++i) {
	    cin >> arr[i];
	}
	int dp[n + 1][n + 1];
	memset(dp, sizeof(dp), 0);
	int res = INT_MIN;
	dp[1][0] = 0;
	dp[1][1] = arr[1];
	for (int i = 2; i <= n; ++i) {
	    for (int j = 0; j <= i; ++j) {
	        if(j == 0){
	            dp[i][j] = 0;
	            continue;
	        }
	        if(j == i) {
	            dp[i][j] = arr[i] * j + dp[i - 1][j - 1];
	        }
	        else {
	            dp[i][j] = max(dp[i - 1][j], arr[i] * j + dp[i - 1][j - 1]);
	        }
	        res = max(res, dp[i][j]);
	    }
	}
	cout << res;
	return 0;
}
