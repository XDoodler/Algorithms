//CODE ARENA PLAYER
// Problem Link : https://www.hackerearth.com/practice/basic-programming/implementation/basics-of-implementation/practice-problems/algorithm/sherlock-and-date/

#include <iostream>
using namespace std;
 
//fnction to get previous date
void getPrevDate(int *day,int *month, int *year)
{
	//if there is first day of month
	if(*day==1)
	{
		//months which have 30 days in previous month
		if(*month==4|| *month==6|| *month==9|| *month==11)
		{
			*day=31;
			*month = *month -1;	
		}
		//for MARCH, to define february last day
		else if(*month==3)
		{
			if(*year%400==0 || *year%4==0)	
				*day=29;
			else
				*day=28;
			
			*month = *month -1;
		}
		//for January, to define December last day
		else if(*month==1)
		{
			*day=31;
			*month = 12;
			*year = *year - 1 ;
		}
		//for Feb, to define January last day
		else if(*month==2)
		{
			*day=31;
			*month = *month -1;
		}
		//for other months
		else
		{
			*day=30;
			*month = *month -1;
		}
	}
	//other days of month
	else
	{
		*day = *day-1;
	}	
 
}
 
int main()
{
    int t;
    cin >> t;
    string arr[12] = {"January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November" , "December"};
    while(t--){
        
        //date, assigning day, month and year
	    int dd=0,mm=0,yy=0;
	    string mm1;
	    cin >> dd >> mm1 >> yy;
	    for(int i=0; i<12; i++){
	        if(arr[i] == mm1){
	            mm = i+1;break;
	        }
	    }
	    //function call to get previous date
	    getPrevDate(&dd,&mm, &yy);
	    //printing previous date
	    
	       cout<<dd<<" "<<arr[mm-1]<<" "<<yy<<'\n';
    }
	
	
	return 0;    
}
