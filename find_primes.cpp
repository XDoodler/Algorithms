vector<int> primes;

bool isPrime(ll n){if(n<=1)return 0;if(n<=3)return 1;if(n%2==0||n%3==0)return 0;for(ll i=5;i*i<=n;i+=6)if(n%i==0||n%(i+2)==0)return 0;return 1;}

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

                             
                             //Access the primes vector for fetching primes btwn 1 - 100000000
