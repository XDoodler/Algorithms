/* nuttela - Soham Chakrabarti */
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define IO ios_base::sync_with_stdio(false); cin.tie(NULL);
#define endl '\n';
 
typedef long long ll;
typedef long double ld;
 
const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int price[N];

int main() {
  IO;
  // total peices
  int n; cin >> n;
  for (int i = 1; i < (n + 1); ++i)
  {
    cin >> price[i]; //cost per peice
  }

  // required length
  int k; cin >> k;

  int L[n + 1][k + 1];

  for (int i = 0; i < (n + 1); ++i)
  {
    for (int j = 0; j < (k + 1); ++j)
    {
      if(i == 0 || j == 0) {
        L[i][j] = 0;
      }
      else if(i > j) {
        L[i][j] = L[i - 1][j];
      }
      else {
        L[i][j] = max (L[i][j - i] + price[i], L[i - 1][j]);
      }
    }
  }

  cout << L[n][k];

  return 0;
}
