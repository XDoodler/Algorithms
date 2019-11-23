/* nuttela - Soham Chakrabarti */
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define endl '\n';
 
typedef long long ll;
typedef long double ld;
 
const int N = 3e5 + 5;
const int MOD = 1e9 + 7;
 
int a[N];
set <int> T[4 * N];

void build(int idx, int start, int end) {
  if(start == end) {
    T[idx].insert(a[start]);
    return;
  }

  int middle = (start + end) >> 1;
  build(idx << 1, start, middle);
  build(idx << 1|1, middle + 1, end);

  T[idx].insert(T[idx << 1].begin(), T[idx << 1].end());
  T[idx].insert(T[idx << 1|1].begin(), T[idx << 1|1].end());
}

set <int> query(int idx, int l, int r, int a, int b) {

  set <int> left, right, res;

  if (b < l || a > r) return res; 
  if (a <= l && r <= b) return T[idx];

  left = query(idx << 1, l, (l + r) / 2, a, b); 
  res.insert(left.begin(), left.end()); 
  
  right = query(idx << 1|1, 1 + (l + r) / 2, r, a, b); 
  res.insert(right.begin(), right.end());

  return res;
}

int get(int l, int r, int n) 
{ 
    set<int> ans = query(1, 0, n - 1, l, r); 
    return ans.size();
} 

int main() {
  IO;
  int n; cin >> n;
  for (int i = 0; i < n; ++i)
  {
    cin >> a[i];
  }

  vector < pair<int, int> > limits(N);
  vector <bool> visited;
  vector <int> low(N), node;
  visited.assign(N, false);

  for (int i = 0; i < n; ++i)
  {
    if(!visited[a[i]]) {
      node.push_back(a[i]);
      low[a[i]] = i;
      visited[a[i]] = true;
    }
    else {
      limits[a[i]] = {low[a[i]],i};
    }
  }

  build(1, 0, n - 1);

  int m = node.size();
  map <int,int> cache;
  for (int i = 0; i < m; ++i)
  {
    int getSize = get(limits[node[i]].first, limits[node[i]].second, n);
    cache[node[i]] = getSize;
  }

  for(pair< int,int> f : cache) {
    cout << f.second << ' ';
  }

  return 0;
}
