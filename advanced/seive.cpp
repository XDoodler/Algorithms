void seive(){ 
  vector<bool> prime;
  prime.resize(MAX,true);

  prime[0] = prime[1] = false;
  for (int i = 2; i <= MAX; ++i)
  {
    if(prime[i] && (long long)i*i <= MAX){
      for (int j = i*i; j <= MAX; j+=i)
      {
        prime[j] = false;
      }
    }
  }

  for (int i = 2; i <= MAX; ++i)
  {
    if(prime[i])primes.push_back(i);
  }

}
