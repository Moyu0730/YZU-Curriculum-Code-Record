#include<iostream>
#include<cstring>
using std::cin;
using std::cout;
using std::endl;

struct HugeInt
{
   int size;
   int *digit;
};

// quotient = dividend / divisor; remainder = dividend % divisor
// provided that dividend != 0, divisor != 0 and dividend >= divisor
void division( HugeInt dividend, HugeInt divisor, HugeInt &quotient, HugeInt &remainder );

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt );

// minuend -= subtrahend
// provided that minuend != 0, subtrahend != 0 and minuend >= subtrahend
void subtraction( HugeInt &minuend, HugeInt subtrahend );

// returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool less( HugeInt hugeInt1, HugeInt hugeInt2 );

// return true if and only if hugeInt1 == hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool equal( HugeInt hugeInt1, HugeInt hugeInt2 );

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt hugeInt );

const int arraySize = 250;

int main(){
    char strA[ 251 ], strB[ 251 ];

    int T;
    cin >> T;
    for( int t = 0; t < T; ++t ){
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
        division( dividend, divisor, quotient, remainder );

        // cout << "Quo : ";
        for( int i = quotient.size - 1; i >= 0; i-- )
            cout << quotient.digit[ i ];
        cout << endl;

        // cout << "Rem : ";
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
void division( HugeInt dividend, HugeInt divisor, HugeInt &quotient, HugeInt &remainder ){
    remainder.size = dividend.size;
    remainder.digit = new int[ remainder.size ]();
    for( int i = 0 ; i < remainder.size ; i++ ) remainder.digit[i] = dividend.digit[i];

    int n = dividend.size - divisor.size;

    HugeInt buffer;
    buffer.size = dividend.size;
    buffer.digit = new int[ buffer.size + 1 ]();

    for( int i = divisor.size - 1 ; i >= 0 ; i-- ) buffer.digit[i+n] = divisor.digit[i];
    for( int i = 0 ; i < n ; i++ ) buffer.digit[i] = 0;

    // cout << "Buf : ";
    // for( int i = buffer.size - 1; i >= 0; i-- )
    //     cout << buffer.digit[ i ];
    // cout << endl;
    
    quotient.size = n;
    quotient.digit = new int[ quotient.size + 1 ]();
    
    if( less(dividend, buffer) ) divideBy10(buffer);
    else quotient.size++;

    for( int i = 0 ; i < quotient.size ; i++ ) quotient.digit[i] = 0;

    for( int i = quotient.size - 1 ; i >= 0 ; i-- ){
        while( less(buffer, remainder) || equal(buffer, remainder) ){
            subtraction(remainder, buffer);
            quotient.digit[i]++;
            if( isZero(remainder) ) return;
        }

        divideBy10(buffer);
    }

    while( quotient.digit[quotient.size-1] == 0 && quotient.size > 1 ) quotient.size--;

    delete[] buffer.digit;
    return;
}

// hugeInt /= 10, or equivalently, shifts right by one position
void divideBy10( HugeInt &hugeInt ){
    if( hugeInt.size == 1 )
        hugeInt.digit[ 0 ] = 0;
    else{
        for( int i = 1; i < hugeInt.size; i++ )
            hugeInt.digit[ i - 1 ] = hugeInt.digit[ i ];

        hugeInt.size--;
        hugeInt.digit[ hugeInt.size ] = 0;
    }
}

// minuend -= subtrahend
// provided that minuend != 0, subtrahend != 0 and minuend >= subtrahend
void subtraction( HugeInt &minuend, HugeInt subtrahend ){
    if( equal( minuend, subtrahend ) ){
        minuend.size = 1;
        minuend.digit = new int[ 1 ];
        minuend.digit[ 0 ] = 0;
        return;
    }

    HugeInt difference;
    difference.size = std::max( minuend.size, subtrahend.size );
    difference.digit = new int[ difference.size ];

    for( int i = 0 ; i < difference.size ; i++ ) difference.digit[i] = 0;
    for( int i = 0 ; i < subtrahend.size ; i++ ) difference.digit[i] = minuend.digit[i] - subtrahend.digit[i];
    for( int i = subtrahend.size ; i < minuend.size ; i++ ) difference.digit[i] = minuend.digit[i];
    for( int i = 0 ; i < difference.size ; i++ ){
        if( difference.digit[i] < 0 ){
            difference.digit[i] += 10;
            difference.digit[i+1]--;
        }
    }

    while( difference.digit[difference.size-1] == 0 ) difference.size--;
    for( int i = 0 ; i < difference.size ; i++ ) minuend.digit[i] = difference.digit[i];
    
    minuend.size = difference.size;

    delete[] difference.digit;
    return;
}

// returns true if and only if hugeInt1 < hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool less( HugeInt hugeInt1, HugeInt hugeInt2 ){
    if( hugeInt1.size < hugeInt2.size ) return true;
	if( hugeInt1.size > hugeInt2.size ) return false;

	for( int i = hugeInt1.size - 1 ; i >= 0 ; i-- ){
		if( hugeInt1.digit[i] == hugeInt2.digit[i] ) continue;

		if( hugeInt1.digit[i] > hugeInt2.digit[i] ) return false;
		else return true;
	}

	return false;
}

// return true if and only if hugeInt1 == hugeInt2
// provided that hugeInt1 != 0 and hugeInt2 != 0
bool equal( HugeInt hugeInt1, HugeInt hugeInt2 ){
   if( hugeInt1.size != hugeInt2.size )
      return false;

   for( int i = hugeInt1.size - 1; i >= 0; i-- )
      if( hugeInt1.digit[ i ] != hugeInt2.digit[ i ] )
         return false;

   return true;
}

// returns true if and only if the specified huge integer is zero
bool isZero( HugeInt hugeInt ){
   return hugeInt.size == 1 && hugeInt.digit[ 0 ] == 0;
}