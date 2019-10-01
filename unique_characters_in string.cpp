
#Problem Link and Solution : https://codeforces.com/contest/1234/submission/61672539
#Codeforces D

#include<bits/stdc++.h>
 
#define ll long long
#define ld long double
 
#define FR(i,j,k) for(int i=j;i<k;++i)
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
 
const int MAX = 1e5+5;
const int MOD = 1e9+7;
 
using namespace std;

string arr;
vector<vector<int>> T(4*MAX, vector<int>(26));
void build(int node,int s,int e){
    if(s==e){
        T[node][arr[s]-'a']++;
        return;
    }
    int m=(s+e)>>1;
    build(node<<1,s,m);
    build(node<<1|1,m+1,e);
    FR(i,0,26)T[node][i]=T[node<<1][i] + T[node<<1|1][i];
}
vector<int> query(int node,int s,int e,int l,int r){
  vector<int> a(26);
  if(e<l || s>r) return a; //no overlap 
  if(l<=s && r>=e) return T[node];
  int mid = (s+e)>>1;
  vector<int> a1 = query(node<<1,s,mid,l,r);
  vector<int> a2 = query(node<<1|1,mid+1,e,l,r);
  FR(i,0,26)a[i] = a1[i] + a2[i];
  return a;

}
void upd(int node,int s,int e,int p,char new_val){
    if(s == e){
    T[node][arr[p] - 'a'] --;
    T[node][new_val - 'a'] ++;
    arr[p]=new_val;
    }
    else
    {
        int mid = (s+e)>>1;
        if(p <= mid)
        {
            upd(node<<1, s, mid, p, new_val);
        }
        else
        {
            upd(node<<1|1, mid+1, e, p, new_val);
        }
        FR(i,0,26){T[node][i]=T[node<<1][i] + T[node<<1|1][i];}
    }
}
int32_t main() {
IOS;
cin>>arr;
int ln=arr.length();
build(1,0,ln-1);
int q;
cin>>q;
while(q--){
  int x;
  cin>>x;
  if(x==1){
    int p;char ch;
    cin>>p>>ch;
    upd(1,0,ln-1,p-1,ch);
  }else{
    int l,r;
    cin>>l>>r;
    vector<int> res = query(1,0,ln-1,l-1,r-1);
    int an=0;
    FR(i,0,26){if(res[i]>0)an++;}
      cout<<an<<endl;
  }
}
return 0;
}
