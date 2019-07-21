#include <bits/stdc++.h>
using namespace std;
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);
#define TC int t; cin >> t; while(t--)

int n,m;
const int MAX = 1e5+5;
const int inf = 1e9;

vector<int> G[MAX],color;
int arrival[MAX],departure[MAX],visited[MAX],path[MAX];

//0 white
//1 gray
//2 black
bool findCycle(int u)
{
	color[u] = 1;

	for(auto x : G[u])
	{
		if(color[x] == 1)return true;
		if(color[x] == 0 && findCycle(x)) return true;
	}color[u] = 2; return false;

}
int32_t main() {
    IOS;
    n=4;
   	G[1].push_back(2);
    G[1].push_back(3);
    G[3].push_back(2);
    G[3].push_back(4);

    int fl=0;
    color.resize(n,0);
    for (int x = 1; x <=n; ++x)
    {

    	if(color[x] == 0)if(findCycle(x)==true)fl=1; else fl=2;
    }
    (fl==1)?cout<<"YES":cout<<"NO";
    cout << '\n';
    return 0;
}
