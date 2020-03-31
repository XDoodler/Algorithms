
int knapSack(int W,int wt[],int val[],int n){
	int dp[n+1][W+1];
	rep(i,0,n+1){
		rep(j,0,W+1){
			if(i==0||j==0) dp[i][j]=0;
			else if(wt[i-1] <= j)dp[i][j]=max(val[i-1] + dp[i-1][j-wt[i-1]],  dp[i-1][j]);
			else  dp[i][j] = dp[i-1][j];
		}
	}
	return dp[n][W];
}
int main() {
	IOS;
	int val[] = {7,5,2,1,3,4}; 
    	int wt[] = {10,2,4,5,1,3}; 
    	int  W = 10; 
   	 int n = sizeof(val)/sizeof(val[0]); 
    	printf("%d\n", knapSack(W, wt, val, n)); 
	return 0;
}


