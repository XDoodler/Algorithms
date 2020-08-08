/* nuttela - Soham Chakrabarti */

/*
    Using the Binary tree

          10
         /  \
        5   -3
       / \    \
      3   2   11
     / \   \
    3  -2   1

    Built a class TreeNode to maintain the Binary tree structure.

    Methods:

    1. DFS(TreeNode*)
    2. BFS(TreeNode*)
*/


#include <bits/stdc++.h>
 
using namespace std;
 
#define io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define all(v) v.begin(),v.end()
#define pb push_back
#define ins insert
#define rep(i,j,k) for(ll i=j;i<k;i++)
#define per(i,j,k) for(ll i=j;i>=k;--i)
#define scan(a,n) rep(i,0,n)cin>>a[i]
#define input freopen("input.txt","r",stdin)
#define output freopen("output.txt","w",stdout)
#define error freopen("error.txt","w",stderr)
#define ff first
#define ss second
 
typedef long long int ll;
typedef unsigned long long ull;
typedef long double ld;
 
const int N = 2e5+1;
const int MAX = 1e6+1;
const int ALPHA = 26;
const int inf = INT_MAX;
const int mod = 1e9+7;

ll powm(ll a,ll b) {ll res=1LL;while(b) {if(b&1)res=(res*a)%mod;a=(a*a)%mod;b>>=1;}return res;}
ll modmult(ll a,ll b) {ll r=0;a%=mod;while(b){if(b&1)r=(r+a)%mod;a=(a<<1)%mod;b>>=1;}return r;}
ll modexpo(ll a,ll b) {ll r=1;a%=mod;while(b){if(b&1)r=(r*a)%mod;a=(a*a)%mod;b>>=1;}return r;}

ll a[N], b[N];

class TreeNode {
public:
    int val;
    TreeNode *left, *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
    void dfs(TreeNode* root) {
        if(root) {
            cout << (root->val) << " ";
            dfs(root->left);
            dfs(root->right);
        }
    }

    void bfs(TreeNode* root) {
        if(!root) return;
        queue<TreeNode* > q;
        q.push(root);
        while(!q.empty()) {
            cout << (q.front()->val) << ' ';
            TreeNode* tmp = q.front();
            q.pop();
            if(tmp) {
                if(tmp->left)q.push(tmp->left);
                if(tmp->right)q.push(tmp->right);
            }
        }
    }
};

int main() {
    io;
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(-3);
    root->right->right = new TreeNode(11);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(2);
    root->left->right->right = new TreeNode(1);
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(-2);

    cout << "DFS : " ;
    root->dfs(root);
    cout << endl;

    cout << "bfs : " ;
    root->bfs(root);
    cout << endl;

    return 0;
}
