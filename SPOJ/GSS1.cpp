#pragma Gpref optimize("O3")
//#pragma Gpref optimize("Ofast")
//#pragma Gpref target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma Gpref optimize("unroll-loops")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
using namespace std;
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
#define all(x) x.begin(), x.end()
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
const int MOD = (int)1e9+7;
const int MAX = 5e4+4;
typedef pair<int, int> prs;

typedef struct data{
    int sum, pref, suff, ans;
}data;

inline data combine(data l, data r)
{
    data d;
    d.sum = l.sum + r.sum;
    d.pref = max(l.pref, l.sum + r.pref);
    d.suff = max(r.suff, r.sum + l.suff);
    d.ans = max({l.ans,r.ans,l.suff+r.pref});
    return d;
}

inline data mkdata(int v){
    data d;int k=0;
    d.sum = d.pref = d.suff = d.ans = max(k,v);
    return d;
}

data T[4*MAX];vector<int> arr;

void build(int node, int s, int e){
    if(s==e){
        T[node]=mkdata(arr[s]);
        return;
    }
    int mid=(s+e)>>1;
    build(node<<1,s,mid);build(node<<1|1,mid+1,e);
    T[node]=combine(T[node<<1],T[node<<1|1]);
}

data query(int node,int s,int e,int l,int r){
    if(e<l||s>r)return mkdata(0);//no overlap
    if(l<=s&&r>=e)return T[node];//total overlap
    int mid=(s+e)>>1;
    return combine(query(node<<1,s,mid,l,r),query(node<<1|1,mid+1,e,l,r));
}

int32_t main() {
    IOS;
    int n,q;
    scanf("%lld",&n);
    arr.resize(n,0);
    rep(i,0,n)scanf("%lld",&arr[i]);
    build(1,0,n-1);
    scanf("%lld",&q);
    while(q--)
    {
        int l,r;
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",query(1,0,n-1,l-1,r-1).ans);
    }
    return 0;
} 
