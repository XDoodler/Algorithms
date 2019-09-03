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
int timer;
const int MAX = 1e5+5;
typedef pair<int, int> pairs;
const int LG = ceil(log2(MAX));

vector<vector<int>> up(MAX, vector<int>(LG+1));
vector<int> tin(MAX),tout(MAX),level(MAX);
vector<int> G[MAX];
map<pair<int,int>,int> weights;
void dfs(int u,int par, int height=0){
    level[u] = height;
    tin[u] = ++timer;
    up[u][0] = par;
    for(int i = 1; i <= LG; i++){
        up[u][i]=up[up[u][i-1]][i-1];
    }
    for(auto x : G[u]){
        if(x!=par)dfs(x,u, height+1);
    }
    tout[u] = ++timer;
}
bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = LG; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

int lcamin(int a, int b){
    //a<b condition
    if(level[a]<level[b])swap(a,b);
    int j=0;
    int mn=INT_MAX;
    int down = up[a][0];
    while(down!=b){
        int x=down;
        int y=up[a][j+1];
        cout << x << y << endl;
        if(x>y)swap(x,y);
        mn = min(mn,weights[{x,y}]);
        down = up[a][j++];
    }
    return mn;
}
int lcamax(int a, int b){
    if(level[a]<level[b])swap(a,b);
    int j=0;
    int mn=INT_MIN;
    int down = up[a][0];
    while(down!=b){
        int x=down;
        int y=up[a][j+1];
        if(x>y)swap(x,y);
        mn = max(mn,weights[{x,y}]);
        down = up[a][j++];
    }
    return mn;
}

int32_t main(){
IOS;
int n,u,v,q,w;
cin >> n;
timer=0;
rep(i,1,n){
    cin >> u >> v >> w;
    G[u].pb(v);
    G[v].pb(u);
    if(u>v)swap(u,v);
    weights[{u,v}] = w;
    //cout << weights[{u,v}] << endl;
}
dfs(1,1);
cin >> q;
while(q--){
    int l,r;
    cin >> l >> r;
    int rt = lca(l,r);
    int lcamin1 = lcamin(l,rt);
    int lcamax1 = lcamax(l,rt);
    int lcamin2 = lcamin(r,rt);
    int lcamax2 = lcamax(r,rt);
    cout << min(lcamin1,lcamin2) << ' ' << max(lcamax1,lcamax2) << '\n';
}
return 0;
}
