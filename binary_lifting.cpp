#pragma Gpref optimize("O3")
//#pragma Gpref optimize("Ofast")
//#pragma Gpref target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma Gpref optimize("unroll-loops")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
#define int long long
#define ld long double
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define TC int t; cin >> t; while(t--)
#define rep(i,j,k) for(int i=j; i<k; i++)
#define rep_(i,j,k) for(int i=j; i>=k; --i)
#define pb push_back
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define F first
#define S second 
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
 
using namespace __gnu_pbds; 
using namespace std;
 
const int MOD = (int)1e9+7;
int n,m,q,mx;
const int MAX = 5;
typedef pair<int, int> pairs;
const int LG = ceil(log2(MAX));

vector<vector<int>> up(MAX, vector<int>(LG+1));
vector<int> G[MAX];
void dfs(int u,int par){
    up[u][0] = par;
    for(int i = 1; i <= LG; i++){
        up[u][i]=up[up[u][i-1]][i-1];
        //cout <<  up[u][i] <<' ';
    }
    for(auto x : G[u]){
        if(x!=par)dfs(x,u);
    }
}

int32_t main(){
IOS;
G[1].pb(2);G[2].pb(1);
G[1].pb(3);G[3].pb(1);
G[3].pb(4);G[4].pb(3);
dfs(1,1);
rep(i,1,MAX){for(int j = 0; j <= LG; j++){cout<<up[i][j]<<' ';}cout<<endl;}
return 0;
}
