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

/*
N=4
*/
