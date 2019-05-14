/*
	Author : Soham Chakrbarti
	SegmentTree 
	1. Sum in range
	2. Minimum number in range

	No updates!
*/
#include <bits/stdc++.h>
using namespace std; 

void build_min_tree(int arr[], int* tree, int start, int end, int ind)
{
	int mid = (start+end)/2;
	if(start == end){
		tree[ind]=arr[start];
		return;
	}

	build(arr, tree, start, mid, 2*ind);
	build(arr,tree, mid+1, end, 2*ind+1);
	tree[ind] = min(tree[2*ind],tree[2*ind+1]);

}

void build_sum_tree(int arr[], int* tree, int start, int end, int ind)
{
	int mid = (start+end)/2;
	if(start == end){
		tree[ind]=arr[start];
		return;
	}

	build(arr, tree, start, mid, 2*ind);
	build(arr,tree, mid+1, end, 2*ind+1);
	tree[ind] = tree[2*ind]+ tree[2*ind+1];

}
int min_in_range (int l, int r, int index, int start, int end ,int* tree)
{
	if(end<l || start>r) return INT_MAX; //no overlap 
	if(l<=start && r>=end) return tree[index]; //total overlap
	int mid = (start+end)/2;
	return min(min_in_range(l, r, 2*index, start, mid, tree),min_in_range(l, r, 2*index+1, mid+1, end, tree));
}

int sum(int l, int r, int index, int start, int end ,int* tree)
{
	if(end<l || start>r) return 0; //no overlap 
	if(l<=start && r>=end) return tree[index]; //total overlap
	int mid = (start+end)/2;
	return sum(l, r, 2*index, start, mid, tree)+ sum(l, r, 2*index+1, mid+1, end, tree);
}
int32_t main(){

	int n;
	cin >> n;
	int arr[n]; //define array
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}
	cout << endl;
	int tree[2*n];
	build_sum_tree(arr, tree, 0, n-1, 1);
	build_min_tree(arr, tree, 0, n-1, 1);


	for (int i = 1; i < 2*n; ++i)
	{
		cout << tree[i] << ' ';
	}
	cout << endl;
	int l,r;
	cout << "Enter lower range and higher range to computer query (0-based indexing) :" << endl;
	cin >> l >> r;
	cout << "Minimum Number in range : " << min_in_range(l,r,1,0,n-1,tree) << endl;
	cout <<"Sum in range : " << sum(l,r,1,0,n-1,tree) << endl;
    return 0;
}
