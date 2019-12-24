/* nuttela - Soham Chakrabarti */
// Problem Link : https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/weighted-string/
// Difficulty : Easy
// Masking of maps

#include <bits/stdc++.h>

using namespace std;

#define IO ios_base::sync_with_stdio(false);cin.tie(NULL);

typedef long long ll;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int main() {
  int tt; cin >> tt;
  while(tt--) {
    int k; cin >> k;
    string st; cin >> st;

    int ln = st.length(), f[ln];
    for (int i = 0; i < ln; ++i)
    {
      f[i] = (st[i] - 'a') + 1;
    }
    unordered_map <int, int> ump;
    int res = 0, curr = 0;
    for (int i = 0; i < ln; ++i)
    {
      curr += f[i];

      if (curr == k)++res;
      if (ump.find(curr-k)!=ump.end())res+=ump[curr-k];
      ++ump[curr];
    }
    cout << res << endl;
  }
  
  return 0;
}

// 1 2 3 4 5 6
