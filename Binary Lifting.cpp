/*

Binary Lifting is an algorithm that is used in finding the Lowest Common ancestor of two nodes in a tree.
Below is the clean implementation of the algorithm.

For ref : https://www.geeksforgeeks.org/lca-in-a-tree-using-binary-lifting-technique/

*/
int n,m,q,mx;
const int MAX = 1e5+5;
typedef pair<int, int> pairs;
const int LG = ceil(log2(MAX));

vector<vector<int>> up(MAX, vector<int>(LG+1));
vector<int> G[MAX];

void dfs(int u,int par){
    up[u][0] = par;
    for(int i = 1; i <= LG; i++){
        up[u][i]=up[up[u][i-1]][i-1];
    }
    for(auto x : G[u]){
        if(x!=par)dfs(x,u);
    }
}

