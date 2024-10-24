// Polynomial multiplication
#include <iostream>
using namespace std;

// product = multiplicand * multiplier
void multiplication( long long int *multiplicandCoef, long long int *multiplicandExpon, int multiplicandSize,
                     long long int *multiplierCoef, long long int *multiplierExpon, int multiplierSize,
                     long long int *&productCoef, long long int *&productExpon, int &productSize );

// addend += adder
void addition( long long int *&addendCoef, long long int *&addendExpon, int &addendSize,
               long long int *adderCoef, long long int *adderExpon, int adderSize );

// returns true if and only if the specified polynomial is the zero polynomial
bool isZero( long long int *coefficient, int size );

// outputs the specified polynomial
void output( long long int *coefficient, long long int *exponent, int size );

int main(){
    int T;
    cin >> T;
    for( int t = 0; t < T; t++ ){
        int multiplicandSize;
        cin >> multiplicandSize; // input multiplicand
        long long int *multiplicandCoef = new long long int[ multiplicandSize ]();
        long long int *multiplicandExpon = new long long int[ multiplicandSize ]();
        for( int i = multiplicandSize - 1; i >= 0; i-- )
            cin >> multiplicandCoef[ i ];
        for( int i = multiplicandSize - 1; i >= 0; i-- )
            cin >> multiplicandExpon[ i ];

        int multiplierSize;     
        cin >> multiplierSize; // input multiplier
        long long int *multiplierCoef = new long long int[ multiplierSize ]();
        long long int *multiplierExpon = new long long int[ multiplierSize ]();
        for( int i = multiplierSize - 1; i >= 0; i-- )
            cin >> multiplierCoef[ i ];
        for( int i = multiplierSize - 1; i >= 0; i-- )
            cin >> multiplierExpon[ i ];

        int productSize;
        long long int *productCoef = new long long int[ multiplierSize * multiplicandSize ]();
        long long int *productExpon = new long long int[ multiplierSize * multiplicandSize ]();
        // product = multiplicand * multiplier
        multiplication( multiplicandCoef, multiplicandExpon, multiplicandSize,
                        multiplierCoef, multiplierExpon, multiplierSize,
                        productCoef, productExpon, productSize );

        output( productCoef, productExpon, productSize );

        delete[] multiplicandCoef;
        delete[] multiplicandExpon;
        delete[] multiplierCoef;
        delete[] multiplierExpon;
        delete[] productCoef;
        delete[] productExpon;
    }
}

// product = multiplicand * multiplier
void multiplication( long long int *multiplicandCoef, long long int *multiplicandExpon, int multiplicandSize,
                     long long int *multiplierCoef, long long int *multiplierExpon, int multiplierSize,
                     long long int *&productCoef, long long int *&productExpon, int &productSize ){

    long long int *bufferCoef = new long long int[ multiplierSize * multiplicandSize ]();
    long long int *bufferExpon = new long long int[ multiplierSize * multiplicandSize ]();
    int bufferSize = 1;

    int indBuffer = 0;
    for( int i = 0 ; i < multiplicandSize ; i++ ){
        indBuffer = 0;
        for( int j = 0 ; j < multiplierSize ; j++ ){
            bufferExpon[indBuffer] = multiplicandExpon[i] + multiplierExpon[j];
            bufferCoef[indBuffer] = multiplicandCoef[i] * multiplierCoef[j];
            indBuffer++;
        }
        
        bufferSize = indBuffer;
        addition(productCoef, productExpon, productSize, bufferCoef, bufferExpon, bufferSize);
    }

    delete[] bufferCoef;
    delete[] bufferExpon;
}

// addend += adder
void addition( long long int *&addendCoef, long long int *&addendExpon, int &addendSize,
               long long int *adderCoef, long long int *adderExpon, int adderSize ){
    
    long long int *bufferCoef = new long long int[ adderSize * addendSize ]();
    long long int *bufferExpon = new long long int[ adderSize * addendSize ]();
    int bufferSize = 1;

    bufferSize = addendSize;
    for( int i = 0 ; i < addendSize ; i++ ){
        bufferExpon[i] = addendExpon[i];
        bufferCoef[i] = addendCoef[i];
    }

    int indBuffer = 0, indAdder = 0, indAddend = 0;
    while( indBuffer < bufferSize && indAdder < adderSize ){
        if( adderExpon[indAdder] < bufferExpon[indBuffer] ){
            addendExpon[indAddend] = adderExpon[indAdder];
            addendCoef[indAddend] = adderCoef[indAdder];
            indAdder++;
        }else if( bufferExpon[indBuffer] < adderExpon[indAdder] ){
            addendExpon[indAddend] = bufferExpon[indBuffer];
            addendCoef[indAddend] = bufferCoef[indBuffer];
            indBuffer++;
        }else{
            addendExpon[indAddend] = adderExpon[indAdder];
            addendCoef[indAddend] = adderCoef[indAdder] + bufferCoef[indBuffer];
            indAdder++;
            indBuffer++;
        }

        if( addendCoef[indAddend] != 0 ) indAddend++;
    }

    addendSize = indAddend;

    if( indBuffer == bufferSize && indAdder == adderSize ){
        delete[] bufferCoef;
        delete[] bufferExpon;
        return;
    }

    if( indBuffer == bufferSize ){
        while( indAdder < adderSize ){
            addendExpon[indAddend] = adderExpon[indAdder];
            addendCoef[indAddend] = adderCoef[indAdder];
            indAdder++;
            indAddend++;
        }
    }else if( indAdder == adderSize ){
        while( indBuffer < bufferSize ){
            addendExpon[indAddend] = bufferExpon[indBuffer];
            addendCoef[indAddend] = bufferCoef[indBuffer];
            indBuffer++;
            indAddend++;
        }
    }

    addendSize = indAddend;
    delete[] bufferCoef;
    delete[] bufferExpon;
}

// returns true if and only if the specified polynomial is the zero polynomial
bool isZero( long long int *coefficient, int size ){
   return ( size == 1 && coefficient[ 0 ] == 0 );
}

// outputs the specified polynomial
void output( long long int *coefficient, long long int *exponent, int size ){
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