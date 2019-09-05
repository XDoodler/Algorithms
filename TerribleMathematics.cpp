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
/*int findSplitPoint(int arr[], int n) 
{ 
    int leftSum = 0; 
    for (int i = 0 ; i < n ; i++) 
        leftSum += arr[i];  
    int rightSum = 0; 
    for (int i=n-1; i >= 0; i--) 
    { 
        rightSum += arr[i];  
        leftSum -=  arr[i] ; 
  
        if (rightSum == leftSum) 
            return i ; 
    }  
    return -1; 
} 
//1 2 3 4 5 5
// 1 3 6 10 15 20
// 5 10
// 15 10
bool printTwoParts(int arr[], int n) 
{ 
    int splitPoint = findSplitPoint(arr, n); 
  
    if (splitPoint == -1 || splitPoint == n ) return false; 
    return true;
   
} */



void left(int mat[][N]) 
{ 
    // Consider all squares one by one 
    for (int x = 0; x < N / 2; x++) 
    { 
        // Consider elements in group of 4 in  
        // current square 
        for (int y = x; y < N-x-1; y++) 
        { 
            // store current cell in temp variable 
            int temp = mat[x][y]; 
  
            // move values from right to top 
            mat[x][y] = mat[y][N-1-x]; 
  
            // move values from bottom to right 
            mat[y][N-1-x] = mat[N-1-x][N-1-y]; 
  
            // move values from left to bottom 
            mat[N-1-x][N-1-y] = mat[N-1-y][x]; 
  
            // assign temp to left 
            mat[N-1-y][x] = temp; 
        } 
    } 
} 

void ryt(int mat[][N]) 
{ 
  
    // Traverse each cycle 
    for (int i = 0; i < N / 2; i++) { 
        for (int j = i; j < N - i - 1; j++) { 
  
            // Swap elements of each cycle 
            // in clockwise direction 
            int temp = mat[i][j]; 
            mat[i][j] = mat[N - 1 - j][i]; 
            mat[N - 1 - j][i] = mat[N - 1 - i][N - 1 - j]; 
            mat[N - 1 - i][N - 1 - j] = mat[j][N - 1 - i]; 
            mat[j][N - 1 - i] = temp; 
        } 
    } 
}

int fib(int n,int a, int b) 
{ 
    /* Declare an array to store Fibonacci numbers. */
    int f[n + 1]; 
    int i; 
  
    /* 0th and 1st number of the series are 0 and 1*/
    f[0] = a; 
    f[1] = b; 
    
    cout << f[0] << f[1] << endl;
    for (i = 2; i <= n; i++) { 
        /* Add the previous 2 numbers in the series 
         and store it */
        f[i] = f[i - 1] ^ f[i - 2]; 
        cout << f[i] << endl;
    } 
  
    return f[n]; 
} 

void printSubArray(int A[], int i, int j, int n)
{
    int xx=0;
    if (i < 0 || i > j || j >= n) // invalid input
        return;

    for (int index = i; index < j; index++)
        xx++;
    xx++;
    cccccc=max(cccccc,xx);
}

