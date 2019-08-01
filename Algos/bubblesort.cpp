#include<bits/stdc++.h>
using namespace std;
int main(){
	int arr[] = {56,89,12,34,90,1,25};
	int n = sizeof(arr)/sizeof(arr[0]);
	for (int i = 0; i < n-1; ++i)
	{
		for (int j = 0; j < n-i-1; ++j)
		{
			if(arr[j] > arr[j+1])swap(arr[i],arr[j]);
		}
	}
	for (auto x:arr)
	{
		cout << x <<' ';
	}
	return 0;
}
	
