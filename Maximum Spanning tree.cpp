#include<bits/stdc++.h>
using namespace std;
int tests;
int n,m;
int a[1<<20],b[1<<20],c[1<<20];
vector<pair<int, int> > v;
int w[1<<20];
int ans;
int get(int x)
{
	if (x==w[x])
		return x;
	return w[x]=get(w[x]);
}
void merge(int a,int b)
{
	w[a]=b;
}
int main(){
ios_base::sync_with_stdio(0);
cin>>tests;
for (;tests;--tests)
{
	cin>>n>>m;
	v.clear();
	for (int i=1;i<=m;i++)
	{
		cin>>a[i]>>b[i]>>c[i];
		v.push_back(make_pair(c[i],i));
	}
	sort(v.begin(),v.end());
	reverse(v.begin(),v.end());
	for (int i=1;i<=n;i++)
		w[i]=i;
		
	ans=0;
	
	for (int i=0;i<v.size();i++)
	{
		int id=v[i].second;
		int q,w;
		q=a[id];
		w=b[id];
		q=get(q);
		w=get(w);
		if (q!=w)
		{
			ans+=c[id];
			merge(q,w);
		}
	}
	cout<<ans<<endl;
}
return 0;}
