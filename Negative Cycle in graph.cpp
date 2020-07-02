int a[MAX][MAX];

bool negativeCycle() //Returns true if there is a negative cycle
{
    vector<int> dis(n, 0);
    rep(k,1,n) {
        rep(i,0,n) {
            rep(j,0,n) {
                if(dis[i]+a[i][j]<dis[j]) {
                    dis[j]=dis[i]+a[i][j];
                }
            }
        }
    }
    rep(i,0,n) {
            rep(j,0,n) {
                if(dis[i]+a[i][j]<dis[j]) {
                    return true;
            }
        }
    }
    return false;

}



//Problem : https://www.codechef.com/PROC2020/problems/TIMET
// Solution : https://www.codechef.com/viewsolution/34924252
