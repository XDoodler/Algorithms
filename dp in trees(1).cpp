/*
Loved this problem again! :)
*/

#include<bits/stdc++.h>
#define LL long long
#define pb push_back

using namespace std;

const LL MAX = 1e6;
LL n;
vector<pair<LL,LL>> ans;
vector<LL> Tree[MAX];
vector<LL> v(MAX),m(MAX),A;

void dfs2(LL u, LL parent) {
	//trace the path from node to leaf
	LL child_node = 0;  //child_node used will keep the track
    if(A.size()) A.pb(__gcd(A[A.size()-1], v[u]));
    else A.pb(v[u]);
    for(auto x : Tree[u]) {
        if(x == parent) continue;
        ++child_node;
        dfs2(x, u);
    }
    if(!child_node) {
        LL szzz = A.size();
        LL HH = A[szzz-1];
        LL PP = __gcd(HH,m[u]);
        ans.pb({u, m[u]-PP});
    }
    A.pop_back();
}

int32_t main()
{
	ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
	LL t;
	cin >> t;
	while(t--){
		cin >> n;
		A.reserve(n);
		ans.reserve(n);
		for(LL i=1; i<=n-1; i++)
		{
			LL u,v;
			cin >> u >> v;
			Tree[u].pb(v);
			Tree[v].pb(u);
		}
		for (LL i = 1; i <= n; ++i)
		{
			cin >> v[i];
		}
		for (LL i = 1; i <= n; ++i)
		{
			cin >> m[i];
		}
		dfs2(1,0);
		sort(ans.begin(),ans.end());
		for(auto x : ans)
            cout << x.second << ' ';
        cout << endl;
		for (LL i = 1; i <= n; ++i)
		{
			Tree[i].clear();
		}
		A.clear();
		ans.clear();
	}
	return 0;
}
