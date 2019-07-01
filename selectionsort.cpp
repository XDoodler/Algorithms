#include<bits/stdc++.h>
using namespace std;
int main(){
	int arr[] = {56,89,12,34,90,1,25};
	int n = sizeof(arr)/sizeof(arr[0]),mini;
	for (int i = 0; i < n-1; ++i)
	{
		mini=i;
		for (int j = i+1; j < n; ++j)
		{
			if(arr[mini] > arr[j])mini=j;
		}

		swap(arr[mini], arr[i]);
	}
	for (auto x:arr)
	{
		cout << x <<' ';
	}
	return 0;
}
	
