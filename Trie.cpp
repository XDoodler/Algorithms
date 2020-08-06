/* nuttela - Soham Chakrabarti */


/* void insert(string) -> insert a lowercase string into the trie*/
/* bool search(string) -> search a  string is present/not present in the trie*/
/* bool prefix(string) -> search a prefix of a string is present/not present in the trie*/
/* bool searchAdvanced(string) -> search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.*/


/*
    Below Code is entire in C++
    Used a Class named Trie, with data members (isEnd), Trie* t[26]
    and member functions mentioned above with their params(...) and work.

    Explaintain of a trie with helpful Snippets: https://leetcode.com/problems/implement-trie-prefix-tree/solution/
    You can solve the problem as well. ;)
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


struct Trie{
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

        bool dfsTrie(Trie* root, string word, int index, int len) {
            if(index == len)
                return root->isEnd; // end of string search

            if(word[index] != '.') {
                if(root->t[word[index]-'a'])
                    return dfsTrie(root->t[word[index]-'a'], word, index+1, len);
                else 
                    return false;
            }
            
            for (int i = 0; i < 26; ++i) {
                if(root->t[i])
                    if(dfsTrie(root->t[i], word, index+1, len)) return true;
            }
            return false;
        }

        bool searchAdvanced(string word) {
            Trie* root = this;
            int sz = word.size();
            return dfsTrie(root, word, 0, sz);
        }
    };

int main() {
    io;
    Trie* obj = new Trie();

    obj->insertWord("apple");
    obj->insertWord("bunny");
    obj->insertWord("buck");

    cout << "Search the Word -> 'app' : "<< (obj->searchWord("app")?"Present":"Not present") << endl;
    cout << "Search the Word -> 'apple' : "<< (obj->searchWord("apple")?"Present":"Not present") << endl;
    cout << "Search the Word -> 'appleo' : "<< (obj->searchWord("appleo")?"Present":"Not present") << endl;

    cout << "Prefix -> 'app' : "<< (obj->hasPrefix("app")?"Present":"Not present") << endl;
    cout << "Prefix -> 'apple' : "<< (obj->hasPrefix("apple")?"Present":"Not present") << endl;
    cout << "Prefix -> 'appleo' : "<< (obj->hasPrefix("appleo")?"Present":"Not present") << endl;

    cout << "searchAdvanced -> '.uck' : "<< (obj->searchAdvanced(".uck")?"Present":"Not present") << endl;
    cout << "searchAdvanced -> 'a.p.e' : "<< (obj->searchAdvanced("a.p.e")?"Present":"Not present") << endl;
    cout << "searchAdvanced -> 'bunn.' : "<< (obj->searchAdvanced("bunn.")?"Present":"Not present") << endl;


    return 0;
}

/*

 Output:
    Search the Word -> 'app' : Not present
    Search the Word -> 'apple' : Present
    Search the Word -> 'appleo' : Not present
    Prefix -> 'app' : Present
    Prefix -> 'apple' : Present
    Prefix -> 'appleo' : Not present
    searchAdvanced -> '.uck' : Present
    searchAdvanced -> 'a.p.e' : Present
    searchAdvanced -> 'bunn.' : Present

*/
