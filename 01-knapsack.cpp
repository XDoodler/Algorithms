//Lowest common ancestor.
#pragma GCC optimize("O3")
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define ll long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define TC int t; cin >> t; while(t--)
#define rep(i,j,k) for(int i=j; i<k; i++)
#define endl '\n'
#define pb push_back
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
const int MAX = (int)1e5+5;
using namespace std;
vector<int> G[MAX];


int knapSack(int W,int wt[],int val[],int n){
	int dp[n+1][W+1];
	rep(i,0,n+1){
		rep(j,0,W+1){
			if(i==0||j==0) dp[i][j]=0;
			else dp[i][j]=max(val[i-1] + dp[i-1][j-wt[i-1]],  dp[i-1][j]); 
		}
	}return dp[n][W];
}
int main() {
	IOS;
	int val[] = {60,100,120}; 
    int wt[] = {10,20,30}; 
    int  W = 50; 
    int n = sizeof(val)/sizeof(val[0]); 
    printf("%d\n", knapSack(W, wt, val, n)); 
	return 0;
}


