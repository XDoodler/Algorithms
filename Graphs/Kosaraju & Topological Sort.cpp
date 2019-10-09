// https://www.codechef.com/problems/MCO16405

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define ld long double
#define pb push_back
#define ppb pop_back
#define pii pair<ll, ll>
#define pll pair<ll, ll>
#define vi vector<ll>
#define vll vector<ll>
#define vull vector<ull>
#define vpii vector<pll >
#define vpll vector<pll >
#define mt make_tuple
#define ff first
#define ss second
#define uset unordered_set
#define umap unordered_map
#define all(x) x.begin(), x.end()
#define revall(x) x.rbegin(), x.rend()
#define rep(i, j, k) for(ll i = j; i < k; ++i)
#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define TT int tt; cin>>tt; while(tt--)

const ll MOD = (ll)(1e9+7);
const int inf = (int)INFINITY;
const ll INF = (ll)INFINITY;
const int MAX = (int)(1e5+1);

int n, m, ind = 0;
ll maxval = 0;
vi G[MAX], GR[MAX], T[MAX], GG[MAX], proc, cost(MAX), val(MAX), comp, arr;
bool vis[MAX] = {false};
umap<int, int> mp;

void dfs1(int u) {
    vis[u] = true;
    for(auto v : GR[u])
        if(!vis[v])
            dfs1(v);
    proc.pb(u);
}

void dfs2(int u) {
    vis[u] = true;
    for(auto v : G[u])
        if(!vis[v])
            dfs2(v);
    comp.pb(u);
}

void kosaraju() {
    rep(i, 1, n+1)
        if(!vis[i])
            dfs1(i);
    memset(vis, false, sizeof(vis));
    for(int i = n-1; i >= 0; --i)
        if(!vis[proc[i]]) {
            ll sum = 0;
            dfs2(proc[i]);
            for(auto x : comp) sum += cost[x];
            for(auto x : comp) {
                T[ind].pb(x);
                mp[x] = ind;
                val[x] = sum;
            }
            ++ind;
            comp.clear();
        }
}

void dfs(int u) {
    vis[u] = true;
    for(auto v : GG[u])
        if(!vis[v])
            dfs(v);
    arr.pb(u);
}

void toposort() {
    memset(vis, false, sizeof(vis));
    rep(i, 1, n+1)
        if(!vis[i]) 
            dfs(i);
}

int main() {
    fastio;
    //TT {
        cin >> n >> m;
        rep(i, 1, n+1) cin >> cost[i];
        rep(i, 0, m) {
            int u, v;
            cin >> u >> v;
            G[u].pb(v);
            GR[v].pb(u);
        }
        kosaraju();
        rep(i, 0, ind) {
            for(auto u : T[i]) {
                for(auto v : G[u])
                    if(mp[v] != i)
                        GG[i].pb(mp[v]);
            }
        }
        toposort();
        rep(i, 0, arr.size()) {
            ll sum = 0;
            for(auto u : T[arr[i]]) {
                for(auto v : G[u])
                    if(mp[v] != mp[u])
                        sum = max(sum, val[v]);
            }
            for(auto u : T[arr[i]])
                val[u] += sum;
        }
        rep(i, 1, n+1) cout << val[i] << " ";
        rep(i, 0, n+1) {
            G[i].clear();
            GR[i].clear();
        }
        proc.clear();
        arr.clear();
        memset(vis, false, sizeof(vis));
    //}
    return 0;
}
