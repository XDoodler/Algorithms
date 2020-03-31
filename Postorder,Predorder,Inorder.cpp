#include<bits/stdc++.h>

using namespace std;  
void postorder(int a[], vector<int> &v,  int n, int index) 
{ 
    if(index >= n) 
        return; 
    postorder(a, v, n, 2 * index + 1); 
    postorder(a, v, n, 2 * index + 2); 
    v.push_back(a[index]);
}
void inorder(int a[], vector<int> &v,  int n, int index) 
{ 
    if(index >= n) 
        return; 
    inorder(a, v, n, 2 * index + 1); 
    v.push_back(a[index]);
    inorder(a, v, n, 2 * index + 2); 
    
}
void preorder(int a[], vector<int> &v,  int n, int index) 
{ 
    if(index >= n) 
        return; 
    v.push_back(a[index]);
    preorder(a, v, n, 2 * index + 1); 
    preorder(a, v, n, 2 * index + 2); 
} 

int32_t main()
{	
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n=7;

    int a[]={ 5, 6, 7, 8, 9, 10, 11};

    cout<<"Original Series"<<endl;

    for (int i = 0; i < n; ++i)
    {
    	cout<<a[i]<<' ';
    }
    cout<<endl;

    vector<int> v;
    
    inorder(a, v, n, 0);

    cout<<"INORDER :"<<'\n';

    for (int i = 0; i < n; ++i)
    {
    	cout<<v[i]<<' ';
    }
    v.clear();

    cout<<endl;

    cout<<"PREORDER :"<<'\n';

    preorder(a, v, n, 0);

    for (int i = 0; i < n; ++i)
    {
    	cout<<v[i]<<' ';
    }
    v.clear();

    cout<<endl;

    cout<<"POSTORDER :"<<'\n';

    postorder(a, v, n, 0); 

    for (int i = 0; i < n; ++i)
    {
    	cout<<v[i]<<' ';
    }
    v.clear();

    cout<<endl;
	return 0;
}	
