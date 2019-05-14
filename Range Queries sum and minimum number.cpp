/*
	Author : Soham Chakrbarti
	SegmentTree 
	1. Sum in range
	2. Minimum number in range
	
	Update Segment tree as well.
*/
#include <bits/stdc++.h>
using namespace std; 

void build_min_tree(int arr[], int* tree_min, int start, int end, int ind)
{
	int mid = (start+end)/2;
	if(start == end){
		tree_min[ind]=arr[start];
		return;
	}

	build_min_tree(arr, tree_min, start, mid, 2*ind);
	build_min_tree(arr,tree_min, mid+1, end, 2*ind+1);
	tree_min[ind] = min(tree_min[2*ind],tree_min[2*ind+1]);

}

void build_sum_tree(int arr[], int* tree_sum, int start, int end, int ind)
{
	int mid = (start+end)/2;
	if(start == end){
		tree_sum[ind]=arr[start];
		return;
	}

	build_sum_tree(arr, tree_sum, start, mid, 2*ind);
	build_sum_tree(arr,tree_sum, mid+1, end, 2*ind+1);
	tree_sum[ind] = tree_sum[2*ind]+ tree_sum[2*ind+1];

}
int min_in_range(int l, int r, int index, int start, int end ,int* tree_min)
{
	if(end<l || start>r) return INT_MAX; //no overlap 
	if(l<=start && r>=end) return tree_min[index]; //total overlap
	int mid = (start+end)/2;
	return min(min_in_range(l, r, 2*index, start, mid, tree_min), min_in_range(l, r, 2*index+1, mid+1, end, tree_min));
}

int sum(int l, int r, int index, int start, int end ,int* tree_sum)
{
	if(end<l || start>r) return 0; //no overlap 
	if(l<=start && r>=end) return tree_sum[index]; //total overlap
	int mid = (start+end)/2;
	return sum(l, r, 2*index, start, mid, tree_sum)+ sum(l, r, 2*index+1, mid+1, end, tree_sum);
}

void update_sum(int index, int start, int end, int position, int new_val, int* tree_sum)
{
	if(start == end)
	{
		tree_sum[index] = new_val;
	}
	else
	{
		int mid = (start + end)/2;
		if(position <= mid)
		{
			update_sum(2*index, start, mid, position, new_val, tree_sum);
		}
		else
		{
			update_sum(2*index+1, mid+1, end, position, new_val, tree_sum);
		}
		tree_sum[index] = tree_sum[2*index]+tree_sum[2*index+1];
	}
	
}
void update_min(int index, int start, int end, int position, int new_val, int* tree_min)
{
	if(start == end)
	{
		tree_min[index] = new_val;
	}
	else
	{
		int mid = (start + end)/2;
		if(position <= mid)
		{
			update_min(2*index, start, mid, position, new_val, tree_min);
		}
		else
		{
			update_min(2*index+1, mid+1, end, position, new_val, tree_min);
		}
		tree_min[index] = min(tree_min[2*index],tree_min[2*index+1]);
	}
	
}
int32_t main(){

	int n;
	cin >> n;
	int arr[n]; //define array
	for (int i = 0; i < n; ++i)
	{
		cin >> arr[i];
	}
	int tree_sum[4*n];
	int tree_min[4*n];
	build_sum_tree(arr, tree_sum, 0, n-1, 1);
	build_min_tree(arr, tree_min, 0, n-1, 1);
	int l,r, pos, new_value,l1,r1;
	cout << "Enter lower range and higher range to computer query (0-based indexing) :" << endl;
	cin >> l >> r;
	cout << "Minimum Number in range : " << min_in_range(l,r,1,0,n-1,tree_min) << endl;
	cout <<"Sum in range : " << sum(l,r,1,0,n-1,tree_sum) << endl;
	cout << "Enter position and Value to be updated :" << endl;
	cin >> pos >> new_value;
	update_sum(1, 0, n-1, pos, new_value, tree_sum);
	update_min(1, 0, n-1, pos, new_value, tree_min);
	cout << "Updated Sum Tree###" << endl;
	for (int i = 1; i < 2*n; ++i)
	{
		cout << tree_sum[i] << ' ';
	}cout << endl;
	cout << "Updated Min Tree###" << endl;
	for (int i = 1; i < 2*n; ++i)
	{
		cout << tree_min[i] << ' ';
	}
	cout << endl;
	cout << "Enter lower range and higher range to computer query (0-based indexing) :" << endl;
	cin >> l >> r;
	cout << "Minimum Number in range : " << min_in_range(l,r,1,0,n-1,tree_min) << endl;
	cout <<"Sum in range : " << sum(l,r,1,0,n-1,tree_sum) << endl;
    return 0;
}
