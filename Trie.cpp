/* nuttela - Soham Chakrabarti */

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

class Trie{
    bool isEnd;
    Trie* t[ALPHA];
    public:
         Trie() {
            isEnd = false;
            rep(i,0,ALPHA)t[i]=NULL;
        }

        // Insert a Word into the Trie
        void insertWord(string word) {
            Trie* root = this;
            for (int i = 0; i < word.size(); ++i) {
                int idx = word[i] - 'a';
                if (root->t[idx] == NULL)
                    root->t[idx] = new Trie();
                root = root->t[idx];
            }
            root->isEnd = true;
        }

        // Search a Word in the trie
        bool searchWord(string word) {
            Trie* root = this;
            for (int i = 0; i < word.size(); ++i) {
                int idx = word[i] - 'a';
                if (root->t[idx] ==  NULL) return false;
                root = root->t[idx];
        }
        
        return root->isEnd;
        }

        // Check if any word has the 'prefix' 
        bool hasPrefix(string prefix) {
            Trie* root = this;
            bool present = true;
            if(root == NULL) return false;
            for (int i = 0; i < prefix.size(); ++i) {
                int idx = prefix[i] - 'a';
                if(root->t[idx] == NULL) {
                    present = false;
                    break;
                }
                root = root->t[idx];

            }
            return present;
        }
    };

int32_t main() {
    io;
    Trie* obj = new Trie();
    obj->insertWord("Apple");

    cout << "Search the Word -> 'App' : "<< (obj->searchWord("App")?"Present":"Not present") << endl;
    cout << "Search the Word -> 'Apple' : "<< (obj->searchWord("Apple")?"Present":"Not present") << endl;
    cout << "Search the Word -> 'Appleo' : "<< (obj->searchWord("Appleo")?"Present":"Not present") << endl;

    cout << "Prefix -> 'App' : "<< (obj->hasPrefix("App")?"Present":"Not present") << endl;
    cout << "Prefix -> 'Apple' : "<< (obj->hasPrefix("Apple")?"Present":"Not present") << endl;
    cout << "Prefix -> 'Appleo' : "<< (obj->hasPrefix("Appleo")?"Present":"Not present") << endl;
    return 0;
}
