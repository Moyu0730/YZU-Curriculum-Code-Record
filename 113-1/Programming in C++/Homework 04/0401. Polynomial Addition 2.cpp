// Polynomial addition
#include <iostream>
using namespace std;

// sum = addend + adder
void addition( long long int addendCoef[], long long int addendExpon[], int addendSize,
               long long int adderCoef[], long long int adderExpon[], int adderSize,
               long long int sumCoef[], long long int sumExpon[], int &sumSize );

// outputs the specified polynomial
void output( long long int coefficient[], long long int exponent[], int size );

const int arraySize = 100;

int main(){
   // ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int T;
   cin >> T;
   for( int t = 0; t < T; t++ ){
      // cout << "---------\n";
      
      long long int addendCoef[ arraySize ] = {};
      long long int addendExpon[ arraySize ] = {};
      int addendSize;
      cin >> addendSize; // input addend
      for( int i = addendSize - 1; i >= 0; i-- )
         cin >> addendCoef[ i ];
      for( int i = addendSize - 1; i >= 0; i-- )
         cin >> addendExpon[ i ];

      long long int adderCoef[ arraySize ] = {};
      long long int adderExpon[ arraySize ] = {};
      int adderSize;     
      cin >> adderSize; // input adder
      for( int i = adderSize - 1; i >= 0; i-- )
         cin >> adderCoef[ i ];
      for( int i = adderSize - 1; i >= 0; i-- )
         cin >> adderExpon[ i ];

      long long int sumCoef[ 2 * arraySize ] = {};
      long long int sumExpon[ 2 * arraySize ] = {};
      int sumSize = 1;

      addition( addendCoef, addendExpon, addendSize,
                adderCoef, adderExpon, adderSize,
                sumCoef, sumExpon, sumSize );

      output( sumCoef, sumExpon, sumSize );

      // cout << "---------\n";
   }
}

// sum = addend + adder
void addition( long long int addendCoef[], long long int addendExpon[], int addendSize,
               long long int adderCoef[], long long int adderExpon[], int adderSize,
               long long int sumCoef[], long long int sumExpon[], int &sumSize ){

   int indAddend = 0, indAdder = 0, indSum = 0;
   while( indAddend < addendSize && indAdder < adderSize ){
      // cout << "END " << indAddend << " " << addendCoef[indAddend] << " " << addendExpon[indAddend] << " | ";
      // cout << "ER " << indAdder << " " << adderCoef[indAdder] << " " << addendExpon[indAdder] << " | ";
      if( adderExpon[indAdder] < addendExpon[indAddend] ){
         // cout << "A " << indAdder << " " << adderCoef[indAdder] << " " << indAddend << " " << addendCoef[indAdder] << " | ";
         sumExpon[indSum] = adderExpon[indAdder];
         sumCoef[indSum] = adderCoef[indAdder];
         indAdder++;
      }else if( addendExpon[indAddend] < adderExpon[indAdder] ){
         // cout << "B " << indAdder << " " << adderCoef[indAdder] << " " << indAddend << " " << addendCoef[indAdder] << " | ";
         sumExpon[indSum] = addendExpon[indAddend];
         sumCoef[indSum] = addendCoef[indAddend];
         indAddend++;
      }else{
         // cout << "C " << indAdder << " " << adderCoef[indAdder] << " " << indAddend << " " << addendCoef[indAdder] << " | ";
         sumExpon[indSum] = adderExpon[indAdder];
         sumCoef[indSum] = adderCoef[indAdder] + addendCoef[indAddend];
         indAdder++;
         indAddend++;
      }

      // cout << indAdder << " " << indAddend << " " << indSum << " " << sumCoef[indSum] << " " << sumExpon[indSum] << "\n";

      if( sumCoef[indSum] != 0 ) indSum++;
   }

   sumSize = indSum;

   if( indAddend == addendSize && indAdder == adderSize ) return;

   if( indAddend == addendSize ){
      while( indAdder < adderSize ){
         sumExpon[indSum] = adderExpon[indAdder];
         sumCoef[indSum] = adderCoef[indAdder];
         indAdder++;
         indSum++;
      }
   }else if( indAdder == adderSize ){
      while( indAddend < addendSize ){
         sumExpon[indSum] = addendExpon[indAddend];
         sumCoef[indSum] = addendCoef[indAddend];
         indAddend++;
         indSum++;
      }
   }

   sumSize = indSum;
}

// outputs the specified polynomial
void output( long long int coefficient[], long long int exponent[], int size )
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