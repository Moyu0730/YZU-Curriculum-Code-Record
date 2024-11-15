#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend != 0, divisor != 0 and dividend >= divisor
void division( vector< int > dividend, vector< int > divisor,
               vector< int > &quotient, vector< int > &remainder );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( vector< int > &hugeInt );

// minuend -= subtrahend
// provided that minuend != 0, subtrahend != 0 and minuend >= subtrahend
void subtraction( vector< int > &minuend, vector< int > subtrahend );

// returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool less( vector< int > hugeInt1, vector< int > hugeInt2 );

// return true if and only if hugeInt1 == hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool equal( vector< int > hugeInt1, vector< int > hugeInt2 );

// returns true if and only if the specified huge integer is zero
bool isZero( vector< int > hugeInt );

const int arraySize = 250;

int main()
{
   char strA[ 251 ], strB[ 251 ];

   int T;
   cin >> T;
   for( int t = 0; t < T; ++t )
   {
      cin >> strA >> strB;

      int dividendSize = strlen( strA );
      vector< int > dividend( dividendSize );
      for( int i = 0; i < dividendSize; ++i )
         dividend[ i ] = strA[ dividendSize - 1 - i ] - '0';

      int divisorSize = strlen( strB );
      vector< int > divisor( divisorSize );
      for( int i = 0; i < divisorSize; ++i )
         divisor[ i ] = strB[ divisorSize - 1 - i ] - '0';

      vector< int > quotient;
      vector< int > remainder;
      division( dividend, divisor, quotient, remainder );

      for( int i = quotient.size() - 1; i >= 0; i-- )
         cout << quotient[ i ];
      cout << endl;

      for( int i = remainder.size() - 1; i >= 0; i-- )
         cout << remainder[ i ];
      cout << endl;
   }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend != 0, divisor != 0 and dividend >= divisor
void division( vector< int > dividend, vector< int > divisor, vector< int > &quotient, vector< int > &remainder ){
    remainder.resize( dividend.size() );
    for( int i = 0 ; i < remainder.size() ; i++ ) remainder[i] = dividend[i];

    int n = dividend.size() - divisor.size();

    vector<int> buffer;
    buffer.resize( dividend.size() );

    for( int i = divisor.size() - 1 ; i >= 0 ; i-- ) buffer[i+n] = divisor[i];
    for( int i = 0 ; i < n ; i++ ) buffer[i] = 0;

    quotient.resize(n);
    
    if( less(dividend, buffer) ) divideBy10(buffer);
    else quotient.push_back(0);

    for( int i = 0 ; i < quotient.size() ; i++ ) quotient[i] = 0;

    for( int i = quotient.size() - 1 ; i >= 0 ; i-- ){
        while( less(buffer, remainder) || equal(buffer, remainder) ){

            subtraction(remainder, buffer);
            quotient[i]++;
            if( isZero(remainder) ) return;
        }

        divideBy10(buffer);
    }

    while( quotient[quotient.size()-1] == 0 && quotient.size() > 1 ) quotient.pop_back();

    return;
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( vector< int > &hugeInt ){
   int size = hugeInt.size();
   if( size == 1 )
      hugeInt[ 0 ] = 0;
   else
   {
      for( int i = 1; i < size; i++ )
         hugeInt[ i - 1 ] = hugeInt[ i ];
      hugeInt.pop_back();
   }
}

// minuend -= subtrahend
// provided that minuend != 0, subtrahend != 0 and minuend >= subtrahend
void subtraction( vector< int > &minuend, vector< int > subtrahend ){
    vector<int> difference;

    if( equal( minuend, subtrahend ) ){
        minuend.resize(1);
        minuend[0] = 0;
        return;
    }

    difference.resize( std::max( minuend.size(), subtrahend.size() ) );

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

    minuend.resize(difference.size());
    for( int i = 0 ; i < difference.size() ; i++ ) minuend[i] = difference[i];

    return;	
}

// returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool less( vector< int > hugeInt1, vector< int > hugeInt2 ){
    if( hugeInt1.size() < hugeInt2.size() ) return true;
	if( hugeInt1.size() > hugeInt2.size() ) return false;

	for( int i = hugeInt1.size() - 1 ; i >= 0 ; i-- ){
		if( hugeInt1[i] == hugeInt2[i] ) continue;

		if( hugeInt1[i] > hugeInt2[i] ) return false;
		else return true;
	}

	return false;
}

// return true if and only if hugeInt1 == hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool equal( vector< int > hugeInt1, vector< int > hugeInt2 )
{
   int size1 = hugeInt1.size();
   int size2 = hugeInt2.size();
   if( size1 != size2 )
      return false;

   for( int i = size1 - 1; i >= 0; i-- )
      if( hugeInt1[ i ] != hugeInt2[ i ] )
         return false;

   return true;
}

// returns true if and only if the specified huge integer is zero
bool isZero( vector< int > hugeInt ){
   return hugeInt.size() == 1 && hugeInt[ 0 ] == 0;
}