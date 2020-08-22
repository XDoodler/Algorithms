/* Faced the problem in GOCC 21 SWE Google Grad */

/* You are given two arrays A and B (consider 1-based indexed). Both have N integers. 
You are given M list of pairs of indices, whose val can be swapped in array A only.

For example (i, j) 1 <= i, j <= N , you can swap a[i] and a[j] 

The hamming distance between two arrays is the count of indexes where A[i] NOT equal to B[i].

You can swap the M pairs (as many times as you want, includung zero), Find the minimum Hamming Distance.


Input :

N, M
Array A
Array B
.
.
.M pairs

Output :

Single Integer(H. D)
I/O displayed at end.

Code Below ->
*/


/* nuttela - Soham Chakrabarti */

#include <bits/stdc++.h>
 
using namespace std;
 
#define io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define all(v) v.begin(),v.end()
#define pb push_back
#define ins insert
#define rep(i,j,k) for(ll i=j;i<k;i++)
#define per(i,j,k) for(ll i=j;i>=k;--i)
#define scan(a,n) rep(i,0,n)cin>>a[i]
#define input freopen("input.txt","r",stdin)
#define output freopen("output.txt","w",stdout)
#define error freopen("error.txt","w",stderr)
#define ff first
#define ss second
 
typedef long long int ll;
typedef unsigned long long ull;
typedef long double ld;
 
const int N = 1e6+1;
const int MAX = 1e6+1;
const int ALPHA = 26;
const int inf = INT_MAX;
const int mod = 1e9+7;

ll powm(ll a,ll b) {ll res=1LL;while(b) {if(b&1)res=(res*a)%mod;a=(a*a)%mod;b>>=1;}return res;}
ll modmult(ll a,ll b) {ll r=0;a%=mod;while(b){if(b&1)r=(r+a)%mod;a=(a<<1)%mod;b>>=1;}return r;}
ll modexpo(ll a,ll b) {ll r=1;a%=mod;while(b){if(b&1)r=(r*a)%mod;a=(a*a)%mod;b>>=1;}return r;}

ll a[MAX], b[MAX];
vector<ll> g[MAX], vis1(MAX), vis2(MAX);
multiset<int> el;
int ans;

void dfs1(int u) {
    vis1[u]=1;
    el.insert(a[u]);
    for(auto &x:g[u]) {
        if(!vis1[x])dfs1(x);
    }
}

void dfs2(int u) {
    vis2[u]=1;
    if(el.count(b[u])) {
        el.erase(el.lower_bound(b[u]));
    }
    else
        ++ans;
    for(auto &x:g[u]) {
        if(!vis2[x])dfs2(x);
    }
}

int32_t main() {
    io;
    // input; output;
    int t;
    cin>>t;
    while(t--) {
        int n,m;
        ans=0;
        el.clear();
        cin>>n>>m;
        scan(a,n);
        scan(b,n);
        rep(i,0,m) {
            int u,v;
            cin>>u>>v;
            --u,--v;
            if(u!=v) {
                g[u].pb(v);
                g[v].pb(u);
            }
        }

        rep(i,0,n) {
            if(!vis1[i]) {
                dfs1(i);
                dfs2(i);
                el.clear();
            }
        }
        rep(i,0,MAX) {
            g[i].clear();
            vis1[i]=vis2[i]=0;
        }
        cout<<ans<<endl;
    }
    return 0;
}

/*
Input 
6
5 4
1 5 9 2 3
2 4 5 1 3
1 4
2 3
3 5
2 5
6 5
8 8 6 5 4 8
5 3 8 2 6 8
6 1
4 5
6 3
2 1
2 4
6 5
4 8 8 2 7 10
5 5 7 10 7 7
3 4
3 6
2 2
3 5
5 3
5 2
1 9 8 5 1
4 10 1 7 8
1 4
4 1
8 2
9 7 1 4 10 7 9 10
10 1 7 8 9 4 6 4
6 2
6 6
7 2
5 9 3 10 9 5 5
2 10 1 8 9 2 1
3 6
1 5


output:
1
2
4
5
8
6

*/
