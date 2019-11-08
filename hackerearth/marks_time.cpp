/* nuttela Code Arena Player */


#pragma Gpref optimize("O3")
//#pragma Gpref optimize("Ofast")
//#pragma Gpref target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma Gpref optimize("unroll-loops")
#include <bits/stdc++.h>
#define int long long
#define ld long double
#define ull unsigned long long 
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define TC int t; cin >> t; while(t--)
#define FR(i,j,k) for(int i=j; i<k; i++)
#define FRI(i,j,k,l) for(int i=j; i<k; i+=l)
#define BFR(i,j,k) for(int i=j; i>=k; --i)
#define BFRI(i,j,k,l) for(int i=j; i>=k; i-=l)
#define pb push_back
#define mp make_pair
#define vi vector<int>
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define pi pair<int,int>
#define F first
#define S second
 
 
using namespace std;
const int MOD = (int)1e9+7;
const int N = 1e5+1;
const int M  = 32;
 
int modmul(int a,int b){int res=0;a%=MOD;while(b){if(b&1)res=(res+a)%MOD;a=(a<<1)%MOD;b>>=1;}return res;}
int power(int x,unsigned int y){int res=1;x=x%MOD;while(y>0){if(y&1)res=(res*x)%MOD;y=y>>1;x=(x*x)%MOD;}return res;}
int modexpo(int a,int b){int res=1;a%=MOD;while(b>0){if(b%2==1)res=(res*a)%MOD;a=(a*a)%MOD;b/=2;}return res%MOD;}
int nCr(int n,int r){int res=1;if(r>n>>1)r=n-r;FR(i,0,r){res=(res*(n-i))%MOD;res=(res*modexpo(i+1,MOD-2))%MOD;}return res;}
 

clock_t time_c=clock();
 
void nuttela()
{
    time_c = clock()-time_c;
    cerr<< " Time : "<<(float)(time_c)/CLOCKS_PER_SEC<<"\n";
}

bool is(int n) 
{ 
   if(n==0) 
   return false; 
  
   return (ceil(log2(n)) == floor(log2(n))); 
}
int phi(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if(n > 1)
        result -= result / n;
    return result;
}
int32_t main(){
//Online JUDGE starts
#ifndef ONLINE_JUDGE
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
freopen("error.txt", "w", stderr);
#endif
//Online JUDGE ends32

IOS;

//pre();
//TC{
  //CODE BEGINS
  int n, q;
  cin >> n >> q;
  vi time(n), marks(n), f;
  multimap <int,int, greater<int>> value;
  FR(i,0,n) cin >> time[i];
  FR(i,0,n) cin >> marks[i];

  FR(i,0,n) value.insert({marks[i],time[i]});
  for(auto &x:value)f.pb(x.S);
  
  FR(i,1,n)f[i] += f[i-1];
  
  while(q--){
    int k; cin >> k;
    cout << f[k-1]; cout << '\n';
  }

//}
nuttela();
 
return 0;
}
