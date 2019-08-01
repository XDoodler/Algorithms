#include <bits/stdc++.h>
using namespace std;
#define int unsigned long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);
#define TC int t; cin >> t; while(t--)

int n,m;
const int MAX = 1e5+5;
const int inf = 1e18+18;

vector<pair<int,int>> G[MAX];
int arrival[MAX],departure[MAX],visited[MAX],path[MAX];

void dijsktra(int source, int dest)
{
	set<pair<int,int>> st;
	arrival[source] = 0;
	st.insert({0,source});
	while(!st.empty())
	{	cout << endl;
		//for(auto x : st)cout << x.first << ' ' << x.second << ' ';
		auto x = *(st.begin());
		st.erase(x);
		visited[x.second] = 1;
		departure[x.second] = arrival[x.second];
		for(auto it:G[x.second])
		{
			if(arrival[it.first] > departure[x.second] + it.second)
			{
				st.erase({arrival[it.first], it.first});
				arrival[it.first]=departure[x.second] + it.second;
				st.insert({arrival[it.first], it.first});
				path[it.first]=x.second;
			}
		}
	}
		if(!visited[dest])
		{
		cout<<"-1";
		return;
		}
		int v = dest;
		vector<int> ans;
		while(path[v])
		{
			//cout << v << ' ';
			ans.push_back(v);
			v=path[v];
		}
		for (int i = 1; i <=n; ++i)
		{
			cout << path[i];
		}
		ans.push_back(source);
		reverse(ans.begin(), ans.end());
		for(auto it:ans)
		cout<<it<<" ";
}
int32_t main() {
    IOS;

    int u,v,w;
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
    	cin >> u >> v >> w;
    	G[u].push_back({v,w});
    	G[v].push_back({u,w});
    }
    /*for (int i = 1; i <= n; ++i)
	{
		arrival[i] = inf;
		departure[i] = inf;
	}*/
    dijsktra(1,n);

    return 0;
}

//(0,1)
// (2,2)()
