#pragma Gpref optimize("O3")
//#pragma Gpref optimize("Ofast")
//#pragma Gpref target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma Gpref optimize("unroll-loops")
#include <bits/stdc++.h>
#define int long long
#define ld long double
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define TC int t; cin >> t; while(t--)
#define rep(i,j,k) for(int i=j; i<k; i++)
#define rep_(i,j,k) for(int i=j; i>=k; --i)
#define pb push_back
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define F first
#define S second
using namespace std;
 
const int MOD = (int)1e9+7;
const int MX = 105;
const int N=105;
typedef pair<int, int> prs;
int mat[MX][MX];

int cccccc=INT_MIN;

int bitstodec(string n,int m) 
{ 
    string num = n; 
    int dec_value = 0;  
    int base = 1; 
    int len = num.length(); 
    for (int i = len - 1; i >= 0; i--) { 
        if (num[i] == '1') 
            dec_value += base; 
        base = base * 2;
        base%=m; dec_value%=m;
    } 
  
    return dec_value%m; 
}
int32_t main(){
    //freopen("ic1.txt", "r", stdin);
    //freopen("oc1.txt", "w", stdout);
    IOS;
    TC{
        int n,k,len,c=0,y,z;
        cin >> n >> k;
        string s;cin >> s;
        len=s.length();
        rep(i,0,len){
            if(s[i] == '_')c++;
        }
        int x=pow(2,c);int gg=x;
        char bits[gg][c];
        rep(i,0,c){
            x/=2;y=x,z=x;
            rep(j,0,gg){
                if(y!=0 && z!=0){bits[j][i]='0';y--;}
                else {bits[j][i]='1';z--;}
                if(y==0&&z==0){y=x;z=x;}
            }
        }
int cnt=0;
        rep(i,0,gg){
            string ss="";int hh=0;
            rep(j,0,n){
                if(s[j]=='_')ss+=(bits[i][hh++]);else ss+=s[j];
            }
            if(bitstodec(ss,k)%k==0)cnt++;
        }cout<<cnt<<endl;

        rep(i,0,gg)fill_n(bits[i],0,c);
    }

    return 0;
}
