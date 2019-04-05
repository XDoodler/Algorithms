/* author : Soham Chakrabarti
   codechef : nuttela
   codeforces : xdoodler
   
   Floyd Warshal
*/
#define int long long
using namespace std;

const int N = 1e6+6;
vector<int> adj[N];
bool vis[N];

void dfs(int s) {
if (vis[s]) return;
vis[s] = true;
for (auto u: adj[s]) {
dfs(u);
}
}

int32_t main(){
//input adjacency list and dfs( _starting node_)
dfs(1);
return 0;
}
