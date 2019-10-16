// CODE ARENA PLAYER
// Problem Link : https://www.hackerearth.com/problem/algorithm/monk-and-square-root/

#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    ll t; 
    cin>>t;
    while(t--){
        ll n, m;
        cin>>n>>m;
        ll ans = -1;
        for(ll i=0; i<m; i++)
            if((i*i)%m == n){
            ans = i;
            break;
        }
        cout<<ans<<endl;
    }
}
