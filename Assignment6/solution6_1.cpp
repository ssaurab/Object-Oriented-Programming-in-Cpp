#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

long long int fib(int t0, int t1, int n)
{
//as the fibonacci numbers shoot up very quick
  long long int f[n+1];
  int i;
 
  f[0] = t0;
  f[1] = t1;
 
  for (i = 2; i <= n; i++)
  {
//we only need remainders so reduce at every computation, otherwise the bitspacce is insufficient very quick
      f[i] = ( 2*f[i-1] + f[i-2] ) % 1000000007; //iterating the array and filling it until needed
  }
 //note that we did not repeat any computation
  return f[n];    
}
 
int main ()
{
  int t0, t1;
    scanf("%d %d\n", &t0, &t1);
  int n;
    scanf("%d\n", &n);
    long long int k = (fib(t0, t1, n-1)%1000000007);
  printf("%lld", k);
  return 0;
}
