def zellercongruence(day,month,year):
  if(month==1):
    year-=1
    month=13
  if(month==2):
    year-=1
    month=14
  q=day
  m=month
  k=year%100
  j=year//100
  h=q+13*(m + 1)//5+k+k//4+j//4+5*j
  h%=7
  return h

print(zellercongruence(7,18,2020))