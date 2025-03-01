// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <string>
#include "string 2-3.h"

void testInsert1();
void testInsert2();
void testInsert3();
void testInsert4();
void testErase1();
void testErase2();
void testErase3();
void testErase4();
void testErase5();
void testErase6();
void testErase7();
void testErase8();

// return true iff string1 == string2
bool equal( string &string1, std::string &string2 );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int capacities[ 51 ];

int main()
{
   ifstream capFile( "capacities.txt", ios::in );

   if( !capFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   const unsigned int number = 50;
   for( int i = 0; i <= number; i++ )
      capFile >> capacities[ i ];

   capFile.close();

   testInsert1();
   testInsert2();
   testInsert3();
   testInsert4();
   testErase1();
   testErase2();
   testErase3();
   testErase4();
   testErase5();
   testErase6();
   testErase7();
   testErase8();
   cout << endl;

   system( "pause" );
}

// test string with capacity == 15
void testInsert1()
{
   int numErrors = 0;
   for( int s = 0; s <= 15; s++ )
   {
      for( int position = 0; position <= s; position++ )
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

         char value = static_cast< char >( 97 + rand() % 26 );
         string1.insert( string1.begin() + position, value );
         string2.insert( string2.begin() + position, value );

         if( !equal( string1, string2 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test string with capacity > 15
void testInsert2()
{
   const unsigned int number = 10;
   int numErrors = 0;
   for( int i = 1; i <= number; i++ )
   {
      int c = capacities[ i ]; // c >= 31
      for( int s = 0; s <= c; s++ )
      {
         for( int position = 0; position <= s; position++ )
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
            if( sizeof( size_t ) == 4 )
            {
               myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
               myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
            }
            else
            {
               myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes
               myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
            }

            *myCap1 = c; // string1.myRes = c
            *myCap2 = c;

            for( int j = 0; j < s; j++ )
            {
               char value = static_cast< char >( 97 + rand() % 26 );
               string1.at( j ) = value; // string1.bx.ptr[ j ] = value
               string2[ j ] = value;
            }
            string1.at( s ) = '\0'; // string1.bx.ptr[ s ] = '\0'
            string2[ s ] = '\0';

            char value = static_cast< char >( 97 + rand() % 26 );
            string1.insert( string1.begin() + position, value );
            string2.insert( string2.begin() + position, value );

            if( !equal( string1, string2 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test string with capacity == 15
void testInsert3()
{
   int numErrors = 0;
   for( int s = 0; s < 15; s++ )
   {
      for( int position = 0; position <= s; position++ )
      {
         string str( s, '\0' ); // str.mySize = s; str.myRes = 15; str.bx.buf is used
         char *p = str.begin();

         char value = static_cast< char >( 97 + rand() % 26 );
         str.insert( str.begin() + position, value );

         if( str.begin() != p )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test string with capacity > 15
void testInsert4()
{
   const unsigned int number = 30;
   int numErrors = 0;
   for( int i = 1; i <= number; i++ )
   {
      int c = capacities[ i ]; // c >= 31
      for( int s = 0; s <= c; s++ )
      {
         for( int position = 0; position <= s; position++ )
         {
            string str( s, '\0' ); // str.mySize = s

            char **ptr = reinterpret_cast< char ** >( &str ); // ptr points to str.bx.ptr or str.bx.buf
            if( s > 15 ) // str.myRes > 15; str.bx.ptr is used
               delete[] *ptr;
            *ptr = new char[ c + 1 ];

            size_t *myCap;
            if( sizeof( size_t ) == 4 )
               myCap = reinterpret_cast< size_t * >( &str ) + 5; // myCap points to str.myRes
            else
               myCap = reinterpret_cast< size_t * >( &str ) + 3;

            *myCap = c;

            char *p = str.begin();
            char value = static_cast< char >( 97 + rand() % 26 );
            str.insert( str.begin() + position, value );

            if( str.capacity() == c && str.begin() != p )
               numErrors++;

            // str.begin() == p if and only if
            // the array pointed by str.bx.ptr before
            // the excution of str.insert( str.begin() + position, value ) is the same as
            // the array pointed by str.bx.ptr after
            // the excution of str.insert( str.begin() + position, value )
            // i.e., there is no memory allocation during the excution of
            // str.insert( str.begin() + position, value )
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test empty string with capacity == 15
void testErase1()
{
   int numErrors = 0;

   string string1;      // empty string
   std::string string2; // empty string

   string1.erase( string1.begin() );
   string2.erase( string2.begin() );

   if( !equal( string1, string2 ) )
      numErrors++;

   cout << "There are " << numErrors << " errors.\n";
}

// test nonempty string with capacity == 15
void testErase2()
{
   int numErrors = 0;

   for( int s = 1; s <= 15; s++ )
   {
      for( int position = 0; position < s; position++ )
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

         string1.erase( string1.begin() + position );
         string2.erase( string2.begin() + position );

         if( !equal( string1, string2 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test empty string with capacity > 15
void testErase3()
{
   const unsigned int number = 50;
   int numErrors = 0;
   for( int i = 1; i <= number; i++ )
   {
      int c = capacities[ i ]; // c >= 31
      string string1; // empty string
      std::string string2; // empty string

      char **ptr1 = reinterpret_cast< char ** >( &string1 ); // ptr1 points to string1.bx.buf
      char **ptr2 = reinterpret_cast< char ** >( &string2 ) + offset;
      *ptr1 = new char[ c + 1 ];
      *ptr2 = new char[ c + 1 ];

      size_t *myCap1;
      size_t *myCap2;
      if( sizeof( size_t ) == 4 )
      {
         myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
         myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
      }
      else
      {
         myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes
         myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
      }

      *myCap1 = c; // string1.myRes = c
      *myCap2 = c;

      string1.at( 0 ) = '\0'; // string1.bx.ptr[ s ] = '\0'
      string2[ 0 ] = '\0';

      string1.erase( string1.begin() );
      string2.erase( string2.begin() );

      if( !equal( string1, string2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test nonempty string with capacity > 15
void testErase4()
{
   const unsigned int number = 10;
   int numErrors = 0;
   for( int i = 1; i <= number; i++ )
   {
      int c = capacities[ i ]; // c >= 31
      for( int s = 1; s <= c; s++ )
      {
         for( int position = 0; position < s; position++ )
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
            if( sizeof( size_t ) == 4 )
            {
               myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
               myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
            }
            else
            {
               myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes
               myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
            }

            *myCap1 = c; // string1.myRes = c
            *myCap2 = c;

            for( int j = 0; j < s; j++ )
            {
               char value = static_cast< char >( 97 + rand() % 26 );
               string1.at( j ) = value; // string1.bx.ptr[ j ] = value
               string2[ j ] = value;
            }
            string1.at( s ) = '\0'; // string1.bx.ptr[ s ] = '\0'
            string2[ s ] = '\0';

            string1.erase( string1.begin() + position );
            string2.erase( string2.begin() + position );

            if( !equal( string1, string2 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test empty string with capacity == 15
void testErase5()
{
   int numErrors = 0;

   string string1; // empty string
   std::string string2; // empty string

   string1.erase( 0, 0 );
   string2.erase( 0, 0 );

   if( !equal( string1, string2 ) )
      numErrors++;

   cout << "There are " << numErrors << " errors.\n";
}

// test nonempty string with capacity == 15
void testErase6()
{
   int numErrors = 0;

   for( int s = 1; s <= 15; s++ )
   {
      for( int pos = 0; pos < s; pos++ )
      {
         for( int n = 0; n < s; n++ )
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

            string1.erase( pos, n ); // Erases elements [ pos, pos + n ) of string1.
            string2.erase( pos, n ); // Erases elements [ pos..pos + n ) of string2.

            if( !equal( string1, string2 ) )
               numErrors++;
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test empty string with capacity > 15
void testErase7()
{
   const unsigned int number = 50;
   int numErrors = 0;
   for( int i = 1; i <= number; i++ )
   {
      int c = capacities[ i ]; // c >= 31
      string string1; // empty string
      std::string string2; // empty string

      char **ptr1 = reinterpret_cast< char ** >( &string1 ); // ptr1 points to string1.bx.buf
      char **ptr2 = reinterpret_cast< char ** >( &string2 ) + offset;
      *ptr1 = new char[ c + 1 ];
      *ptr2 = new char[ c + 1 ];

      size_t *myCap1;
      size_t *myCap2;
      if( sizeof( size_t ) == 4 )
      {
         myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
         myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
      }
      else
      {
         myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes
         myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
      }

      *myCap1 = c; // string1.myRes = c
      *myCap2 = c;

      string1.at( 0 ) = '\0'; // string1.bx.ptr[ 0 ] = '\0'
      string2[ 0 ] = '\0';

      string1.erase( 0, 0 );
      string2.erase( 0, 0 );

      if( !equal( string1, string2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

// test nonempty string with capacity > 15
void testErase8()
{
   const unsigned int number = 3;
   int numErrors = 0;
   for( int i = 1; i <= number; i++ )
   {
      int c = capacities[ i ]; // c >= 31
      for( int s = 1; s <= c; s++ )
      {
         for( int pos = 0; pos < s; pos++ )
         {
            for( int n = 0; n < s; n++ )
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
               if( sizeof( size_t ) == 4 )
               {
                  myCap1 = reinterpret_cast< size_t * >( &string1 ) + 5; // myCap1 points to string1.myRes
                  myCap2 = reinterpret_cast< size_t * >( &string2 ) + 5 + offset;
               }
               else
               {
                  myCap1 = reinterpret_cast< size_t * >( &string1 ) + 3; // myCap1 points to string1.myRes
                  myCap2 = reinterpret_cast< size_t * >( &string2 ) + 3 + offset;
               }

               *myCap1 = c; // string1.myRes = c
               *myCap2 = c;

               for( int j = 0; j < s; j++ )
               {
                  char value = static_cast< char >( 97 + rand() % 26 );
                  string1.at( j ) = value; // string1.bx.ptr[ j ] = value
                  string2[ j ] = value;
               }
               string1.at( s ) = '\0'; // string1.bx.ptr[ s ] = '\0'
               string2[ s ] = '\0';

               string1.erase( pos, n ); // Erases elements [ pos, pos + n ) of string1.
               string2.erase( pos, n ); // Erases elements [ pos..pos + n ) of string2.

               if( !equal( string1, string2 ) )
                  numErrors++;
            }
         }
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