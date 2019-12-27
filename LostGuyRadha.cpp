/* nuttela - Soham Chakrabarti */

#include <bits/stdc++.h>

using namespace std;

#define IO ios_base::sync_with_stdio(false);cin.tie(NULL);
#define endl '\n'

typedef long long ll;
typedef long double ld;
typedef pair <int, int> pii;

const int N = 1e3;
const int inf = INT_MAX;
const int MOD = 1e9 + 7;

int main() {
  ll tt; cin >> tt;
  while(tt--) {
    int n, q;
    cin >> n >> q;
    int f[n];
    set <int> a;
    for (int i = 0; i < n; ++i)
    {
      int x;
      cin >> x;
      a.insert(x);
      f[i] = *--a.end(); //last element of set
    }
    for (int i = 0; i < q; ++i)
    {
      int x;
      cin >> x;
      cout << f[x - 1] << endl;
    }
  }
  return 0;
}
