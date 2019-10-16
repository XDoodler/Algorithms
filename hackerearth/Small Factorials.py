#CODE ARENA PLAYER
#Problem Link : https://www.hackerearth.com/practice/algorithms/searching/ternary-search/practice-problems/algorithm/small-factorials/
f = [1] * 105
for i in range(2,105):
    f[i] = f[i-1] * i
t = int(input())
while t:
    t-=1
    n = int(input())
    print(f[n])