void calculate(int A[], int n)
{
    // Map to mark elements as visited in the current window
    unordered_map<int, bool> visited;

    // points to left and right boundary of the current window
    // i.e. current window is formed by A[left, right]
    int right = 0, left = 0;

    // loop until right index of the current window is less
    // than the maximum index
    while (right < n)
    {
        // keep increasing the window size if all elements in the
        // current window are distinct
        while (right < n && !visited[A[right]])
        {
            visited[A[right]] = true;
            right++;
        }

        printSubArray(A, left, right - 1, n);

        // As soon as duplicate is found (A[right]), 
        // terminate the above loop and reduce the window's size 
        // from its left to remove the duplicate
        while (right < n && visited[A[right]])
        {
            visited[A[left]] = false;
            left++;
        }
    }
}
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

    
            
            
        /* 
            0 0
            0 0
            0 1
            0 1
            1
            1
            1
            1
            00 0
            10 0
            20 0
            30 0

            

            00
            10
            20
            30
        0 0 
        0 1
        1 0
        1 1

        
        _ _ _

        1 0 _ 1 _

        10010
        10110
        10011
        10111

        0 0 0 
        1 0 0


        2

        101 10101 1 1 1
        1 0 _
        1 0 0 1 0 1 

        1 
        1 2
        2 2
        1 1 2 2
        15 24 32 36 40 48 56 60 64 72 80 84 88 96 100
        TC{
            int N,q;
            cin >> N >> q;
            
            rep(i,0,N){
                rep(j,0,N){
                    cin >> mat[i][j];
                }
            }
            char l;int r;
            while(q--){
                cin >> l;
                if(l=='L'){ cin>>r;
                    rep(i,0,r){



                        for (int x = 0; x < N / 2; x++) 
    { 
        // Consider elements in group of 4 in  
        // current square 
        for (int y = x; y < N-x-1; y++) 
        { 
            // store current cell in temp variable 
            int temp = mat[x][y]; 
  
            // move values from right to top 
            mat[x][y] = mat[y][N-1-x]; 
  
            // move values from bottom to right 
            mat[y][N-1-x] = mat[N-1-x][N-1-y]; 
  
            // move values from left to bottom 
            mat[N-1-x][N-1-y] = mat[N-1-y][x]; 
  
            // assign temp to left 
            mat[N-1-y][x] = temp; 
        } 
    } 


                    }







                }
                else  {cin>>r;
                    rep(i,0,r){


                        // Traverse each cycle 
    for (int i = 0; i < N / 2; i++) { 
        for (int j = i; j < N - i - 1; j++) { 
  
            // Swap elements of each cycle 
            // in clockwise direction 
            int temp = mat[i][j]; 
            mat[i][j] = mat[N - 1 - j][i]; 
            mat[N - 1 - j][i] = mat[N - 1 - i][N - 1 - j]; 
            mat[N - 1 - i][N - 1 - j] = mat[j][N - 1 - i]; 
            mat[j][N - 1 - i] = temp; 
        } 
    } 




                    }}  

                     
                }
                for (int i=0; i<N; i++) 
                    { 
                        for (int j=0; j<N; j++) 
                        cout << mat[i][j] << " "; 
                        cout << endl; 
                    } 
            rep(i,0,N)fill_n(mat[i],0,N);

        }*/
    
    // 1 2 3 6 6
    // 18
    // 2
    // 2 3 5 
    /*int a[n][m];
    rep(i,0,n){
        rep(j,0,m){
            cin >> a[i][j];
        }
    }
    int fl=0;
    rep(i,0,n){
        rep(j,0,m){
            if(a[i][j]){
                if((a[i-1][j]==1&&a[i-1][j-1]==1&&a[i][j-1]==1) || (a[i+1][j]==1&&a[i+1][j-1]==1&&a[i][j-1]==1) || (a[i-1][j+1]==1&&a[i][j+1]==1&&a[i-1][j]==1) ||
                 (a[i+1][j]==1&&a[i][j+1]==1&&a[i+1][j+1]==1)){
                    continue;
                }else {fl=1;break;}
            }
        }
    }
    set<prs> vec;
    rep(i,0,n){
        rep(j,0,m){
            if(a[i][j]==1){
                bool upleft = (a[i-1][j]==1&&a[i-1][j-1]==1&&a[i][j-1]==1);
                bool upright = (a[i+1][j]==1&&a[i+1][j-1]==1&&a[i][j-1]==1);
                bool downleft = (a[i-1][j+1]==1&&a[i][j+1]==1&&a[i-1][j]==1);
                bool downright = (a[i+1][j]==1&&a[i][j+1]==1&&a[i+1][j+1]==1);
                //cout << upleft << upright << downleft << downright << endl;
                if (upleft){int x=i-1,y=j-1;vec.insert({x+1,y+1});} //upleft
                else if (upright){int x=i-1,y=j;vec.insert({x+1,y+1});}
                else if (downleft){int x=i,y=j-1;vec.insert({x+1,y+1});}
                else if (downright){int x=i,y=j;vec.insert({x+1,y+1});}
            }
        }
    }
 
    if(fl)cout<<-1<<endl;else{cout<<vec.size()<<endl;
        for(auto x : vec){
            cout << x.F << ' ' << x.S << endl;
        }}*/

    
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
