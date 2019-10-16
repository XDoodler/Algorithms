//CODE ARENA PLAYER
// Problem Link : https://www.hackerearth.com/practice/algorithms/searching/linear-search/practice-problems/algorithm/rest-in-peace-21-1/
t = int(input())
while (t):
    t-=1
    done = False
    n = (input())
    for x in range(len(n)-1):
        if n[x] == '2' and n[x+1] == '1':
            done = True
            break
 
    if done :
        print("The streak is broken!")   
        continue
 
    n = int(n)
    if(n % 21 == 0):
        done = True
 
     
    if done:
        print("The streak is broken!")   
        continue
 
    
    print("The streak lives still in our heart!")  
