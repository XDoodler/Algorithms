//build Tree 
// Let array size be N . Tree Size will not be more than 4N

int tree[4*N];

//build the tree

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        tree[v] = tree[v*2] + tree[v*2+1];
    }
}

// pass build(array , 1 , 0 , N-1)

//sum query
int sum(int a, int b, int k, int x, int y) {
if (b < x || a > y) return 0;
if (a <= x && y <= b) return tree[k];
int d = (x+y)/2;
return sum(a,b,2*k,x,d) + sum(a,b,2*k+1,d+1,y);
}

//Update Query
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1];
    }
}

/*To calculate sum(a,b) 
 We pass */
 int32_t main(){
 while(condition){
 int s = sum(a, b, 1, 0, n-1);
     cout << s << '\n';
 update(1, 0, n-1, position_to_update, new_value);
 }
 
 }
