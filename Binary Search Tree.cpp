/* nuttela - Soham Chakrabarti */
/*      20
      /    \
     8     22
    / \
   4  12
      / \
     10  14
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
 
const int N = 1e6+1;
const int MAX = 1e6+1; 
const int inf = INT_MAX;
const int mod = 1e9+7;

ll powm(ll a,ll b) {ll res=1LL;while(b) {if(b&1)res=(res*a)%mod;a=(a*a)%mod;b>>=1;}return res;}
ll modmult(ll a,ll b) {ll r=0;a%=mod;while(b){if(b&1)r=(r+a)%mod;a=(a<<1)%mod;b>>=1;}return r;}
ll modexpo(ll a,ll b) {ll r=1;a%=mod;while(b){if(b&1)r=(r*a)%mod;a=(a*a)%mod;b>>=1;}return r;}

ll a[N],b[N];
int found,lca;

class Node {
        int data;
        Node *left,*right;
    public:
        Node():data(0),left(NULL),right(NULL){};
        Node (int val) {
            data=val;
            left=right=NULL;
        }
        /* Insertion in BST */
        Node* insert(Node* rootNode,int val) {
            if(!rootNode) {
                return new Node(val);
            }
            if(rootNode->data > val)
                rootNode->left=insert(rootNode->left, val);
            else 
                rootNode->right=insert(rootNode->right, val);
            return rootNode;
        }

        /* Inorder Print */
        void inorder(Node* rootNode) {
            if(!rootNode)return;
            inorder(rootNode->left);
            printf("%d ",rootNode->data);
            inorder(rootNode->right);
        }

        /* Search Node */
        void search(Node* rootNode,int val) {
            if(!rootNode) return;
            if(rootNode->data==val) {
                printf("%s%d\n","Found -> ",val);
                found=1;
            }
            search(rootNode->left,val);
            search(rootNode->right,val);
        }

        /* Lowest Common Ancestor */

        void LCA(Node* rootNode,int u,int v) {
            if(!rootNode) return;
            // printf("%d\n",rootNode->data);
            if(rootNode->data>u&&rootNode->data>v) {
                LCA(rootNode->left,u,v);
            }
            else if(rootNode->data<u&&rootNode->data<v)
                LCA(rootNode->right,u,v);
            else {
                // printf("LCA:%d\n",rootNode->data);
                lca=rootNode->data;
                return;
            }

        }
    };

int32_t main() {
    io;
    
    Node n,*rootNode=NULL;
    rootNode=n.insert(rootNode,20);
    printf("%s\n","Root Created");

    n.insert(rootNode, 8);
    n.insert(rootNode, 22); 
    n.insert(rootNode, 4); 
    n.insert(rootNode, 12); 
    n.insert(rootNode, 10); 
    n.insert(rootNode, 14);

    printf("%s","Inorder ->");
    n.inorder(rootNode);
    printf("\n");
    found=0;
    int key;
    key=2;
    n.search(rootNode,key);
    if(!found)
        printf("%s%d\n","Not Found -> ",key);
    key=5,found=0;
    n.search(rootNode,key);
    int u,v;
    printf("%s\n","U and V for LCA");
    scanf("%d%d",&u,&v);
    n.LCA(rootNode,u,v);
    printf("%d\n",lca);
    return 0;
}
