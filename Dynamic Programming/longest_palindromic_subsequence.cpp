// Not handling overlapping subproblems

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

//GLOBAL VARIABLES
string st;

int solve(int first, int last){
  if(first == last) 
    return 1;

  if (st[first] ==  st[last] && first + 1 == last)
    return 2;

  if(st[first] ==  st[last])
    return solve(first + 1, last - 1) + 2;

    return max(solve(first, last-1),solve(first+1, last));
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
  int n;
  cin >> n;
  cin >> st;
  int get = solve(0,n-1);

  //cout << get.length() << '\n';
  cout << get;

//}

nuttela();
 
return 0;
}

// 3 4 5 6 7  11
// 10 3 5  13 5
// 7 9 11  16 11


// 7 9 10 3 3 
// 11 6 5 5


// (10 7 3) (4 3 9) (5 5 11) (6)
// (6 5 11) (5 3 9) (4 10 7) (3)


// 7  11
//    9
// 

/*
1 0 #
2 2 !
3 1
4 0 
5 4
6 (3) !
7 (9)
8 1 
9 0 #


1111
11123
111112


*/
// 4 

