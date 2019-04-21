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
text  = a b c b c a c d e x y
pattern = abc

new string = a b c ($) a b c b c a c d e x y

now perform z algorithm to fetch the number of times the pattern exixts in the array! 
*/
