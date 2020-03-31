
const int M = 1e6+6;

vector<int> G[M]; 
vector<bool> vis(M);

void dfs(int u) 
{  
	if(vis[u])return;
	vis[u]=true;
	cout << u << endl;
	for(int child:G[u])
	{
		if(!vis[child])dfs(child);
	}
} 
