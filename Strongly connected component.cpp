#include<bits/stdc++.h>

#define int long long
#define FR(i,j,k) for(int i=j;i<k;++i)
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
const int MAX = 1e9;
using namespace std;

vector<int> stck, G[MAX], RG[MAX];
vector<int> component[MAX];
bool vis[MAX];

void dfs1(int u){
  vis[u] = 1;
  for(auto x: G[u]){
    if(!vis[u]) dfs(x);
  }
  stck.push_back(u);
}

void df2(int u, int cnt){
  component[u] = cnt;
  for(auto x:RG[u]){
    if(component[u]==-1) dfs(x,cnt);
  }
}
void sccAddEdge(int u, int v)
{
  G[u].push_back(v);
  RG[v].push_back(u);
}

void ssc(){
  int gp=0;
  FR(i,1,n+1){
    component[i] = -1;
  }
  FR(i,1,n+1){
    if(!vis[i])dfs1(i);
  }
  reverse(stck.begin(), stck.end());
  FR(i,1,n+1){
    if(component[i]==-1){
        dfs2(i,++gp);
    }
  }

}
