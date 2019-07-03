#include<bits/stdc++.h> 
using namespace std; 
vector<int> v;
void subsetSums(int arr[], int l, int r, int sum=0) 
{ 
	if (l > r) 
	{ 
      	v.push_back(sum);
		return; 
	} 
	subsetSums(arr, l+1, r, sum+arr[l]); 
	subsetSums(arr, l+1, r, sum); 
} 

// Driver code 
int main() 
{ 
	int arr[] = {3,8,10}; 
	int n = sizeof(arr)/sizeof(arr[0]),s=0,p; 
	subsetSums(arr, 0, n-1); 

  	for(int i=0;i<n;i++) s+=arr[i]; s=s/2;
  	sort(v.begin(),v.end());
  	for(auto x:v){
      if(x>s){p=x;break;}
    }
  	cout << p << endl;
	return 0; 
} 
