/*
Depth First Search is a technique to traverse a tree or a graph.

*/

/* DFS of a Directed tree/graph */
const int M = 1e6+6;

vector<int> G[M]; 
vector<bool> vis(M);

void dfs(int u) 
{  
	vis[u] = true;
	cout << u << endl;
	for(int child : G[u])
	{
		if(!vis[child])
			dfs(child);
	}
} 

/* DFS of a Undirected tree/graph */
void dfs(int u, int par) 
{  
	cout << u << endl;
	for(int child : G[u])
	{
		if(child != par)
			dfs(child);
	}
}

