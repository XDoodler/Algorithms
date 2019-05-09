void find_primes(ll n = 100000000){
ll limit=floor(sqrt(n))+1;
vi test;test.pb(2),primes.pb(void find_primes(ll n = 100000000){
ll limit=floor(sqrt(n))+1;
vi test;test.pb(2),primes.pb(2);
for(ll i=3;i<limit;i+=2)if(isPrime(i))test.pb(i),primes.pb(i);
ll lo=limit,hi=2*limit;bool p[limit];
while(lo<n){if(hi>n)hi=n;
  memset(p,true,sizeof(p));
  for(int i=0;i<test.size();++i){
  ll mn=(lo/test[i])*test[i];if(mn<lo)mn+=test[i];
  for(ll j=mn;j<hi;j+=test[i])p[j-lo]=0;}
  rep(i,0,limit)if(p[i] && i+lo<hi)primes.pb(i+lo);
  lo+=limit,hi+=limit;}}
