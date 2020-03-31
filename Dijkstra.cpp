

const int MOD = 1e9+7;
const int MAX = 1e7;
vector<int> dis;
vector<bool> processed(MAX, false);

const int inf = INFINITY;
void dijkstra(int source){
  priority_queue<pair<int,int>> q;
  q.push({0,source});
  dis.resize(MAX,inf);
  dis[source] = 0;

  while(!q.empty()){
    int u = q.top().second;
    q.pop();
    if(processed[u]) continue;
        processed[u] = true;
    for(auto y : G[u]){
      int v = y.first, w = y.second;
      if(dis[u] + w < dis[v]){
        dis[v] = dis[u] + w;
        q.push(-dis[v],v);
      }
    }
  }
}
int main()
{
  dijkstra(source);
  return 0;
}
