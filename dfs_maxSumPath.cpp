#include <bits/stdc++.h> 
#define LL unsigned long long
#define F first
#define S second
#define MAX 100000
using namespace std; 
 
vector<LL> Tree[MAX]; 
vector<LL> arr;
int dp[10000];


// algorithm to fetch the path with maximum sum


void dfs(int u, int parent) 
{  
    dp[u] = arr[u - 1]; 
    int maximum = 0; 
    for (int child : Tree[u]) {  
        if (child == parent) 
            continue;  
        dfs(child, u); 
        maximum = max(maximum, dp[child]); 
    }  
    dp[u] += maximum; 
} 

int32_t main(){
//input the adjacency list and node weight array
cout << dp[1] << endl;
}
/*
----------------------------------------------------------------------------------------------------------------------------
Problem : https://www.codechef.com/problems/NUTMONEY
Solution : https://www.codechef.com/viewsolution/23763911

*/
