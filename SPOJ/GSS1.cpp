/*
 Status WA.
 Problem Link : https://www.spoj.com/problems/GSS1/
 
 What am I missing? HELP NEEDED!
*/



#pragma Gpref optimize("O3")
//#pragma Gpref optimize("Ofast")
//#pragma Gpref target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma Gpref optimize("unroll-loops")
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
using namespace std;
#define int long long
#define ld long double
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define TC int t; cin >> t; while(t--)
#define rep(i,j,k) for(int i=j; i<k; i++)
#define rep_(i,j,k) for(int i=j; i>=k; --i)
#define pb push_back
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define F first
#define S second 
#define all(x) x.begin(), x.end()
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
const int MOD = (int)1e9+7;
const int MAX = 1e5+5;
typedef pair<int, int> prs;

int SET = 1073741823;
int n,k,q,rem,cnt=0,ll,rr;
int T[4*MAX];
vector<int> arr, input_arr,blocks;
vector<int> parent,size;    
int block_size;
/*
void pre(int n){
    parent.resize(n+1,0);size.resize(n+1,0);
    rep(i,1,n+1){
        parent[i] = i;
        size[i] = 1;
    }
}
int find_parent(int v){
     if (v == parent[v])
        return v;
    return parent[v] = find_parent(parent[v]);
}
void union_set(int a,int b){
    a = find_parent(a);
    b = find_parent(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}
*/
void build(int node,int s,int e){
    if(s==e){
        T[node] = arr[s];
        return;
    }
    int m=(s+e)>>1;
    build(node<<1,s,m);
    build(node<<1|1,m+1,e);
    int total_sum=T[node<<1]+T[node<<1|1];
    int max_sum=max(T[node<<1],T[node<<1|1]);
    T[node]=max(total_sum,max_sum);
}
int query(int node,int s,int e,int l,int r){
    if(e<l || s>r) return 0; //no overlap 
    if(l<=s && r>=e) return T[node]; //total overlap
    int mid = (s+e)>>1;
    return (query(node<<1,s,mid,l,r)+query(node<<1|1,mid+1,e,l,r));
}

/*
void upd(int node,int s,int e,int p,int new_val){
    if(s == e)T[node] = new_val;
    else
    {
        int mid = (s+e)>>1;
        if(p <= mid)
        {
            upd(node<<1, s, mid, p, new_val);
        }
        else
        {
            upd(node<<1|1, mid+1, e, p, new_val);
        }
        T[node] = max(T[node<<1],T[node<<1|1]);
    }
}

void SQRT_update(int index, int val){
    int blk = index/block_size;
    blocks[blk] += (val - input_arr[index]);
    input_arr[index] = val;
}

int SQRT_query(int l, int r){
int sum = 0; 
    while (l<r and l%block_size!=0 && l!=0) 
    { 
        sum += input_arr[l]; 
        l++; 
    } 
    while (l+block_size <= r) 
    { 
        sum += blocks[l/block_size]; 
        l += block_size; 
    } 
    while (l<=r) 
    { 
        sum += input_arr[l]; 
        l++; 
    } 
    return sum;
}

void build_SQRT_DECOMPED_TREE(int n){
    block_size = ceil(sqrt(n));
    blocks.resize(block_size,0);
    int index_of_block = -1;
    rep(i,0,n){
        if(i % block_size==0){
            index_of_block++; 
        }

        blocks [index_of_block] += input_arr[i];
    }
}
*/
int32_t main(){
    //freopen("ic1.txt", "r", stdin);
    //freopen("oc1.txt", "w", stdout);
    IOS;
       
        int n,q,x,y,z,t;
        cin >> n;
        arr.resize(n,0);
        //input_arr.resize(n,0);
        rep(i,0,n)cin>>arr[i];
        build(1,0,n-1);
        //build_SQRT_DECOMPED_TREE(n);
        cin >> q;
        while(q--){
            cin >> x >> y;
            cout << query(1,0,n-1,x-1,y-1) <<endl;
        }
        return 0;
    }
