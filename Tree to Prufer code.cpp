/*
  Tree to Prufer Code
  Complexity: O(VlogV)
 */

vector<int> treeToPrufercode (int nodes, vector<pair<int,int>> &edges) {
    unordered_set<int> neighbors[nodes+1]; // For each node, who is it's neighbor?

    for( int i = 0; i < edges.size(); i++ ) {
        pair<int,int> edge = edges[i];
        int u = edges[i].first; int v = edges[i].second;
        neighbors[u].insert(v);
        neighbors[v].insert(u);
    }

    priority_queue<int> leaves;
    for ( int i = 0; i <= nodes; i++ ) {
        if (neighbors[i].size() == 1 ) {
            leaves.push(-i); // Negating since we need min heap
        }
    }
    vector<int> pruferCode;
    int need = nodes - 2;
    while(need--) {
        int leaf = -leaves.top(); leaves.pop();
        int neighborOfLeaf = *(neighbors[leaf].begin());
        pruferCode.push_back(neighborOfLeaf);
        // Remove the leaf
        neighbors[neighborOfLeaf].erase(leaf);
        // The neighbor can become a new leaf
        if(neighbors[neighborOfLeaf].size() == 1) {
            leaves.push(-neighborOfLeaf);
        }
    }
    return pruferCode;
}
