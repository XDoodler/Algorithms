//Lowest common ancestor.

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const int MAX = (int)1e4+1;

int n, m, u, v, sz;
vector<int> G[MAX], euler, first(MAX), height(MAX), tree(8*MAX);

void dfs(int u, int h = 0) {
    height[u] = h;
    first[u] = euler.size();
    euler.pb(u);
    for(int v : G[u]) {
        dfs(v, h+1);
        euler.pb(u);
    }
}

void build(int node, int l, int r) {
    if(l == r) {
        tree[node] = euler[l];
        return;
    }
    int m = (l+r)>>1;
    build(node<<1, l, m);
    build(node<<1|1, m+1, r);
    int a = tree[node<<1], b = tree[node<<1|1];
    tree[node] = height[a] < height[b] ? a : b;
}

int query(int node, int l, int r, int p, int q) {
    if(r < p || l > q)
        return -1;
    if(l >= p && r <= q)
        return tree[node];
    int m = (l+r)>>1;
    int a = query(node<<1, l, m, p, q), b = query(node<<1|1, m+1, r, p, q);
    if(a == -1)
        return b;
    if(b == -1)
        return a;
    return height[a] < height[b] ? a : b;
}

int lca(int u, int v) {
    u = first[u], v = first[v];
    if(u > v) swap(u, v);
    return query(1, 0, sz, u, v);
}

int main() {
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> m;
        for(int j = 0; j < m; ++j) {
            cin >> u;
            G[i].pb(u); // G[i+1] for 1-based indexing
        }
    }
    dfs(0); // dfs(1) for 1-based indexing
    sz = (int)euler.size() - 1;
    build(1, 0, sz);
    int q;
    cin >> q;
    while(q--) {
        cin >> u >> v;
        cout << lca(u, v) << '\n';
    }
    return 0;
}



// Problem Link : https://www.spoj.com/problems/LCASQ/
