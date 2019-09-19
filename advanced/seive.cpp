//Clash Credenz 2019 Wildcard
//Team : Runtime Terror

#include <bits/stdc++.h>

#define ll unsigned long long

#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

using namespace std;


const int MOD = 1e9+7;
const int MAX = 1e7;
//ll modmult(ll a,ll b){ll res=0;a%=MOD;while(b){if(b&1)res=(res+a)%MOD;a=(a<<1)%MOD;b>>=1;}return res;}
//ll modexpo(ll a,ll b){ll res=1;a%=MOD;while(b){if(b&1)res=(res*a)%MOD;a=(a*a)%MOD;b>>=1;}return res;

vector<int> primes;
void pre(){ 
  vector<bool> prime;
  prime.resize(MAX,true);

  prime[0] = prime[1] = false;
  for (int i = 2; i <= MAX; ++i)
  {
    if(prime[i] && (long long)i*i <= MAX){
      for (int j = i*i; j <= MAX; j+=i)
      {
        prime[j] = false;
      }
    }
  }

  for (int i = 0; i <= MAX; ++i)
  {
    cout << i << ' ' << prime[i] << endl;
  }

}
int main()
{
  pre();

  return 0;
}
