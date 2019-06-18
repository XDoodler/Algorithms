/*
   codechef : nuttela
   
   Depth- first search
*/
#include <bits/stdc++.h> 
#define int unsigned long long
#define del for(int i = 0; i < M; i++)G[i].clear();
using namespace std; 
 
const int M = 1e6+6;

vector<int> G[M]; 
vector<bool> vis(M);
void dfs(int u, int parent) 
{  
	if(vis[u])return;
	vis[u]=true;
	cout << u << endl;
	for(int child:G[u])
	{
		if(!vis[child])dfs(child, u);
	}
} 
int32_t main() 
{  
	int n,v,e;
	cin >> n;
	for (int i = 0; i < n - 1; ++i){
		cin >> v >> e;
		G[v].push_back(e);
		G[e].push_back(v);
	} 
	dfs(1,0);
	del;
	return 0; 
} 

/*----------------------------------------------------------------------------------------------------------------------
Problem : https://www.codechef.com/problems/FIRESC
Solution : https://www.codechef.com/viewsolution/23666254

*/
