#include <iostream>
#include<vector>
using namespace std;
int get_superparent(int x,vector<int>arr,vector<int>par){
    if(par[x]==x)return x;
    else{
        return par[x]=get_superparent(par[x],arr,par);
    }
}
void union_func(int a,int b,int &component,vector<int>arr,vector<int> &par){
    int x=get_superparent(a,arr,par);
    int y=get_superparent(b,arr,par);
    // cout<<"superParent of "<<a<<" is "<<x<<endl;
    // cout<<"superparent of "<<b<<" is "<<y<<endl;

    if(x!=y){
        par[x]=y;
        component-=1;
    }
}
int main() {
    int n,q,a,b,component;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)cin>>arr[i];
    component=n;
    vector<int> par(n);
    for(int i=0;i<n;i++)par[i]=i;
    cin>>q;
    //mark superParent and parent of each node is self
    for(int i=0;i<q;i++){
        cin>>a>>b;
        union_func(a,b,component,arr,par);
    }
    cout<<component<<endl;
}
