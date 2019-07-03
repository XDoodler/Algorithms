#include <bits/stdc++.h>
using namespace std;

int bell(int x)
{
	int bell[x+1][x+1];
	bell[0][0] = 1;
	for (int i = 1; i <= x; ++i)
	{
		bell[i][0] = bell[i-1][i-1];
		for (int j = 1; j <= x; ++j)
		{
			bell[i][j] = bell[i][j-1] + bell[i-1][j-1];
		}
	}
	return bell[x][0];
}
int main()
{
	int n;
	cin>>n;
	cout<<bell(n)<<endl;
	return 0;
}
