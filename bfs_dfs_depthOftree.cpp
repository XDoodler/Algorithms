/*
	Author : Soham Chakrabarti
*/
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+6;
vector<int> t[N];
int visited[N];
int level = -1;
void dfs(int x,int y){
	if(!visited[x])visited[x]=true;
	for(auto i:t[x]){
		if(visited[i])continue;
		cout<<i<<' ';
		dfs(i,x);
	}
}
int bfsAndMaxDepth(int x){
	memset(visited,0,N);
	queue<pair<int,int>> q;
	q.push({x,level});
	while(!q.empty()){
		int n=q.front().first;
		cout<<n<<' ';
		visited[n]=true;
		q.pop();
		int depth=q.front().second;
		level=max(level,depth);
		for(auto i:t[n]){
		if(!visited[i])q.push({i,depth+1});}
	}
}
int32_t main(){
	t[1].push_back(2);t[2].push_back(1);
	t[1].push_back(3);t[3].push_back(1);
	t[1].push_back(4);t[4].push_back(1);
	t[2].push_back(5);t[5].push_back(2);
	t[2].push_back(6);t[6].push_back(2);
	t[3].push_back(7);t[7].push_back(3);
	t[7].push_back(8);t[8].push_back(7);
	t[4].push_back(9);t[9].push_back(4);
	t[4].push_back(10);t[10].push_back(4);
	memset(visited,0,N);
	cout<<"Depth First Search : "<<1<<' ';dfs(1,0);cout<<endl;
	cout << "Breadth First Search : ";bfsAndMaxDepth(1);cout<<endl;
	cout << "Max Depth : " << level << endl;
return 0;
}
