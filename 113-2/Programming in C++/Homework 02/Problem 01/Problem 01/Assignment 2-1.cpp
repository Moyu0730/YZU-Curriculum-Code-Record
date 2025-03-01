// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <string>
#include "string 2-1.h"

void testFromBufferConstructor();
void testFillConstructor();
void testCopyConstructor1();
void testCopyConstructor2();

// return true iff string1 == string2
bool equal( string &string1, std::string &string2 );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int capacities[ 31 ];
const unsigned int number = 30;

int main()
{
   ifstream capFile( "capacities.txt", ios::in );

   if( !capFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   for( int i = 0; i <= number; i++ )
      capFile >> capacities[ i ];

   capFile.close();

   testFromBufferConstructor();
   testFillConstructor();
   testCopyConstructor1();
   testCopyConstructor2();
   cout << endl;

   system( "pause" );
}

void testFromBufferConstructor()
{
   const unsigned int number = 1000;
   int numErrors = 0;
   for( int s = 0; s <= number; s++ )
   {
      char str[ number + 1 ];
      for( int i = 0; i < s; i++ )
         str[ i ] = static_cast< char >( 97 + rand() % 26 );
      str[ s ] = '\0';

      string string1( str, s );
      std::string string2( str, s );

      if( !equal( string1, string2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testFillConstructor()
{
   const unsigned int number = 200;
   int numErrors = 0;
   for( int s = 0; s <= number; s++ )
   {
      char c = static_cast< char >( 97 + rand() % 26 );
      string string1( s, c );
      std::string string2( s, c );

      if( !equal( string1, string2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test string with capacity == 15
void testCopyConstructor1()
{
   int numErrors = 0;
   for( int s = 0; s <= 15; s++ )
   {
      string string1( s, '\0' ); // string1.mySize = s; string1.myRes = 15; string1.bx.buf is used
      std::string string2( s, '\0' );

      for( int i = 0; i < s; i++ )
      {
         char value = static_cast< char >( 97 + rand() % 26 );
         string1.at( i ) = value; // string1.bx.buf[ i ] = value
         string2[ i ] = value;
      }
      string1.at( s ) = '\0'; // string1.bx.buf[ s ] = '\0'
      string2[ s ] = '\0';

      string string3( string1 );
      std::string string4( string2 );

      if( !equal( string3, string4 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test string with capacity > 15
void testCopyConstructor2()
{
   const unsigned int number = 30;
   int numErrors = 0;
   for( int i = 1; i <= number; i++ )
   {
      int c = capacities[ i ]; // c >= 31
      for( int s = 0; s <= c; s++ )
      {
         string string1( s, '\0' ); // string1.mySize = s
         std::string string2( s, '\0' );

         char **ptr1 = reinterpret_cast< char ** >( &string1 ); // ptr1 points to string1.bx.ptr or string1.bx.buf
         char **ptr2 = reinterpret_cast< char ** >( &string2 ) + offset;
         if( s > 15 ) // string1.myRes > 15; string1.bx.ptr is used
         {
            delete[] *ptr1;
            delete[] *ptr2;
         }
         *ptr1 = new char[ c + 1 ];
         *ptr2 = new char[ c + 1 ];

         size_t *myCap1;
         size_t *myCap2;
         if( sizeof( size_t ) == 4 ) // x86
         {
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
            myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
         }
         else // x64
         {
            myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes
            myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
         }

         *myCap1 = c; // string1.myRes = c
         *myCap2 = c;

         for( int j = 0; j < s; j++ )
         {
            char value = static_cast< char >( 97 + rand() % 26 );
            string1.at( j ) = value; // string1.bx.ptr[ i ] = value
            string2[ j ] = value;
         }
         string1.at( s ) = '\0'; // string1.bx.ptr[ s ] = '\0'
         string2[ s ] = '\0';

         string string3( string1 );
         std::string string4( string2 );

         if( !equal( string3, string4 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// return true iff string1 == string2
bool equal( string &string1, std::string &string2 )
{
   if( string1.capacity() != string2.capacity() )
      return false;

   if( string1.size() != string2.size() )
      return false;

   if( string2.size() == 0 )
      return true;

   for( size_t i = 0; i <= string2.size(); i++ )
      if( string1.at( i ) != string2[ i ] )
         return false;

   return true;
}