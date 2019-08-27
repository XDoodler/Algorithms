/*

Segment Trees (Hard)
Using Policy based data structures...
https://www.spoj.com/problems/ORDERSET

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
const int MAX = 1e5+1;;
typedef pair<int, int> prs;


int n,k,q,rem,cnt=0,ll,rr;
int T[4*MAX];
vector<int> arr;
vector<int> parent,size;

/*void pre(int n){
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

void build(int node,int s,int e){
    if(s==e){
        T[node] = arr[s]%k;
        return;
    }
    int m=(s+e)>>1;
    build(node<<1,s,m);
    build(node<<1|1,m+1,e);
    if(T[node<<1]%k==0)ll=;
    if(T[node<<1|1]%k==0)rr=1;
    T[node]=ll+rr;
}
int query(int node,int s,int e,int l,int r){
    if(e<l || s>r) return 0; //no overlap 
    if(l<=s && r>=e) return T[node]; //total overlap
    int mid = (s+e)>>1;
    int lft = ((query(node<<1,s,mid,l,r)));
    int ryt = ((query(node<<1|1,mid+1,e,l,r)));
    if(lft==rem)cnt++;
    return (lft+ryt);
}
void upd(int node,int s,int e,int p,int new_val){
    if(s == e)T[node] +=new_val;
    else
    {
        int mid = (s + e)/2;
        if(p <= mid)
        {
            upd(2*node, s, mid, p, new_val);
        }
        else
        {
            upd(2*node+1, mid+1, e, p, new_val);
        }
        T[node] = (T[2*node]+T[2*node+1]);
    }
}*/
int32_t main(){
	//freopen("ic1.txt", "r", stdin);
	//freopen("oc1.txt", "w", stdout);
 	IOS;
       int q;
       cin >> q;
       ordered_set st; 
       while(q--){
        char ch;int x;
        cin >> ch >> x;
        if(ch == 'I'){
            st.insert(x);
        }
        if(ch == 'D'){
            if(st.find(x)!=st.end())st.erase(st.find(x));
        }
        if(ch == 'K'){
            if(x>st.size())cout<<"invalid"<<endl;
            else cout << *(st.find_by_order(x-1))  << endl;
        }   
        if(ch == 'C'){
            cout << st.order_of_key(x)  << endl; 
        }
       }

	   
		/* 

            8 =  1 2 4 8 k=4 k'=4 0 
            9 = 1 3 9 k=3 k'=2 1
            10 = 1 2 5 10  k=4 k2 2

        1 2 
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
	x-1y	xy  x+1y
	x-1y+1	xy+1 x+1y+1
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

1. Toposorting
2. SQRT
*/
