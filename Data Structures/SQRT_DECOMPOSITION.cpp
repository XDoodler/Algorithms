/*
 SQRT-DECOMP

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
int32_t main(){
 	IOS;
       
        int n,q,x,y,z;
        cin >> n;
        arr.resize(n,0);
        input_arr.resize(n,0);
        rep(i,0,n)cin>>input_arr[i];
        build_SQRT_DECOMPED_TREE(n);
        cin >> q;
        while(q--){
            cin >> x >> y >> z;
            if(x==1){
                SQRT_update(y,z);
            }else cout << SQRT_query(y,z) <<endl;
        }

	
	return 0;
}

