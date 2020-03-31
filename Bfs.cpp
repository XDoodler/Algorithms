/*
BFS stands for Breadth first search.
A searching technique used to traverse a tree.

Consider the tree with 5 nodes and every (u -> v) edge added.
5
1 3
1 4
4 2
4 5

Tree visual:

	1
       / \
      3   4
         / \
        2   5
	
BFS order.
1 3 4 2 5
*/
const int N = 1e6+6;
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

