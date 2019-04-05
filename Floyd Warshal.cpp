#include <bits/stdc++.h>
/* author : Soham Chakrabarti
   codechef : nuttela
   codeforces : xdoodler
   
   Floyd Warshal
*/
#define int long long
using namespace std;

const int N = 1e6+6;

int dist[N][N];

void floydWarshall(){
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				distance[i][j] = min(distance[i][j],
				distance[i][k]+distance[k][j]);
			}
		}
	}
}	
int32_t main()
{
	//inputs and call floydWarshall() 
	return 0;
}

