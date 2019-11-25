/* nuttela - Soham Chakrabarti */
 
#include <stdio.h>
 
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define endl '\n';
  
const int N = 1e2 + 2;
const int MOD = 1e9 + 7;

int G[N][N];
bool vis[N];

bool dfs(int u, int parent, int limit) {
  vis[u] = true;;
  for (int i = 0; i < limit; ++i) {
    if(G[u][i]) {
      if(i == parent) continue;
      if(vis[i]) return true;
      if(dfs(i, u, limit))return true;
    }
   return true;
  }
}

int main() {
  IO;
  //inputs
  int n; scanf("%d", &n)
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      scanf ("%d", G[i][j]);
    }
  }
  bool hasCycle = false;

  //declare false
  for (int i = 0; i < n; ++i)
  {
    vis[i] = false;
  }

  for (int i = 0; i < n; ++i)
  {
      if (vis[i]) continue;
      if (dfs(i, -1, n)) hasCycle = true;
      break;
  }

  if(hasCycle) {
    printf("%s\n", "YES");
  }
  else {
    printf("%s\n","NO");
  }
  return 0;
}
