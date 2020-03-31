/*    
	      1
	   /	\
	  2	 3
	 /  \
  	4    5 


   Euler Tour : 1 2 4 2 5 2 1 3 1 
   
   Ref : https://www.geeksforgeeks.org/euler-tour-tree/
*/

vector<int> G[MAX], euler_tour;

void dfs(int u,int parent){
	euler_tour.pb(u);
	for(auto x:G[u]){
		if(x==parent)continue;
		dfs(x,u);
		euler_tour.pb(u);
	}
}
