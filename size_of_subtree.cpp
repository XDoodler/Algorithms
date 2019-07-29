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
const int MAX = 1e6+6;
const int MOD = (int) 1e9+7;

ll modmul(ll a,ll b){ll res=0;a%=MOD;while(b){if(b&1)res=(res+a)%MOD;a=(a<<1)%MOD;b>>=1;}return res;}
ll modexp(ll a,ll b){ll res=1;a%=MOD;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;}
using namespace std;

vector<int> G[MAX],child;
int sum=0;
int dfs(int u,int par)
{	
	child[u] = 1;
	for(auto x : G[u])
	{
		if(x == par)continue;
		dfs(x,u);
		child[u] += child[x]; 
	}
	return 0;
}
int32_t main() {
    IOS;
    int n,m,u,v;
    cin >> n >> m;
    rep(i,0,m)
    {
    	cin >> u >> v;
    	G[u].pb(v);G[v].pb(u);
    }
    child.resize(n+1);
    dfs(1,0);
    rep(i,1,n+1)cout << child[i] << ' ';
    return 0;
}

//INPUT
//	  	    1
//	 	   / \
//		  2   3
//		 / \ 
//		4   5

//OUTPUT
// 5 3 1 1 1
