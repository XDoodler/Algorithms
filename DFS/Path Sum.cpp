/* Take template from Nuttela.cpp */

/* path with maximum sum in tree (positive values only) Use value array to store values */

vector<int> g[MAX];
int dp[MAX];

void dfs(int u,int par,int &res) {
    dp[u]=u+dp[par];
    for(int x:g[u]) {
        if(x==par) continue;
        dp[x]=x+dp[u];
        dfs(x,u,res);
    }
    res=max(res,dp[u]);
}

int32_t main() {
    io;
    int n;
    cin>>n;
    rep(i,1,n) {
        int u,v;
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    int res=-1;
    memset(dp,0,sizeof(dp));
    dfs(1,0,res);
    cout<<res<<endl;
    return 0;
}
