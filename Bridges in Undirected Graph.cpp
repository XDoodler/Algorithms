/* take template from Nuttela.cpp */

vector<ll> g[MAX];
int in[MAX],low[MAX],vis[MAX];
int time=0;
void dfs(int u,int par) {
    vis[u]=1;
    in[u]=low[u]=time++;
    for(auto &x:g[u]) {
        if(x==par)continue;
        if(vis[x])low[u]=min(in[x],low[u]);
        else {
            dfs(x,u);
            low[u]=min(low[u],low[x]);
            if(low[x]>in[u]) {
                ++bridge;
                // is_bridge(u,x);
            }
        }
    }
}
