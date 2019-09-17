/*
   Connected Points - Union Find 
   Problem link : https://www.spoj.com/problems/ANTTT/
   Any IDEA why WA ?


*/



#include<bits/stdc++.h>
#define int long long int 
using namespace std;
 
 
vector<int> parent, size;
// Lines intersection code --> https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
struct Point 
{ 
    int x; 
    int y; 
}; 
 
bool onSegment(Point p, Point q, Point r) 
{ 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
       return true; 
  
    return false; 
} 
 
int orientation(Point p, Point q, Point r) 
{  
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
  
    return (val > 0)? 1: 2; // clock or counterclock wise 
}  
bool doIntersect(Point p1, Point q1, Point p2, Point q2) 
{ 
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 
  
    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 
  
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 
  
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 
  
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 
  
    return false; // Doesn't fall in any of the above cases 
} 
 
int getid(int x){
  if(x == parent[x])return x;
  else return parent[x] = getid(parent[x]);
}
 
void unite(int x, int y){
  x = getid(x);
  y = getid(y);
  parent[y] = x;
  size[x] += size[y];
}
int32_t main(){
  int t;
  cin >> t;
  while(t--){
    int n,m,n1,m1;
    int j=0;
    cin >> n >> m;
    n1=n;
    m1=m;
    int x1[n],x2[n],y1[n],y2[n];
    while(n1--){
      cin >> x1[j] >> y1[j] >> x2[j] >> y2[j];
      ++j;
    }
    //process
    parent.resize(n+1,0);
    size.resize(n+1,0);
    for (int i = 1; i <=n; ++i)
    {
      parent[i] = i;
      size[i] = 1;
    }
    for (int i = 0; i < n-1; ++i)
    {
      struct Point p1 = {x1[i],y1[i]}; // p1---p2
      struct Point q1 = {x2[i],y2[i]}; // p1---p2
      struct Point p2 = {x1[i+1],y1[i+1]}; //q1----q2
      struct Point q2 = {x2[i+1],y2[i+1]}; //q1----q2
      if(doIntersect(p1, q1, p2, q2)){
        unite(i+1,i+2);
      }
    }
    while(m--){
      int a,b;
      cin >> a >> b;
      a = getid(a);
      b = getid(b);
      cout << ((a==b)?"YES":"NO") << '\n';
    }
  }
  return 0;
} 
