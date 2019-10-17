//CODE ARENA PLAYER
// Maximum Spanning Tree : https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/maximum-spanning-tree/

#include <bits/stdc++.h>
 
#define L first
#define R second
#define LL long long
#define PB push_back
#define MP make_pair
#define Size(c) ((int)(c).size())
#define For(i, c) for(__typeof(c.begin()) i=c.begin();i!=c.end();++i)
 
using namespace std;
typedef pair<int, int> pie;
typedef pair<int, pie> pii;
const int Maxn=1e6+1000;
 int Par[Maxn], High[Maxn]; 
 
int getpar(int fi){
  if(Par[fi]==fi)
    return fi;
  else
    return Par[fi]=getpar(Par[fi]);
}
void Merge(int fi, int se){
  fi=getpar(fi); se=getpar(se);
  if(High[fi]>High[se])
    swap(fi, se);
  if(High[fi]==High[se]){
    Par[fi]=se;
    High[se]++;
  }else
    Par[fi]=getpar(se);
}
int main(){
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--){
int n, m, Min_Weight = 0; 
vector<pii> Edges;
  for(int i=1;i<Maxn;i++)
    Par[i]=i,High[i] = 0;
  cin>>n>>m;
  while(m--){
    int Fi, Se, Th;
    cin>>Fi>>Se>>Th;
    Edges.PB(MP(Th, MP(Fi, Se)));
  }
  sort(Edges.begin(), Edges.end());
  for(int i=Size(Edges)-1;i>=0;i--){
    int Fi=Edges[i].R.L, Se=Edges[i].R.R, Th=Edges[i].L;
    if(getpar(Fi) != getpar(Se)){
      //Res.PB(MP(Fi, Se));
      Min_Weight+=Th;
      Merge(Fi, Se);
    }
  }
  cout<<Min_Weight<<endl;
 // For(i, Res)
   // cout<<i->L<<" "<<i->R<<endl;
}
}
