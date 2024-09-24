#include<iostream>
using namespace std;

int numDigits;

// returns the k-th power of d, where k is the number of digits of n.
int ksm( int base, int power ){
    int res = 1;
    while( power > 0 ){
        if( power & 1 ) res *= base;
        
        power >>= 1;
        base *= base;
    }

    return res;
}

// returns the sum of the k-th powers of digits of n,
// where k is the number of digits of n.
int sumPowerDigits( int n ){
  int res = 0;
  while( n > 0 ){
    res += ksm(n%10, numDigits);
		n /= 10;
	}

	return res;
}

int main()
{
   int numCases;
   cin >> numCases;
   for( int i = 1; i <= numCases; i++ )
   {
      int n;
      cin >> n;

      numDigits = 0; // the number of digits of n
      for( int i = n; i > 0; i /= 10 )
         numDigits++;

      if( n == sumPowerDigits( n ) )
         cout << "Armstrong" << endl;
      else
         cout << "Not Armstrong" << endl;
   }
}