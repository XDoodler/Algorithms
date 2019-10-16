//CODE ARENA PLAYER
// Problem Link 

#pragma Gpref optimize("O3")
//#pragma Gpref optimize("Ofast")
//#pragma Gpref target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma Gpref optimize("unroll-loops")
#include <bits/stdc++.h>
#define int unsigned long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define TC int t; cin >> t; while(t--)
#define FR(i,j,k) for(int i=j; i<k; i++)
#define BFR(i,j,k) for(int i=j; i>=k; --i)
#define pb push_back
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define go continue
#define F first
#define S second
using namespace std;
 

const int MOD = (int)1e9+7;
const int N = 1e8+8;
vector<int> fact;

int32_t main(){
IOS;
int n;
cin >> n;
vector<int> v(n);
FR(i,0,n)cin >> v[i];
int fl=0;
FR(j,2,N){
fl=0;
int x = v[0]%j;
FR(i,1,n){
int y = v[i]%j;
if(x!=y){fl=1;break;}
}
if(!fl)cout << j << ' ';}
return 0;
}

