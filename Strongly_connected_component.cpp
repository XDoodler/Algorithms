/* nuttela - Soham Chakrabarti */

/* problem Link - https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/practice-problems/algorithm/magical-islands/description/ */
/* Solution below */

#include <bits/stdc++.h>
 
using namespace std;
 
#define IO ios_base::sync_with_stdio(false);cin.tie(NULL)
#define all(v) v.begin(),v.end()
#define pb push_back
#define FR(i,j,k) for (ll i=j;i<k;++i)
#define FRR(i,j,k) for (ll i=j;i>=k;--i)
#define ff first
#define ss second
 
typedef long long int ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair <int, int> pii;
 
const int N = 1e5+5;
const int M = 101;
const int inf = INT_MAX;
const int MOD = 1e7+9;
 
int n,m,p,q;
vector<int> G1[N],G2[N];
vector<int> node,lis;
bool v[N];
 
void dfs1(int u)
{
    v[u]=1;
    for(auto &x:G1[u]){
        if(!v[x])dfs1(x);
    }
    node.pb(u);
}
void dfs2(int u)
{
    v[u]=1;
    lis.pb(u);
    for(auto &x:G2[u]){
        if(!v[x])dfs2(x);
    }
    
}
 
int main() {
    IO;
    cin>>n>>m;
    FR(i,0,m)
    {
        cin>>p>>q;
        --p,--q;
        G1[p].pb(q);
        G2[q].pb(p);
    }
 
    memset(v,0,sizeof(v));
    FR(i,0,n){
        if(!v[i])dfs1(i);
    }
    int out=0;
    memset(v,0,sizeof(v));
    reverse(all(node));
    for(int x:node){
        lis.clear();
        if(!v[x]){
            dfs2(x);
            out=max(out,(int)lis.size());
        }
    }
    cout<<out;
    return 0;
}
