/* nuttela - Soham Chakrabarti */
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define all(v) v.begin(),v.end()
#define pb push_back
#define ins insert
#define rep(i,j,k) for(ll i=j;i<k;i++)
#define per(i,j,k) for(ll i=j;i>=k;--i)
#define in freopen("input.txt","r",stdin);
#define out freopen("output.txt","w",stdout);
#define ff first
#define ss second
 
typedef long long int ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair <ll,ll> pll;
 
const int N = 1e5 + 5;
const int M = 1e5 + 5;
const int inf = INT_MAX;
const int MOD = 1e9 + 7;

vector<int> primes;
ll nI[N],fI[N],fact[N];

ll max(ll a,ll b){return a>b?a:b;}
ll min(ll a,ll b){return a<b?a:b;}
ll gcd(ll a,ll b){while(b){ll t=a;a=b;b=t%b;}return a;}     
ll lcm(ll a,ll b){return (max(a,b)/gcd(a,b))*min(a,b);}
ll power(ll a,ll b){ll r=1;while(b){if(b&1)r*=a;a=a*a;b>>=1;}return r;}
bool isPrime(ll n){if(n<=1)return 0;if(n<=3)return 1;if(n%2==0||n%3==0)return 0;for(ll i=5;i*i<=n;i+=6)if(n%i==0||n%(i+2)==0)return 0;return 1;}
void find_primes(ll n=100000000){ll limit=floor(sqrt(n))+1;vector<int> test;test.pb(2),primes.pb(2);for(ll i=3;i<limit;i+=2)if(isPrime(i))test.pb(i),primes.pb(i);ll lo=limit,hi=2*limit;bool p[limit];while(lo<n){if(hi>n)hi=n;memset(p,true,sizeof(p));for(int i=0;i<test.size();++i){ll mn=(lo/test[i])*test[i];if(mn<lo)mn+=test[i];for(ll j=mn;j<hi;j+=test[i])p[j-lo]=0;}rep(i,0,limit)if(p[i] && i+lo<hi)primes.pb(i+lo);lo+=limit,hi+=limit;}}
ll modmult(ll a,ll b){ll r=0;a%=MOD;while(b){if(b&1)r=(r+a)%MOD;a=(a<<1)%MOD;b>>=1;}return r;}
ll modexpo(ll a,ll b){ll r=1;a%=MOD;while(b){if(b&1)r=(r*a)%MOD;a=(a*a)%MOD;b>>=1;}return r;}
ll nCr(ll n,ll r){ll res=1;if(r>n>>1)r=n-r;rep(i,0,r){res=(res*(n-i))%MOD;res=(res*modexpo(i+1,MOD-2))%MOD;}return res;}
void binomial_pre(){nI[0]=nI[1]=fI[0]=fI[1]=fact[0]=1;rep(i,2,N)nI[i]=nI[MOD%i]*(MOD-MOD/i)%MOD;rep(i,2,N)fI[i]=(nI[i]*fI[i-1])%MOD;rep(i,1,N)fact[i]=(fact[i-1]*i)%MOD;}
ll binomial(ll n,ll r){if(n<r)return 0;return ((fact[n]*fI[r])%MOD*fI[n-r])%MOD;}

int32_t main() {
    io;
    // in;out;
    int t;
    cin>>t;
    while(t--) {
    	//code goes here

    }
    return 0;
}
