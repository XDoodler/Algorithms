/* 
   codechef : nuttela
   
   Disjoint Set Unions (Union Find and Path Compression
*/

#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6+6;

int parent[N], size[N];

//find the parent
int find(int x) {
    return x == parent[x] ? x : parent[x] = find(parent[x]);
}

//unite , merge and change parent
void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if(a == b) return;
    if(size[a] < size[b]) swap(a,b);
    size[a] += size[b];
    parent[b] = a;
}

int32_t main() {
    for (int i = 1; i <= 5; ++i) {
	parent[i] = i;
	size[i] = 1;
    }

    //process DSUs over the array and compute
    //unite(1,2); 
    //unite(1,5);
    //unite(5,4);
    return 0;
}
