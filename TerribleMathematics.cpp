#pragma Gpref optimize("O3")
//#pragma Gpref optimize("Ofast")
//#pragma Gpref target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma Gpref optimize("unroll-loops")
#include <bits/stdc++.h>
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
using namespace std;
 
const int MOD = (int)1e9+7;
const int MX = 105;
const int N=105;
typedef pair<int, int> prs;
int mat[MX][MX];

int cccccc=INT_MIN;

int bitstodec(string n,int m) 
{ 
    string num = n; 
    int dec_value = 0;  
    int base = 1; 
    int len = num.length(); 
    for (int i = len - 1; i >= 0; i--) { 
        if (num[i] == '1') 
            dec_value += base; 
        base = base * 2;
        base%=m; dec_value%=m;
    } 
  
    return dec_value%m; 
}
int32_t main(){
    //freopen("ic1.txt", "r", stdin);
    //freopen("oc1.txt", "w", stdout);
    IOS;
    TC{
        int n,k,len,c=0,y,z;
        cin >> n >> k;
        string s;cin >> s;
        len=s.length();
        rep(i,0,len){
            if(s[i] == '_')c++;
        }
        int x=pow(2,c);int gg=x;
        char bits[gg][c];
        rep(i,0,c){
            x/=2;y=x,z=x;
            rep(j,0,gg){
                if(y!=0 && z!=0){bits[j][i]='0';y--;}
                else {bits[j][i]='1';z--;}
                if(y==0&&z==0){y=x;z=x;}
            }
        }
int cnt=0;
        rep(i,0,gg){
            string ss="";int hh=0;
            rep(j,0,n){
                if(s[j]=='_')ss+=(bits[i][hh++]);else ss+=s[j];
            }
            //cout<<ss<<endl;
            if(bitstodec(ss,k)%k==0)cnt++;
        }cout<<cnt<<endl;

        rep(i,0,gg)fill_n(bits[i],0,c);
    }

    return 0;
}
/*  
    1 1 1
    1 1 1
    0 1 1
 
    0 0 0
    0 0 0
    0 0 0 
    1 1 0
    1 1 0
    0 0 0
 
    1 1 0 1 1
    1 1 0 1 1
 
    
    x-1y-1  xy-1 x+1y-1
    x-1y    xy  x+1y
    x-1y+1  xy+1 x+1y+1
10 20 11 
00
 
21 22
 
00 01 02
10 11 12
20 21 22
/*#include<bits/stdc++.h>
using namespace std;
 
int main()
{   
    freopen("i3.txt", "w", stdout);
 
    srand(time(NULL));
 
    std::random_device rd;
    std::mt19937 eng(rd()); 
    std::uniform_int_distribution<> distr(1, 100);
    static const char generator[] = "abcdefghijklmnopqrstuvwxyz";
    static const char leet[] = "12";
 
    int tc = 10;
  
    cout << tc << '\n';
 
    while(tc--)
    {
        //10000 + rand() % (( 100000 + 1 ) - 10000);
        //cout << len << endl;
 
        //struct timeval time;
        ///gettimeofday(&time,NULL);
        //srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
 
        const int maxN = 100000;
        const int N = rand() % maxN + 1;
 
        cout << N << endl;
        int x = -100000000, y = 10000000;
        for (int i = 0; i < N; ++i)
        {
            cout << x + rand() % (( y + 1 ) - (x))<< ' ';
        }cout << endl;
 
            vector<int> nodeIds;
            for (int i = 1; i <= N; i++)
            {
                nodeIds.push_back(i);
            }
            random_shuffle(nodeIds.begin(), nodeIds.end());
 
            vector<int> usedNodeIds = { nodeIds.back() };
            nodeIds.pop_back();
 
            for (int i = 0; i < N - 1; i++)
            {
                const int newNodeId = nodeIds.back();
                const int oldNodeId = usedNodeIds[rand() % usedNodeIds.size()];
 
                cout << newNodeId << " " << oldNodeId << endl;
 
                usedNodeIds.push_back(newNodeId);
                nodeIds.pop_back();
            }
 
 
        /*char s[len];
        for (int i = 0; i < len; ++i) s[i] = generator[rand() % (sizeof(generator) - 1)];
 
        for (int i = 0; i < len; ++i)cout << s[i];
        cout << '\n';
 
        int query = 100000;//10000 + rand() % (( 100000 + 1 ) - 10000);
        //min + rand() % (( max + 1 ) - min);
 
        cout << query << '\n';
        while(query--)
        {
            char task =  leet[rand() % (sizeof(leet) - 1)];
 
            if(task == '1')
            {
                int l,r;
                l = 1 + rand() % (( N + 1 ) - 1);
                r = x + rand() % (( y + 1 ) - (x));
                cout << 1 << ' ' << l << ' ' << r << '\n';
            }
 
            else
            {
                int p;
                p = 1 + rand() % (( N + 1 ) - 1);
                cout << 2 << ' ' << p << '\n';
 
            }
        }
    
    }
    return 0;
}




  12 1 2 3 4 6 12  4-2 2

  24 1 2 3 4 6 12 24  5-2 = 3
    

    1 2 3 4 6 12
    1 2 3 4 6 8 12 24

    1 2 3 5 10 15 30
  1 3 9 18

  14 28

  1 2 7 14
  1 2 7 14 28

  odd even = even
  even even = even


  3 4 7 3 4 7
  0 1 2 3 4 5
  0 1 2 0 1 2


  325 265 76 325 265 76
  0    1   2  3   4   5  


  1 1 2 2 3 4 



  11
  12
  13
  1 4 1 4 9

  1 - 13
  4 - 24
  9 - 5

  1 1 2 2

  1-12
  2-34

  1 2 3 2 4 1 5

  1 - 16
  2 - 24
  3 - 3
  4 - 5
  5 - 7

  1 2 4 6

  0 1 2 4


*/
