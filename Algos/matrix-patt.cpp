/*
	author : nuttela
*/
#include<bits/stdc++.h>
#define LL long long int
using namespace std;

int32_t main()
{
	int n;
	cin >> n;
	for(int j=0; j<=n-1; j+=2)
	{
		for(int i=1; i<=n; i++){
			cout << (i + n * j) << " * ";
		}cout << endl;
	}
	int k = (n%2)? 2:1;

	for(int j=n-k; j>=1; j-=2)
	{
		for(int i=1; i<=n; i++){
		cout << (i + n * j) << " * ";
		}	cout << endl;
	}
	
	
	return 0;
}

/*-----------------------------------------------------OUTPUT---------------------------------------------------------------
N=4

1 * 2 * 3 * 4 * 
9 * 10 * 11 * 12 * 
13 * 14 * 15 * 16 * 
5 * 6 * 7 * 8 * 

N=5
1 * 2 * 3 * 4 * 5 * 
11 * 12 * 13 * 14 * 15 * 
21 * 22 * 23 * 24 * 25 * 
16 * 17 * 18 * 19 * 20 * 
6 * 7 * 8 * 9 * 10 * 

*/
