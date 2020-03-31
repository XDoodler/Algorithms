#include<bits/stdc++.h>
const int N = 1e6+6;
using namespace std;
int vis[N], g[N]
void bfs()
{
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int node = q.front();
        	cout << node << endl;
		vis[node]=1; 
		q.pop();
		for(auto it:g[node])
		{
			if(!vis[it])q.push(it);
		}
	} 
}

