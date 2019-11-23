/* nuttela - Soham Chakrabarti */
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define endl '\n';
 
typedef long long ll;
typedef long double ld;
 
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;
 
vector <int> G[N], deg;
vector <bool> is;

int main() {
  IO;
  int n, k;
  cin >> n >> k;

  deg.assign(n + 1, 0);
  is.assign(n + 1, false);
  for (int i = 1; i < n; ++i)
  {
    int u, v;
    cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
    ++deg[u]; ++deg[v];
  }

  for (int i = 0; i < k; ++i)
  {
    int x; cin >> x;
    is[x] = true;
  }

  queue <int> nodes;
  for (int i = 1; i < (n + 1); ++i)
  {
    if(!is[i] && deg[i] == 1) { //leaf nodes and not terminus
      nodes.push(i);
    }
  }

  int nvis = 0;
  while(!nodes.empty()) {
    int data = nodes.front();
    // cout << data << endl;
    nodes.pop();
    for (auto u : G[data]) {
      remove(G[u].begin(), G[u].end(), data); 
      deg[u]--;
    } 
    for (auto u : G[data]) {
      if(!is[u] && deg[u] == 1) {
        nodes.push(u);
      }
    }
    nvis++;
  }

  cout << (n - nvis);
  cout << endl;
  return 0;
}
