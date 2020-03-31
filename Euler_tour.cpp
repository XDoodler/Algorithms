
vector<int> G[MAX], euler_tour;

void dfs(int u,int parent){
	euler_tour.pb(u);
	for(auto x:G[u]){
		if(x==parent)continue;
		dfs(x,u);
		euler_tour.pb(u);
	}
}
int main() {
	IOS;
	G[1].push_back(2);G[2].push_back(1);
	G[1].push_back(3);G[3].push_back(1);
	G[2].push_back(4);G[4].push_back(2);
	G[2].push_back(5);G[5].push_back(2);
	dfs(1,0);
	rep(i,0,euler_tour.size())cout<<euler_tour[i]<<' ';cout<<endl;
    return 0;
}


/*    
	      1
	   /	\
	  2	 3
	 /  \
  	4    5 


   Euler Tour : 1 2 4 2 5 2 1 3 1 
*/
