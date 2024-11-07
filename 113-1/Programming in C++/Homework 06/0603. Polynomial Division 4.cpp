// Polynomial division provided that the quotient and remainder have integer coefficients
#include <iostream>
using namespace std;

// quotient = dividend / divisor; remainder = dividend % divisor provided that
// dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ], and
// neither dividend nor divisor is the zero polynomial
void division( int *dividendCoef, long long int *dividendExpon, int dividendSize,
               int *divisorCoef, long long int *divisorExpon, int divisorSize,
               int *&quotientCoef, long long int *&quotientExpon, int &quotientSize,
               int *&remainderCoef, long long int *&remainderExpon, int &remainderSize );

// returns true if and only if polynomial1 == polynomial2
bool equal( int *coefficient1, long long int *exponent1, int size1,
            int *coefficient2, long long int *exponent2, int size2 );

// minuend -= subtrahend
void subtraction( int *minuendCoef, long long int *minuendExpon, int &minuendSize,
                  int *subtrahendCoef, long long int *subtrahendExpon, int subtrahendSize );

// outputs the specified polynomial
void output( int *coefficient, long long int *exponent, int size );

const int arraySize = 20;

int main()
{
   int T;
   cin >> T;
   for( int t = 0; t < T; t++ )
   {
      int dividendSize;
      cin >> dividendSize; // input dividend
      int *dividendCoef = new int[ dividendSize ]();
      long long int *dividendExpon = new long long int[ dividendSize ]();
      for( int i = dividendSize - 1; i >= 0; i-- )
         cin >> dividendCoef[ i ];
      for( int i = dividendSize - 1; i >= 0; i-- )
         cin >> dividendExpon[ i ];

      int divisorSize;     
      cin >> divisorSize; // input divisor
      int *divisorCoef = new int[ divisorSize ]();
      long long int *divisorExpon = new long long int[ divisorSize ]();
      for( int i = divisorSize - 1; i >= 0; i-- )
         cin >> divisorCoef[ i ];
      for( int i = divisorSize - 1; i >= 0; i-- )
         cin >> divisorExpon[ i ];

      int quotientSize;
      int *quotientCoef = new int[ dividendSize ]();
      long long int *quotientExpon = new long long int[ dividendSize ]();

      int remainderSize;
      int *remainderCoef = new int[ dividendSize ]();
      long long int *remainderExpon = new long long int[ dividendSize ]();

      // quotient = dividend / divisor; remainder = dividend % divisor
      division( dividendCoef, dividendExpon, dividendSize,
                divisorCoef, divisorExpon, divisorSize,
                quotientCoef, quotientExpon, quotientSize,
                remainderCoef, remainderExpon, remainderSize );

      output( quotientCoef, quotientExpon, quotientSize );
      output( remainderCoef, remainderExpon, remainderSize );

      delete[] dividendCoef;
      delete[] dividendExpon;
      delete[] divisorCoef;
      delete[] divisorExpon;
      delete[] quotientCoef;
      delete[] quotientExpon;
      delete[] remainderCoef;
      delete[] remainderExpon;
   }
}

// quotient = dividend / divisor; remainder = dividend % divisor provided that
// dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ], and
// neither dividend nor divisor is the zero polynomial
void division( int *dividendCoef, long long int *dividendExpon, int dividendSize,
               int *divisorCoef, long long int *divisorExpon, int divisorSize,
               int *&quotientCoef, long long int *&quotientExpon, int &quotientSize,
               int *&remainderCoef, long long int *&remainderExpon, int &remainderSize ){

    int *bufferCoef = new int[ dividendSize ]();
    long long int *bufferExpon = new long long int[ dividendSize ]();
    int bufferSize = 1;

    remainderSize = dividendSize;
    for( int i = 0 ; i < dividendSize ; i++ ){
        remainderCoef[i] = dividendCoef[i];
        remainderExpon[i] = dividendExpon[i];
    }

    quotientSize = dividendSize;
    // for( int i = 0 ; i < quotientSize-1 ; i++ ){
    //     quotientCoef[i] = 0;
    //     quotientExpon[i] = 0;
    // }

    for( int i = quotientSize-1 ; i >= 0 ; i-- ){

        quotientCoef[i] = remainderCoef[remainderSize-1] / divisorCoef[divisorSize-1];
        quotientExpon[i] = remainderExpon[remainderSize-1] - divisorExpon[divisorSize-1];
  
        bufferSize = divisorSize;
        for( int j = 0 ; j < divisorSize ; j++ ){
            bufferExpon[j] = divisorExpon[j] + quotientExpon[i];
            bufferCoef[j] = divisorCoef[j] * quotientCoef[i];
        }

        // cout << "---Buffer---\n";
        // output(bufferCoef, bufferExpon, bufferSize);
        // cout << "---Rem---\n";
        // output(remainderCoef, remainderExpon, remainderSize);

        if( equal(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize) ){
            // cout << "Buffer\n";
            // output(bufferCoef, bufferExpon, bufferSize);
            // cout << "Rem\n";
            // output(remainderCoef, remainderExpon, remainderSize);
            remainderCoef[0] = 0;
            remainderExpon[0] = 0;
            remainderSize = 1;
            break;
        }

        // cout << "----------\n";
        // cout << "Rem\n";
        // output(remainderCoef, remainderExpon, remainderSize);
        // cout << "Buffer\n";
        // output(bufferCoef, bufferExpon, bufferSize);
        subtraction(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);
        // cout << "Rem\n";
        // output(remainderCoef, remainderExpon, remainderSize);
        // cout << "----------\n";

        if( remainderExpon[remainderSize-1] < divisorExpon[divisorSize-1] ) break;
    }

    // cout << "---Buffer---\n";
    // output(bufferCoef, bufferExpon, bufferSize);
    // cout << "---Rem---\n";
    // output(remainderCoef, remainderExpon, remainderSize);
    // cout << "---Quo---\n";
    // output(quotientCoef, quotientExpon, quotientSize);
    // cout << "\n\n";

    int notzero = 0;
    for( int i = 0 ; i < quotientSize ; i++ ){
        if( quotientCoef[i] != 0 ){
            notzero = i;
            break;
        }
    }

    quotientSize = quotientSize - notzero;
    for( int i = 0 ; i < quotientSize ; i++ ) quotientCoef[i] = quotientCoef[i+notzero];
    for( int i = 0 ; i < quotientSize ; i++ ) quotientExpon[i] = quotientExpon[i+notzero];

    delete[] bufferCoef;
    delete[] bufferExpon;
    return;
}

