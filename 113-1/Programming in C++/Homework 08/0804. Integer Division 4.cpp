#include<iostream>
#include<cstring>
using std::cin;
using std::cout;
using std::endl;

class HugeInt
{
public:
   int size;
   int *digit;

   // quotient = dividend / divisor; remainder = dividend % divisor
   // provided that dividend != 0, divisor != 0 and dividend >= divisor
   void division( HugeInt divisor, HugeInt &quotient, HugeInt &remainder );

   // hugeInt /= 10, or equivalently, shifts right by one position
   void divideBy10();

   // minuend -= subtrahend
   // provided that minuend != 0, subtrahend != 0 and minuend >= subtrahend
   void subtraction( HugeInt subtrahend );

   // returns true if and only if hugeInt1 < hugeInt2
   // provided that hugeInt1 != 0 and hugeInt2 != 0
   bool less( HugeInt hugeInt2 );

   // return true if and only if hugeInt1 == hugeInt2
   // provided that hugeInt1 != 0 and hugeInt2 != 0
   bool equal( HugeInt hugeInt2 );

   // returns true if and only if the specified huge integer is zero
   bool isZero();
};

const int arraySize = 250;

int main()
{
   char strA[ 251 ], strB[ 251 ];

   int T;
   cin >> T;
   for( int t = 0; t < T; ++t )
   {
      cin >> strA >> strB;

      HugeInt dividend;
      dividend.size = strlen( strA );
      dividend.digit = new int[ dividend.size ]();
      for( int i = 0; i < dividend.size; ++i )
         dividend.digit[ i ] = strA[ dividend.size - 1 - i ] - '0';

      HugeInt divisor;
      divisor.size = strlen( strB );
      divisor.digit = new int[ divisor.size ]();
      for( int i = 0; i < divisor.size; ++i )
         divisor.digit[ i ] = strB[ divisor.size - 1 - i ] - '0';

      HugeInt quotient;
      HugeInt remainder;
      dividend.division( divisor, quotient, remainder );

      for( int i = quotient.size - 1; i >= 0; i-- )
         cout << quotient.digit[ i ];
      cout << endl;

      for( int i = remainder.size - 1; i >= 0; i-- )
         cout << remainder.digit[ i ];
      cout << endl;

      delete[] dividend.digit;
      delete[] divisor.digit;
      delete[] quotient.digit;
      delete[] remainder.digit;
   }
}

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend != 0, divisor != 0 and dividend >= divisor
void HugeInt::division( HugeInt divisor, HugeInt &quotient, HugeInt &remainder ){
    remainder.size = size;
    remainder.digit = new int[ remainder.size ]();
    for( int i = 0 ; i < remainder.size ; i++ ) remainder.digit[i] = digit[i];

    int n = size - divisor.size;

    HugeInt buffer;
    buffer.size = size;
    buffer.digit = new int[ buffer.size + 1 ]();

    for( int i = divisor.size - 1 ; i >= 0 ; i-- ) buffer.digit[i+n] = divisor.digit[i];
    for( int i = 0 ; i < n ; i++ ) buffer.digit[i] = 0;

    // cout << "Buf : ";
    // for( int i = buffer.size - 1; i >= 0; i-- )
    //     cout << buffer.digit[ i ];
    // cout << endl;
    
    quotient.size = n;
    quotient.digit = new int[ quotient.size + 1 ]();
    
    if( less(buffer) ) buffer.divideBy10();
    else quotient.size++;

    for( int i = 0 ; i < quotient.size ; i++ ) quotient.digit[i] = 0;

    for( int i = quotient.size - 1 ; i >= 0 ; i-- ){
        while( buffer.less(remainder) || buffer.equal(remainder) ){
            remainder.subtraction(buffer);
            quotient.digit[i]++;
            if( remainder.isZero() ) return;
        }

        buffer.divideBy10();
    }

    while( quotient.digit[quotient.size-1] == 0 && quotient.size > 1 ) quotient.size--;

    delete[] buffer.digit;
    return;
}

// hugeInt /= 10, or equivalently, shifts right by one position
void HugeInt::divideBy10(){
    if( size == 1 )
        digit[ 0 ] = 0;
    else{
        for( int i = 1; i < size; i++ )
            digit[ i - 1 ] = digit[ i ];

        size--;
        digit[ size ] = 0;
    }
}

// minuend -= subtrahend
// provided that minuend != 0, subtrahend != 0 and minuend >= subtrahend
void HugeInt::subtraction( HugeInt subtrahend ){
    if( equal( subtrahend ) ){
        size = 1;
        digit = new int[ 1 ];
        digit[ 0 ] = 0;
        return;
    }

    HugeInt difference;
    difference.size = std::max( size, subtrahend.size );
    difference.digit = new int[ difference.size ];

    for( int i = 0 ; i < difference.size ; i++ ) difference.digit[i] = 0;
    for( int i = 0 ; i < subtrahend.size ; i++ ) difference.digit[i] = digit[i] - subtrahend.digit[i];
    for( int i = subtrahend.size ; i < size ; i++ ) difference.digit[i] = digit[i];
    for( int i = 0 ; i < difference.size ; i++ ){
        if( difference.digit[i] < 0 ){
            difference.digit[i] += 10;
            difference.digit[i+1]--;
        }
    }

    while( difference.digit[difference.size-1] == 0 ) difference.size--;
    for( int i = 0 ; i < difference.size ; i++ ) digit[i] = difference.digit[i];
    
    size = difference.size;

    delete[] difference.digit;
    return;
}

// returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool HugeInt::less( HugeInt hugeInt2 ){
    if( size < hugeInt2.size ) return true;
	if( size > hugeInt2.size ) return false;

	for( int i = size - 1 ; i >= 0 ; i-- ){
		if( digit[i] == hugeInt2.digit[i] ) continue;

		if( digit[i] > hugeInt2.digit[i] ) return false;
		else return true;
	}

	return false;
}

// return true if and only if hugeInt1 == hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool HugeInt::equal( HugeInt hugeInt2 ){
   if( size != hugeInt2.size )
      return false;

   for( int i = size - 1; i >= 0; i-- )
      if( digit[ i ] != hugeInt2.digit[ i ] )
         return false;

   return true;
}

// returns true if and only if the specified huge integer is zero
bool HugeInt::isZero(){
   return size == 1 && digit[ 0 ] == 0;
}