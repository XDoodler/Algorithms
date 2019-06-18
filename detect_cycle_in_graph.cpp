vector<int> G[M]; 
bool vis[M];
bool rescursuionStack[M];
int cycle=0;
bool detectCycle(int u, int parent) 
{  
	if(!vis[u]){
		vis[u]=true;rescursuionStack[u]=true;
	}
	for(int child:G[u])
	{
		if(!vis[child] && detectCycle(child, u))return true;
		else if(rescursuionStack[child]) {return true;}
	}
	rescursuionStack[u]=false;
	return false;
} 
