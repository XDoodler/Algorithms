//Clash Credenz 2019 Wildcard
//Team : Runtime Terror

#include <bits/stdc++.h>

#define ll unsigned long long

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;


const int MOD = 1e9+7;
const int MAX = 1e7;
ll modmul(ll a,ll b){
  ll res = 0;
  a = a % MOD;
  while(b){
    if(b%2){
      res = res + a;
      res %= MOD;
    }
    a = (2 * a)%MOD;
    b = b/2;
  } 
  return res;
}

ll modexp(ll a,ll b){
  ll res = 1;
  a = a % MOD;
  while(b){
    if(b%2){
      res = res * a;
      res %= MOD;
    }
    a = (a * a)%MOD;
    b = b/2;
  } 
  return res;
}
int main()
{
  ll x = 1000;
  ll y = 2000;
  cout << modmul(x,y) << endl;
  cout << modmul(x, modexp(y,MOD-2)) << endl;

  return 0;
}
