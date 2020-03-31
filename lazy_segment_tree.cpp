void build(int node,int s,int e){
    if(s==e){
        T[node] = arr[s];
        return;
    }
    int m=(s+e)>>1;
    build(node<<1,s,m);
    build(node<<1|1,m+1,e);
    T[node]=(T[node<<1]+T[node<<1|1]);
}
int query_tree(int node, int a, int b, int i, int j) {
  
  if(a > b || a > j || b < i) return 0; // Out of range

  if(lazy[node] != 0) { // This node needs to be updated
    T[node] += lazy[node]; // Update it

    if(a != b) {
      lazy[node*2] += lazy[node]; // Mark child as lazy
      lazy[node*2+1] += lazy[node]; // Mark child as lazy
    }

    lazy[node] = 0; // Reset it
  }

  if(a >= i && b <= j) // Current segment is totally within range [i, j]
    return T[node];

  int q1 = query_tree(node*2, a, (a+b)/2, i, j); // Query left child
  int q2 = query_tree(1+node*2, 1+(a+b)/2, b, i, j); // Query right child

  int res = (q1+ q2); // Return final result
  
  return res;
}
void upd(int node,int a,int b,int i, int j,int value){
if(lazy[node] != 0) { // This node needs to be updated
      T[node] += lazy[node]; // Update it

    if(a != b) {
      lazy[node*2] += lazy[node]; // Mark child as lazy
          lazy[node*2+1] += lazy[node]; // Mark child as lazy
    }

      lazy[node] = 0; // Reset it
    }
  
  if(a > b || a > j || b < i) // Current segment is not within range [i, j]
    return;
    
    if(a >= i && b <= j) { // Segment is fully within range
        T[node] += value;

    if(a != b) { // Not leaf node
      lazy[node*2] += value;
      lazy[node*2+1] += value;
    }

        return;
  }

  upd(node*2, a, (a+b)/2, i, j, value); // Updating left child
  upd(1+node*2, 1+(a+b)/2, b, i, j, value); // Updating right child

  T[node] = (T[node*2] + T[node*2+1]); // Updating root with max value
}
