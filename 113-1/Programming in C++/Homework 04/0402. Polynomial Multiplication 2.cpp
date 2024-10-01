// Polynomial multiplication
#include <iostream>
#include <map>
using namespace std;

#define F first
#define S second

// product = multiplicand * multiplier
void multiplication( long long int multiplicandCoef[], long long int multiplicandExpon[], int multiplicandSize,
                     long long int multiplierCoef[], long long int multiplierExpon[], int multiplierSize,
                     long long int productCoef[], long long int productExpon[], int &productSize );

// addend += adder
void addition( long long int addendCoef[], long long int addendExpon[], int &addendSize,
               long long int adderCoef[], long long int adderExpon[], int adderSize );

// returns true if and only if the specified polynomial is the zero polynomial
bool isZero( long long int coefficient[], int size );

// outputs the specified polynomial
void output( long long int coefficient[], long long int exponent[], int size );

const int arraySize = 10;

int main(){
    // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for( int t = 0; t < T; t++ ){
        // cout << "----------\n";
        long long int multiplicandCoef[ arraySize ] = {};
        long long int multiplicandExpon[ arraySize ] = {};
        int multiplicandSize;
        cin >> multiplicandSize; // input multiplicand
        for( int i = multiplicandSize - 1; i >= 0; i-- )
            cin >> multiplicandCoef[ i ];
        for( int i = multiplicandSize - 1; i >= 0; i-- )
            cin >> multiplicandExpon[ i ];

        long long int multiplierCoef[ arraySize ] = {};
        long long int multiplierExpon[ arraySize ] = {};
        int multiplierSize;     
        cin >> multiplierSize; // input multiplier
        for( int i = multiplierSize - 1; i >= 0; i-- )
            cin >> multiplierCoef[ i ];
        for( int i = multiplierSize - 1; i >= 0; i-- )
            cin >> multiplierExpon[ i ];

        long long int productCoef[ arraySize * arraySize ] = {};
        long long int productExpon[ arraySize * arraySize ] = {};
        int productSize = 1;

        // product = multiplicand * multiplier
        multiplication( multiplicandCoef, multiplicandExpon, multiplicandSize,
                        multiplierCoef, multiplierExpon, multiplierSize,
                        productCoef, productExpon, productSize );

        output( productCoef, productExpon, productSize );
   }
}

// product = multiplicand * multiplier
void multiplication( long long int multiplicandCoef[], long long int multiplicandExpon[], int multiplicandSize,
                     long long int multiplierCoef[], long long int multiplierExpon[], int multiplierSize,
                     long long int productCoef[], long long int productExpon[], int &productSize ){

    long long int bufferCoef[ arraySize * arraySize ] = {};
    long long int bufferExpon[ arraySize * arraySize ] = {};
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
        // cout << "----------\n";
        // cout << "Buffer\n";
        // output( bufferCoef, bufferExpon, bufferSize );
        // cout << "----------\n";
        // cout << "Multi"
        addition(productCoef, productExpon, productSize, bufferCoef, bufferExpon, bufferSize);
        // cout << "----------\n";
        // cout << "Product\n";
        // output( productCoef, productExpon, productSize );
        // cout << "----------\n";
    }
}

// addend += adder
void addition( long long int addendCoef[], long long int addendExpon[], int &addendSize,
               long long int adderCoef[], long long int adderExpon[], int adderSize ){

    long long int bufferCoef[ arraySize * arraySize ] = {};
    long long int bufferExpon[ arraySize * arraySize ] = {};
    int bufferSize = 1;

    // cout << "Adder\n";
    // output(adderCoef, adderExpon, adderSize);

    // cout << "Addend\n";
    // output(addendCoef, addendExpon, addendSize);

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
        // cout << "Sum\n";
        // output(addendCoef, addendExpon, addendSize);
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
    // cout << "Sum\n";
    // output(addendCoef, addendExpon, addendSize);
}

// returns true if and only if the specified polynomial is the zero polynomial
bool isZero( long long int coefficient[], int size ){
   return ( size == 1 && coefficient[ 0 ] == 0 );
}

// outputs the specified polynomial
void output( long long int coefficient[], long long int exponent[], int size ){
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