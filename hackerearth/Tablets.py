#CODE AREA PLAYER
#Problem Link : https://www.hackerearth.com/practice/algorithms/dynamic-programming/introduction-to-dynamic-programming-1/practice-problems/algorithm/tablets/
k=2
f = [0] * 1000000
f[0] = 1
f[1] = 3
for i in range(2,1000000):
    if(i%2):
        f[i] = k*3
        k+=1
    else:
        f[i]=f[i-2]+3    
n = int(input())
print(f[n-1])
