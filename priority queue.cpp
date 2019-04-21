priority_queue<int, vector<int>, greater<int>> Q;
//to input elements in a non-increasing order 

priority_queue<int> Q;
//to input elements in a non-decreasing order

	Q.push(X);
  //insert element
  
  int32_t main()
  { 
    for (int i = 0; i < N; i++)
		{
			cin >> X;
			Q.push(X);
			cout << Q.top() << " ";
		}
    
    return 0;
  }
  
  /*
  -------------------------------------------------------------------------------------------------------------------------
  
  Problems : https://www.codechef.com/problems/TSECJ05
  Solution : https://www.codechef.com/viewsolution/23672310
  
  Problem : https://www.codechef.com/problems/PEWDSVTS
  Solution : https://www.codechef.com/viewsolution/24063781
  */
