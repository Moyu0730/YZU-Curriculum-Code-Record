#include <iostream>
#include <cstring>
#include <vector>
using namespace::std;

// returns true if and only if hugeInt1 == hugeInt2
bool equal( vector< int > hugeInt1, vector< int > hugeInt2 );

// difference = minuend - subtrahend provided that minuend >= subtrahend
vector< int > subtraction( vector< int > minuend, vector< int > subtrahend );

int main()
{
   char strA[ 251 ], strB[ 251 ];

   int T;
   cin >> T;
   for( int t = 0; t < T; ++t )
   {
      cin >> strA >> strB;

      int minuendSize = strlen( strA );
      vector< int > minuend( minuendSize );
      for( int i = 0; i < minuendSize; ++i )
         minuend[ i ] = strA[ minuendSize - 1 - i ] - '0';

      int subtrahendSize = strlen( strB );
      vector< int > subtrahend( subtrahendSize );
      for( int i = 0; i < subtrahendSize; ++i )
         subtrahend[ i ] = strB[ subtrahendSize - 1 - i ] - '0';

      vector< int > difference = subtraction( minuend, subtrahend );

      for( int i = difference.size() - 1; i >= 0; i-- )
         cout << difference[ i ];
      cout << endl;
   }
}

// returns true if and only if hugeInt1 == hugeInt2
bool equal( vector< int > hugeInt1, vector< int > hugeInt2 )
{
   int size1 = hugeInt1.size();
   int size2 = hugeInt2.size();
   if( size1 != size2 )
      return false;

   for( int i = 0; i < size1; i++ )
      if( hugeInt1[ i ] != hugeInt2[ i ] )
         return false;

   return true;
}

// difference = minuend - subtrahend provided that minuend >= subtrahend
vector< int > subtraction( vector< int > minuend, vector< int > subtrahend ){
   vector<int> difference;

   if( equal( minuend, subtrahend ) ){
      difference.resize(1);
      difference[0] = 0;
      return difference;
   }

   difference.resize( max( minuend.size(), subtrahend.size() ) );

   for( int i = 0 ; i < difference.size() ; i++ ) difference[i] = 0;

	for( int i = 0 ; i < subtrahend.size() ; i++ ) difference[i] = minuend[i] - subtrahend[i];

	for( int i = subtrahend.size() ; i < minuend.size() ; i++ ) difference[i] = minuend[i];

	for( int i = 0 ; i < difference.size() ; i++ ){
		if( difference[i] < 0 ){
			difference[i] += 10;
			difference[i+1]--;
		}
	}

	while( difference[difference.size()-1] == 0 ) difference.pop_back();	

   return difference;
}