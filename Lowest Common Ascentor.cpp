/* Problem Link - https://www.codechef.com/problems/ENOC1
   Solution Link - https://www.codechef.com/viewsolution/27790936
*/

const int MAX = (int)1e5+1, LG = ceil(log2(MAX));
 
vector<int> G[MAX];
vector<int> lvl(MAX), val;
vector<vector<int>> up(MAX, vector<int>(LG+1)), dp(MAX, vector<int>(LG+1)); 
 
void dfs(int u, int par, int v = -1, int h=0){
  lvl[u] = h;
  up[u][0] = par;
  if(v!=-1)dp[u][0]=v;
  FR(i,1,LG+1){
    up[u][i] = up[up[u][i-1]][i-1];
    dp[u][i] = (dp[u][i-1] ^ dp[up[u][i-1]][i-1]);
  }
  for(auto x:G[u]){
      if(x != par) dfs(x, u, val[x], h+1);
  }
}
 
int lca(int u, int v) {
    if(lvl[u] < lvl[v])
        swap(u, v);
    for(int i = LG; i >= 0; --i) {
        if(lvl[u] - (1<<i) >= lvl[v])
            u = up[u][i];
    }
    if(u == v)
        return u;
    for(int i = LG; i >= 0; --i) {
        if(up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}
