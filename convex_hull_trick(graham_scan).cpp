//Convex Hull Trick.


#pragma GCC optimize("O3")
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define ll long long
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define TC int t; cin >> t; while(t--)
#define rep(i,j,k) for(int i=j; i<k; i++)
#define endl '\n'
#define pb push_back
const int MAX = (int)1e5+5;
using namespace std;


vector<int> G[MAX], euler_tour;
 
struct point
{
    int x, y;
 
    point () {}
 
    point(int x, int y) : x(x), y(y) {}
};
 
bool comp(point &p1, point &p2)
{
    if(p1.x!=p2.x)
        return p1.x<p2.x;
    return p1.y<p2.y;
}
 
bool cw(point &a, point &b, point &c)
{
    int area=a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y);
    //cout <<"a.x: "<<a.x <<" a.y: "<<a.y <<" b.x: "<< b.x <<" b.y: "<<b.y <<" c.x: "<<c.x <<" c.y: "<<c.y <<" Area : "<< area<<endl;
    return area<0;
}
 
bool ccw(point &a, point &b, point &c)
{
    int area=a.x*(b.y-c.y) + b.x*(c.y-a.y) + c.x*(a.y-b.y);
    //cout <<"a.x: "<<a.x <<" a.y: "<<a.y <<" b.x: "<< b.x <<" b.y: "<<b.y <<" c.x: "<<c.x <<" c.y: "<<c.y <<" Area : "<< area<<endl;
    return area>0;
}
 
vector<point> convex_hull(vector<point> &v)
{
    if(v.size()==1)
        return v;
 
    sort(v.begin(), v.end(), comp);
 
    point p1=v[0], p2=v.back();
    //cout <<p1.x<<' '<<p1.y<<endl;
    //cout <<p2.x<<' '<<p2.y<<endl;
 
    vector<point> up, down;
    up.push_back(p1);
    down.push_back(p1);
 
    for(int i=1;i<v.size();i++)
    {
        if(i==v.size()-1 || cw(p1, v[i], p2))
        {
            while(up.size()>=2 && !cw(up[up.size()-2], up[up.size()-1], v[i]))
                up.pop_back();
            up.push_back(v[i]);
        }
        if(i==v.size()-1 || ccw(p1, v[i], p2))
        {
            while(down.size()>=2 && !ccw(down[down.size()-2], down[down.size()-1], v[i]))
                down.pop_back();
            down.push_back(v[i]);
        }
    }
 
    for(int i=down.size()-2;i>0;i--)
        up.push_back(down[i]);
 
    return up;
}

int n, m;
vector<point> poly1, poly2, hull1, hull2;
vector<data> v1, v2; 
 
int32_t main()
{
    IOS;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int x, y;
        cin>>x>>y;
        point p(x, y);
        poly1.push_back(p);
    }
    
    hull1=convex_hull(poly1);

    cout<<"--------------"<<endl;

    for(auto h:hull1)cout<<h.x<<' '<<h.y<<endl;
    
    return 0;
}
