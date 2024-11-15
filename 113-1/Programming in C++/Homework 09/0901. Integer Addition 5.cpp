#include <iostream>
#include <cstring>
#include <vector>
using namespace::std;

// sum = addend + adder
vector< int > addition( vector< int > addend, vector< int > adder );

int main()
{
   char strA[ 251 ], strB[ 251 ];
   int T;
   cin >> T;
   for( int t = 0; t < T; ++t )
   {
      cin >> strA >> strB;

      int addendSize = strlen( strA );
      vector< int > addend( addendSize );
      for( int i = 0; i < addendSize; ++i )
         addend[ i ] = strA[ addendSize - 1 - i ] - '0';

      int adderSize = strlen( strB );
      vector< int > adder( adderSize );
      for( int i = 0; i < adderSize; ++i )
         adder[ i ] = strB[ adderSize - 1 - i ] - '0';

      vector< int > sum = addition( addend, adder );

      for( int i = sum.size() - 1; i >= 0; i-- )
         cout << sum[ i ];
      cout << endl;
   }
}

// sum = addend + adder
vector< int > addition( vector< int > addend, vector< int > adder ){
   vector<int> res;

   res.resize( max( adder.size(), addend.size() ) + 1 );

   int indaddend = 0, indadder = 0, indres = 0;

   for( int i = 0 ; i < res.size() ; i++ ) res[i] = 0;

   while( indaddend < addend.size() && indadder < adder.size() ){
      res[indres] += addend[indaddend] + adder[indadder];
      res[indres+1] = res[indres] / 10;
      res[indres] %= 10;

      indaddend++;
      indadder++;
      indres++;
   }

   while( indaddend < addend.size() ){
      res[indres] += addend[indaddend];
      res[indres+1] = res[indres] / 10;
      res[indres] %= 10;

      indaddend++;
      indres++;
   }

   while( indadder < adder.size() ){
      res[indres] += adder[indadder];
      res[indres+1] = res[indres] / 10;
      res[indres] %= 10;

      indadder++;
      indres++;
   }

   while( res[res.size()-1] == 0 ) res.pop_back();

   return res;
}