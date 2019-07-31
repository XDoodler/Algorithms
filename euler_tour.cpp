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
const int MAX = (int)1e5+5;
using namespace std;


vector<int> G[MAX], euler_tour;

void dfs(int u,int parent){
	euler_tour.pb(u);
	for(auto x:G[u]){
		if(x==parent)continue;
		dfs(x,u);
		euler_tour.pb(u);
	}
}
int main() {
	IOS;
	G[1].push_back(2);G[2].push_back(1);
	G[1].push_back(3);G[3].push_back(1);
	G[2].push_back(4);G[4].push_back(2);
	G[2].push_back(5);G[5].push_back(2);
	dfs(1,0);
	rep(i,0,euler_tour.size())cout<<euler_tour[i]<<' ';cout<<endl;
    return 0;
}


/*    
	      1
	   /	  \
	  2	     3
	 /  \
  4    5 


   Euler Tour : 1 2 4 2 5 2 1 3 1 
*/
