    // Polynomial division provided that the quotient and remainder have integer coefficients
    #include <iostream>
    using namespace std;

    // quotient = dividend / divisor; remainder = dividend % divisor provided that
    // dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ], and
    // neither dividend nor divisor is the zero polynomial
    void division( int dividendCoef[], long long int dividendExpon[], int dividendSize,
                int divisorCoef[], long long int divisorExpon[], int divisorSize,
                int quotientCoef[], long long int quotientExpon[], int &quotientSize,
                int remainderCoef[], long long int remainderExpon[], int &remainderSize );

    // returns true if and only if polynomial1 == polynomial2
    bool equal( int coefficient1[], long long int exponent1[], int size1,
                int coefficient2[], long long int exponent2[], int size2 );

    // minuend -= subtrahend
    void subtraction( int minuendCoef[], long long int minuendExpon[], int &minuendSize,
                    int subtrahendCoef[], long long int subtrahendExpon[], int subtrahendSize );

    // outputs the specified polynomial
    void output( int coefficient[], long long int exponent[], int size );

    const int arraySize1 = 20 + 50;
    const int arraySize2 = 400 + 50;

    int main(){
        // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
        int T;
        cin >> T;
        for( int  t = 0; t < T; t++ ){
            // cout << "---------\n";
            int dividendCoef[ arraySize2 ] = {};
            long long int dividendExpon[ arraySize2 ] = {};
            int dividendSize;
            cin >> dividendSize; // input dividend
            for( int i = dividendSize - 1; i >= 0; i-- )
                cin >> dividendCoef[ i ];
            for( int i = dividendSize - 1; i >= 0; i-- )
                cin >> dividendExpon[ i ];

            int divisorCoef[ arraySize1 ] = {};
            long long int divisorExpon[ arraySize1 ] = {};
            int divisorSize;     
            cin >> divisorSize; // input divisor
            for( int i = divisorSize - 1; i >= 0; i-- )
                cin >> divisorCoef[ i ];
            for( int i = divisorSize - 1; i >= 0; i-- )
                cin >> divisorExpon[ i ];

            int quotientCoef[ arraySize1 ] = {};
            long long int quotientExpon[ arraySize1 ] = {};
            int quotientSize = arraySize1;

            int remainderCoef[ arraySize2 ] = {};
            long long int remainderExpon[ arraySize2 ] = {};
            int remainderSize = dividendSize;

            // quotient = dividend / divisor; remainder = dividend % divisor
            division( dividendCoef, dividendExpon, dividendSize,
                        divisorCoef, divisorExpon, divisorSize,
                        quotientCoef, quotientExpon, quotientSize,
                        remainderCoef, remainderExpon, remainderSize );

            output( quotientCoef, quotientExpon, quotientSize );
            output( remainderCoef, remainderExpon, remainderSize );
        }
    }

    // quotient = dividend / divisor; remainder = dividend % divisor provided that
    // dividendExpon[ dividendSize - 1 ] >= divisorExpon[ divisorSize - 1 ], and
    // neither dividend nor divisor is the zero polynomial
    void division( int dividendCoef[], long long int dividendExpon[], int dividendSize,
                int divisorCoef[], long long int divisorExpon[], int divisorSize,
                int quotientCoef[], long long int quotientExpon[], int &quotientSize,
                int remainderCoef[], long long int remainderExpon[], int &remainderSize ){
        
        int bufferCoef[ arraySize1 ] = {};
        long long int bufferExpon[ arraySize1 ] = {};
        int bufferSize = 1;

        // cout << "Enter1\n";
        remainderSize = dividendSize;
        for( int i = 0 ; i < dividendSize ; i++ ){
            remainderCoef[i] = dividendCoef[i];
            remainderExpon[i] = dividendExpon[i];
        }

        quotientSize = 21;
        for( int i = quotientSize-1 ; i >= 0 ; i-- ){
            // cout << "Enter2\n";

            quotientCoef[i] = remainderCoef[remainderSize-1] / divisorCoef[divisorSize-1];
            if(quotientCoef[i] != 0 ) quotientExpon[i] = remainderExpon[remainderSize-1] - divisorExpon[divisorSize-1];
            else quotientExpon[i] = 0;

            // cout << "Enter3\n";     
            bufferSize = divisorSize;
            for( int j = 0 ; j < divisorSize ; j++ ){
                bufferExpon[j] = divisorExpon[j] + quotientExpon[i];
                bufferCoef[j] = divisorCoef[j] * quotientCoef[i];
            }

            // cout << "Enter4\n";
            if( equal(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize) ){
                remainderCoef[0] = 0;
                remainderExpon[0] = 0;
                remainderSize = 1;
                // cout << "Here1\n";
                break;
            }

            // cout << "Enter5\n";
            // cout << "----------\n";
            // // cout << "Quo " << quotientCoef[i] << "\n";
            // cout << "Rem\n";
            // output(remainderCoef, remainderExpon, remainderSize);
            // cout << "Buffer\n";
            // output(bufferCoef, bufferExpon, bufferSize);
            subtraction(remainderCoef, remainderExpon, remainderSize, bufferCoef, bufferExpon, bufferSize);
            // cout << "----------\n";
            // cout << "Enter6\n";

            if( remainderExpon[remainderSize-1] < divisorExpon[divisorSize-1] ){
                break;
            }
        }

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
    }

    // returns true if and only if polynomial1 == polynomial2
    bool equal( int coefficient1[], long long int exponent1[], int size1,
                int coefficient2[], long long int exponent2[], int size2 ){
    if( size1 != size2 )
        return false;

    for( int i = 0; i < size1; i++ )
        if( coefficient1[ i ] != coefficient2[ i ] || exponent1[ i ] != exponent2[ i ] )
            return false;

    return true;
    }

    // minuend -= subtrahend
    void subtraction( int minuendCoef[], long long int minuendExpon[], int &minuendSize,
                    int subtrahendCoef[], long long int subtrahendExpon[], int subtrahendSize ){
        
        // return;
        
        int bufferCoef[ arraySize2 * 2 ] = {};
        long long int bufferExpon[ arraySize2 * 2 ] = {};
        int bufferSize = 1;

        bufferSize = minuendSize;
        for( int i = 0 ; i < minuendSize ; i++ ){
            bufferExpon[i] = minuendExpon[i];
            bufferCoef[i] = minuendCoef[i];
        }

        for( int i = 0 ; i < subtrahendSize ; i++ ){
            subtrahendCoef[i] *= -1;
        }

        // cout << "Minuend\n";
        // output(minuendCoef, minuendExpon, minuendSize);

        // cout << "Subtrahend\n";
        // output(subtrahendCoef, subtrahendExpon, subtrahendSize);

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
            // cout << "Res\n";
            // output(minuendCoef, minuendExpon, minuendSize);
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
        // cout << "Res\n";
        // output(minuendCoef, minuendExpon, minuendSize);

        return;
    }

    // outputs the specified polynomial
    void output( int coefficient[], long long int exponent[], int size ){
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