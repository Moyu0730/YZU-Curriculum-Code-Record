#include <bits/stdc++.h>
using namespace::std;

// returns true if and only if a and b have a common factor
bool haveCommonFactors( int a, int b );

int main()
{
	int numCases;
	cin >> numCases;
	for( int i = 1; i <= numCases; i++ )
	{
		int a, b;
		cin >> a >> b;

		if( __gcd(a, b) != 1 )
			cout << "not coprime" << endl;
		else
			cout << "coprime" << endl;
	}
}