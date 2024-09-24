#include <iostream>
using namespace::std;

// find the sum of factors of n in the range [ 1 .. n - 1 ]
int sumFactors( int n ){
	int res = 0;
  for( int i = 1 ; i < n ; i++ ){
		if( n % i == 0 ) res += i;
  }
  
	return res;
}

int main()
{
	int numCases;
	cin >> numCases;
	for( int i = 1; i <= numCases; i++ )
	{
		int a, b;
		cin >> a >> b;

		if( a == sumFactors( b ) && b == sumFactors( a ) )
			cout << "amicable pair" << endl;
		else
			cout << "non-amicable pair" << endl;
	}
}