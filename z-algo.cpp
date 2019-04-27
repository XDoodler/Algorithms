vector<int> z_function(string &s)
{
	int n=s.size();
	vector<int> z(n);
	for(int i=1,l=0,r=0;i<n;i++)
	{
		if(i<=r)
			z[i]=min(r-i+1, z[i-l]);
		while(i+z[i]<n && s[z[i]]==s[i+z[i]])
			z[i]++;
		if(i+z[i]-1>r)
			l=i, r=i+z[i]-1;
	}
	return z;
}

/*
/*
Problem : https://www.hackerrank.com/challenges/max-array-sum/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming
Solution : https://www.hackerrank.com/challenges/max-array-sum/submissions/code/105428447?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=dynamic-programming

Given an array of integers, find the subset of non-adjacent elements with the maximum sum. Calculate the sum of that subset.

For example, given an array arr=[2 , 1, 3 ,-4 , 5]  we have the following possible subsets:

Subset      Sum
[-2, 3, 5]   6
[-2, 3]      1
[-2, -4]    -6
[-2, 5]      3
[1, -4]     -3
[1, 5]       6
[3, 5]       8

output : 8
*/

text  = a b c b c a c d e x y
pattern = abc

new string = a b c ($) a b c b c a c d e x y

now perform z algorithm to fetch the number of times the pattern exixts in the array! 
*/
