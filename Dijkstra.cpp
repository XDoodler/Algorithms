  
/* 
   codechef : nuttela
   
   Dijkstra Algorithm 
*/

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e6+6;
int n,m;
int arrival[N], departure[N], vis[N], parent[N];
vector<pair<int, int> > g[N];

void dijkstra(int source, int destination)
{
	for(int i=1;i<=n;i++)
	{
		arrival[i]=1e18;
		departure[i]=1e18;
		vis[i]=0;
	}
	arrival[source]=0;
	set<pair<int, int> > s;
	s.insert({0, source});
	while(!s.empty())
	{
		auto x = *(s.begin());
		s.erase(x);
		vis[x.second]=1;
		departure[x.second]=arrival[x.second];
		for(auto it:g[x.second])
		{
			if(arrival[it.first] > departure[x.second] + it.second)
			{
				s.erase({arrival[it.first], it.first});
				arrival[it.first]=departure[x.second] + it.second;
				s.insert({arrival[it.first], it.first});
				parent[it.first]=x.second;
			}
		}
	}
	if(!vis[destination])
	{
		cout<<"-1";
		return;
	}
	int v=destination;
	vector<int> ans;
	while(parent[v])
	{
		ans.push_back(v);
		v=parent[v];
	}
	ans.push_back(source);
	reverse(ans.begin(), ans.end());
	for(auto it:ans)
		cout<<it<<" ";
}
int32_t main()
{

	cin >> n>> m;
	for(int i=1; i<=m; i++){
		int u,v,w;
		cin >> u >> v >>w;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}

	dijkstra(1,n);
	
	return 0;
}