// returns true if and only if polynomial1 == polynomial2
bool equal( int *coefficient1, long long int *exponent1, int size1,
            int *coefficient2, long long int *exponent2, int size2 ){
   if( size1 != size2 )
      return false;

   for( int i = 0; i < size1; i++ )
      if( coefficient1[ i ] != coefficient2[ i ] || exponent1[ i ] != exponent2[ i ] )
         return false;

   return true;
}

// minuend -= subtrahend
void subtraction( int *minuendCoef, long long int *minuendExpon, int &minuendSize,
                  int *subtrahendCoef, long long int *subtrahendExpon, int subtrahendSize ){
    
    int *bufferCoef = new int[ minuendSize + subtrahendSize ]();
    long long int *bufferExpon = new long long int[ minuendSize + subtrahendSize ]();
    int bufferSize = 1;

    bufferSize = minuendSize;
    for( int i = 0 ; i < minuendSize ; i++ ){
        bufferExpon[i] = minuendExpon[i];
        bufferCoef[i] = minuendCoef[i];
    }

    for( int i = 0 ; i < subtrahendSize ; i++ ) subtrahendCoef[i] *= -1;

    int indBuffer = 0, indSubtrahend = 0, indMinuend = 0;
    while( indBuffer < bufferSize && indSubtrahend < subtrahendSize ){
        if( subtrahendExpon[indSubtrahend] < bufferExpon[indBuffer] ){
            minuendExpon[indMinuend] = subtrahendExpon[indSubtrahend];
            minuendCoef[indMinuend] = subtrahendCoef[indSubtrahend];
            indSubtrahend++;
        }else if( bufferExpon[indBuffer] < subtrahendExpon[indSubtrahend] ){
            minuendExpon[indMinuend] = bufferExpon[indBuffer];
            minuendCoef[indMinuend] = bufferCoef[indBuffer];
            indBuffer++;
        }else{
            minuendExpon[indMinuend] = subtrahendExpon[indSubtrahend];
            minuendCoef[indMinuend] = subtrahendCoef[indSubtrahend] + bufferCoef[indBuffer];
            indSubtrahend++;
            indBuffer++;
        }

        if( minuendCoef[indMinuend] != 0 ) indMinuend++;
    }

    minuendSize = indMinuend;

    if( indBuffer == bufferSize && indSubtrahend == subtrahendSize ){
        delete[] bufferCoef;
        delete[] bufferExpon;
        return;
    }

    if( indBuffer == bufferSize ){
        while( indSubtrahend < subtrahendSize ){
            minuendExpon[indMinuend] = subtrahendExpon[indSubtrahend];
            minuendCoef[indMinuend] = subtrahendCoef[indSubtrahend];
            indSubtrahend++;
            indMinuend++;
        }
    }else if( indSubtrahend == subtrahendSize ){
        while( indBuffer < bufferSize ){
            minuendExpon[indMinuend] = bufferExpon[indBuffer];
            minuendCoef[indMinuend] = bufferCoef[indBuffer];
            indBuffer++;
            indMinuend++;
        }
    }

    minuendSize = indMinuend;
    delete[] bufferCoef;
    delete[] bufferExpon;
    return;	
}

// outputs the specified polynomial
void output( int *coefficient, long long int *exponent, int size )
{
   cout << size << endl;
   cout << coefficient[ size - 1 ];
   for( int i = size - 2; i >= 0; i-- )
      cout << " " << coefficient[ i ];
   cout << endl;

   cout << exponent[ size - 1 ];
   for( int i = size - 2; i >= 0; i-- )
      cout << " " << exponent[ i ];
   cout << endl;
}