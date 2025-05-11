#include <iostream>
using std::cout;
using std::endl;

#include <deque>
#include "1131525 - deque - insert.h"

template< typename T >
void myDequePrint(deque< T >& deque);

template< typename T >
void STLDequePrint(std::deque< T >& deque);

template< typename T >
size_t compDequeSize();

template< typename T >
void testInsert();

template< typename T >
void testInsert1();

template< typename T >
void testInsert2();

template< typename T >
void testInsert3();

template< typename T >
void testInsert4();

template< typename T >
void testInsert5();

template< typename T >
void testInsert6();

template< typename T >
void testInsert7();

template< typename T >
void testInsert8();

template< typename T >
void testInsert9();

template< typename T >
void testInsert10();

template< typename T >
bool equal( std::deque< T > &data1, deque< T > &data2 );

template< typename T >
void myDequePrint(deque< T >& deque) {
    T** map2 = *(reinterpret_cast<T***> (&deque));
    size_t mapSize2 = *(reinterpret_cast<size_t*>(&deque) + 1);
    size_t myOff2 = *(reinterpret_cast<size_t*>(&deque) + 2);
    size_t mySize2 = *(reinterpret_cast<size_t*>(&deque) + 3);

    size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

    cout << "My  Deque Off : " << myOff2 << "My  Deque Size : " << mySize2 << "\n";
    cout << "My  Deque : ";
    for (size_t i = 0; i < dequeSize * mapSize2; ++i) {
        int row = (i / dequeSize) % mapSize2;
        int col = i % dequeSize;
        if (map2[row] != nullptr) cout << (int)map2[row][col] << " ";
    }
    cout << "\n\n";
}

template< typename T >
void STLDequePrint(std::deque< T >& deque) {
    T** map1 = *(reinterpret_cast<T***>(&deque) + 1);
    size_t mapSize1 = *(reinterpret_cast<size_t*>(&deque) + 2);
    size_t myOff1 = *(reinterpret_cast<size_t*>(&deque) + 3);
    size_t mySize1 = *(reinterpret_cast<size_t*>(&deque) + 4);

    size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

    cout << "STL Deque Off : " << myOff1 << ", STL Deque Size : " << mySize1 << "\n";
    cout << "STL Deque : ";
    for (size_t i = 0; i < dequeSize * mapSize1; ++i) {
        int row = (i / dequeSize) % mapSize1;
        int col = i % dequeSize;
        if (map1[row] != nullptr) {
            cout << (int)map1[row][col] << " ";
        }
    }
    cout << "\n";
}

int main()
{
   testInsert< char >();

   testInsert< short >();

   testInsert< long >();

   testInsert< long long >();

   system( "pause" );
}

template< typename T >
void testInsert()
{
/*
*/
   if( sizeof( T ) >= 2 )
      testInsert1< T >();

   testInsert2< T >();

   if( sizeof( T ) >= 2 )
      testInsert3< T >();

   testInsert4< T >();
   testInsert5< T >();
   testInsert6< T >();
   testInsert7< T >();
   testInsert8< T >();
   testInsert9< T >();
   testInsert10< T >();
/*
*/
}

// return number of elements per block (a power of 2)
template< typename T >
size_t compDequeSize()
{
   return sizeof( T ) <= 1 ? 16 : sizeof( T ) <= 2 ? 8 :
          sizeof( T ) <= 4 ?  4 : sizeof( T ) <= 8 ? 2 : 1;
}

template< typename T >
void testInsert1()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 4 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 ){
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff ){
         for( size_t mySize = 1; mySize <= dequeSize * mapSize; ++mySize ){
            for( size_t position = 0; position <= mySize; ++position ){
               std::deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

               deque< T > deque2;
               T ***map2 = reinterpret_cast< T *** > ( &deque2 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

               *mapSize1 = mapSize;
               *mapSize2 = mapSize;
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *myOff2 = myOff;
               *mySize1 = mySize;
               *mySize2 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ ){
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ ){
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               //cout << "\n----------\n";
               //STLDequePrint(deque1);
               //myDequePrint(deque2);

               T value = 1 + rand() % 99;
               typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
               typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

               //cout << "Pos : " << position << ", Val : " << value << "\n";

               if (!equal(deque1, deque2) || *rit1 != *rit2) {
                   //cout << "Error in test 5\n";
                   //cout << "!equal(deque1, deque2) : " << !equal(deque1, deque2) << "\n";
                   //cout << "*rit1 != *rit2 : " << (*rit1 != *rit2) << "\n";
                   //STLDequePrint(deque1);
                   //myDequePrint(deque2);

                   //cout << "For Loop Traverse Auto STLDeque : ";
                   //for (auto it = deque1.begin(); it != deque1.end(); ++it) cout << *it << " ";
                   //cout << "\n";

                   //cout << "For Loop Traverse Auto MyDeque  : ";
                   //for (auto it = deque2.begin(); it != deque2.end(); ++it) cout << *it << " ";
                   //cout << "\n";

                   numErrors++;

                   //system("pause");
               }

               //system("pause");
               //cout << "----------\n";
            }
         }

         if( ( mapSize == 4 * sizeof( T ) && myOff % 8 == 7 ) ||
             ( mapSize == 8 * sizeof( T ) && myOff % 4 == 3 ) )
             cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testInsert2()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 16 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
            for( size_t position = 0; position <= mySize; ++position )
            {
               std::deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** >( &deque1 ) + 1;
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

               deque< T > deque2;
               T ***map2 = reinterpret_cast< T *** > ( &deque2 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

               *mapSize1 = mapSize;
               *mapSize2 = mapSize;
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *myOff2 = myOff;
               *mySize1 = mySize;
               *mySize2 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               {
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               T value = 1 + rand() % 99;
               typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
               typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

               if (!equal(deque1, deque2) || *rit1 != *rit2) {
                   cout << "Error in test 2\n";
                   numErrors++;
               }
            }
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testInsert3()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 4 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 1 ); mySize <= dequeSize * mapSize; ++mySize )
         {
            for( size_t position = 0; position <= mySize; ++position )
            {
               std::deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

               deque< T > deque2;
               T ***map2 = reinterpret_cast< T *** > ( &deque2 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

               *mapSize1 = mapSize;
               *mapSize2 = mapSize;
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *myOff2 = myOff;
               *mySize1 = mySize;
               *mySize2 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               {
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               T value = 1 + rand() % 99;
               typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
               typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

               if (!equal(deque1, deque2) || *rit1 != *rit2) {
                   cout << "Error in test 3\n";
                   numErrors++;
               }
            }
         }

         if( ( mapSize == 4 * sizeof( T ) && myOff % 16 == 15 ) ||
             ( mapSize == 8 * sizeof( T ) && myOff % 8 == 7 ) )
             cout << "There are " << numErrors << " errors\n";
      }
   }

   cout << endl;
}

template< typename T >
void testInsert4()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize; ++mySize )
         {
            size_t pos = ( mySize < 3 ) ? mySize : 3;
            for( size_t position = 0; position <= pos; ++position )
            {
               std::deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

               deque< T > deque2;
               T ***map2 = reinterpret_cast< T *** > ( &deque2 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

               *mapSize1 = mapSize;
               *mapSize2 = mapSize;
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *myOff2 = myOff;
               *mySize1 = mySize;
               *mySize2 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               {
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               T value = 1 + rand() % 99;
               typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
               typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

               if (!equal(deque1, deque2) || *rit1 != *rit2) {
                   cout << "Error in test 4\n";
                   numErrors++;
               }
            }
         }

         switch( sizeof( T ) )
         {
         case 1:
            if( myOff % 16 == 15 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            if( myOff % ( 512 / mapSize ) == 512 / mapSize - 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 4:
         case 8:
            if( ( mapSize == 4 * sizeof( T ) && myOff % 64 == 63 ) ||
                ( mapSize == 8 * sizeof( T ) && myOff % 32 == 31 ) )
               cout << "There are " << numErrors << " errors\n";
            break;
         }
      }
   }

   cout << endl;
}

template< typename T >
void testInsert5()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= dequeSize * mapSize; ++mySize )
         {
            size_t pos = ( mySize < 3 ) ? 0 : mySize - 3;
            for( size_t position = pos; position <= mySize; ++position )
            {
               std::deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

               deque< T > deque2;
               T ***map2 = reinterpret_cast< T *** > ( &deque2 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

               *mapSize1 = mapSize;
               *mapSize2 = mapSize;
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *myOff2 = myOff;
               *mySize1 = mySize;
               *mySize2 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               {
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               T value = 1 + rand() % 99;
               typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
               typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

               if (!equal(deque1, deque2) || *rit1 != *rit2) {
                   cout << "Error in test 5\n";
                   numErrors++;
               }
            }

         }

         switch( sizeof( T ) )
         {
         case 1:
            if( myOff % 16 == 15 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            if( myOff % ( 512 / mapSize ) == 512 / mapSize - 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 4:
         case 8:
            if( ( mapSize == 4 * sizeof( T ) && myOff % 64 == 63 ) ||
               ( mapSize == 8 * sizeof( T ) && myOff % 32 == 31 ) )
               cout << "There are " << numErrors << " errors\n";
            break;
         }
      }
   }

   cout << endl;
}

template< typename T >
void testInsert6()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   #ifdef _WIN64
      const size_t maxMapSize = 256;
   #else
      const size_t maxMapSize = 512;
   #endif

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
            for( size_t position = 0; position <= mySize; ++position )
            {
            std::deque< T > deque1;
            T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
            size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
            size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
            size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

            deque< T > deque2;
            T ***map2 = reinterpret_cast< T *** > ( &deque2 );
            size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
            size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
            size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

            *mapSize1 = mapSize;
            *mapSize2 = mapSize;
            *map1 = new T*[ mapSize ]();
            *map2 = new T*[ mapSize ]();
            *myOff1 = myOff;
            *myOff2 = myOff;
            *mySize1 = mySize;
            *mySize2 = mySize;

            for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
            {
               ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
               ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
            }

            for( size_t i = myOff; i < myOff + mySize; i++ )
            {
               size_t block = i % ( dequeSize * mapSize ) / dequeSize;
               ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
            }

            T value = 1 + rand() % 99;
            typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
            typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

            if (!equal(deque1, deque2) || *rit1 != *rit2) {
                cout << "Error in test 6\n";
                numErrors++;
            }
         }
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testInsert7()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = 0; myOff < 8; ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 2 ); mySize <= dequeSize * mapSize; ++mySize )
            for( size_t position = 0; position <= mySize; ++position )
            {
               std::deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** >( &deque1 ) + 1;
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

               deque< T > deque2;
               T ***map2 = reinterpret_cast< T *** > ( &deque2 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

               *mapSize1 = mapSize;
               *mapSize2 = mapSize;
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *myOff2 = myOff;
               *mySize1 = mySize;
               *mySize2 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               {
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               T value = 1 + rand() % 99;
               typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
               typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

               if (!equal(deque1, deque2) || *rit1 != *rit2) {
                   cout << "Error in test 7\n";
                   numErrors++;
               }
            }

         switch( sizeof( T ) )
         {
         case 1:
            if( myOff % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
         case 4:
         case 8:
            if( ( mapSize == 4 * sizeof( T ) && myOff % 8 == 7 ) ||
                ( mapSize == 8 * sizeof( T ) && myOff % 4 == 3 ) )
               cout << "There are " << numErrors << " errors\n";
         }
      }
   }

   cout << endl;
}

template< typename T >
void testInsert8()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   #ifdef _WIN64
      const size_t maxMapSize = 256;
   #else
      const size_t maxMapSize = 512;
   #endif

   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = dequeSize * ( mapSize - 2 ); myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = 1; mySize <= 8; ++mySize )
            for( size_t position = 0; position <= mySize; ++position )
            {
               std::deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** >( &deque1 ) + 1;
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

               deque< T > deque2;
               T ***map2 = reinterpret_cast< T *** > ( &deque2 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

               *mapSize1 = mapSize;
               *mapSize2 = mapSize;
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *myOff2 = myOff;
               *mySize1 = mySize;
               *mySize2 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               {
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               T value = 1 + rand() % 99;
               typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
               typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

               if (!equal(deque1, deque2) || *rit1 != *rit2) {
                   cout << "Error in test 8\n";
                   numErrors++;
               }
            }
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
void testInsert9()
{
   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   const size_t maxMapSize = 8 * sizeof( T );
   size_t numErrors = 0;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      for( size_t myOff = dequeSize * ( mapSize - 2 ); myOff < dequeSize * ( mapSize + 1 ); ++myOff )
      {
         for( size_t mySize = dequeSize * ( mapSize - 2 ); mySize <= dequeSize * mapSize; ++mySize )
            for( size_t position = 0; position <= mySize; ++position )
            {
               std::deque< T > deque1;
               T ***map1 = reinterpret_cast< T *** >( &deque1 ) + 1;
               size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
               size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
               size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

               deque< T > deque2;
               T ***map2 = reinterpret_cast< T *** > ( &deque2 );
               size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
               size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
               size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

               *mapSize1 = mapSize;
               *mapSize2 = mapSize;
               *map1 = new T * [ mapSize ]();
               *map2 = new T * [ mapSize ]();
               *myOff1 = myOff;
               *myOff2 = myOff;
               *mySize1 = mySize;
               *mySize2 = mySize;

               for( size_t block = myOff / dequeSize; block <= ( myOff + mySize - 1 ) / dequeSize; block++ )
               {
                  ( *map1 )[ block % mapSize ] = new T[ dequeSize ];
                  ( *map2 )[ block % mapSize ] = new T[ dequeSize ];
               }

               for( size_t i = myOff; i < myOff + mySize; i++ )
               {
                  size_t block = i % ( dequeSize * mapSize ) / dequeSize;
                  ( *map1 )[ block ][ i % dequeSize ] = static_cast< T >( i );
                  ( *map2 )[ block ][ i % dequeSize ] = static_cast< T >( i );
               }

               T value = 1 + rand() % 99;
               typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin() + position, value );
               typename deque< T >::iterator rit2 = deque2.insert( deque2.begin() + position, value );

               if (!equal(deque1, deque2) || *rit1 != *rit2) {
                   cout << "Error in test 9\n";
                   numErrors++;
               }
            }

         switch( sizeof( T ) )
         {
         case 1:
            if( myOff % 2 == 1 )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 2:
            if( ( mapSize == 4 * sizeof( T ) && myOff % 8 == 7 ) ||
                ( mapSize == 8 * sizeof( T ) && myOff % 4 == 3 ) )
               cout << "There are " << numErrors << " errors\n";
            break;
         case 4:
         case 8:
            if( ( mapSize == 4 * sizeof( T ) && myOff % 64 == 63 ) ||
                ( mapSize == 8 * sizeof( T ) && myOff % 32 == 31 ) )
               cout << "There are " << numErrors << " errors\n";
            break;
         }
      }
   }

   cout << endl;
}

template< typename T >
void testInsert10()
{
   size_t numErrors = 0;

   {
      std::deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

      deque< T > deque2;
      T ***map2 = reinterpret_cast< T *** > ( &deque2 );
      size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
      size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
      size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

      *mapSize1 = 0;
      *mapSize2 = 0;
      *myOff1 = 0;
      *myOff2 = 0;
      *mySize1 = 0;
      *mySize2 = 0;

      T value = 1 + rand() % 99;
      typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin(), value );
      typename deque< T >::iterator rit2 = deque2.insert( deque2.begin(), value );

      if (!equal(deque1, deque2) || *rit1 != *rit2) {
          cout << "Error in test 10\n";
          numErrors++;
      }
   }

   const size_t maxMapSize = 256;

   for( size_t mapSize = 8; mapSize <= maxMapSize; mapSize *= 2 )
   {
      std::deque< T > deque1;
      T ***map1 = reinterpret_cast< T *** > ( &deque1 ) + 1;
      size_t *mapSize1 = reinterpret_cast< size_t * >( &deque1 ) + 2;
      size_t *myOff1 = reinterpret_cast< size_t * >( &deque1 ) + 3;
      size_t *mySize1 = reinterpret_cast< size_t * >( &deque1 ) + 4;

      deque< T > deque2;
      T ***map2 = reinterpret_cast< T *** > ( &deque2 );
      size_t *mapSize2 = reinterpret_cast< size_t * >( &deque2 ) + 1;
      size_t *myOff2 = reinterpret_cast< size_t * >( &deque2 ) + 2;
      size_t *mySize2 = reinterpret_cast< size_t * >( &deque2 ) + 3;

      *mapSize1 = mapSize;
      *mapSize2 = mapSize;
      *map1 = new T*[ mapSize ]();
      *map2 = new T*[ mapSize ]();
      *myOff1 = 0;
      *myOff2 = 0;
      *mySize1 = 0;
      *mySize2 = 0;

      T value = 1 + rand() % 99;
      typename std::deque< T >::iterator rit1 = deque1.insert( deque1.begin(), value );
      typename deque< T >::iterator rit2 = deque2.insert( deque2.begin(), value );

      if (!equal(deque1, deque2) || *rit1 != *rit2) {
          cout << "Error in test 10-2\n";
          numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors\n\n";
}

template< typename T >
bool equal( std::deque< T > &data1, deque< T > &data2 )
{
   T **map1 = *( reinterpret_cast< T *** > ( &data1 ) + 1 );
   size_t mapSize1 = *( reinterpret_cast< size_t * >( &data1 ) + 2 );
   size_t myOff1 = *( reinterpret_cast< size_t * >( &data1 ) + 3 );
   size_t mySize1 = *( reinterpret_cast< size_t * >( &data1 ) + 4 );

   T **map2 = *( reinterpret_cast< T *** > ( &data2 ) );
   size_t mapSize2 = *( reinterpret_cast< size_t * >( &data2 ) + 1 );
   size_t myOff2 = *( reinterpret_cast< size_t * >( &data2 ) + 2 );
   size_t mySize2 = *( reinterpret_cast< size_t * >( &data2 ) + 3 );

   if (mapSize1 != mapSize2) {
       cout << "Map Size Error\n";
       return false;
   }

   if( mapSize2 == 0 )
      if( mySize2 == 0 && myOff2 == 0 && map2 == nullptr )
         return true;
      else
         return false;

   if (myOff1 != myOff2) {
       cout << "My Off Error\n";
       //STLDequePrint(data1);
       //myDequePrint(data2);
       //cout << "STL Deque Off : " << myOff1 << ", My Deque Off : " << myOff2 << "\n";
       return false;
   }

   if (mySize1 != mySize2) {
       cout << "My Size Error\n";
       return false;
   }

   size_t dequeSize = compDequeSize< T >(); // elements per block (a power of 2)

   size_t row, col;
   for( size_t i = 0; i < dequeSize * mapSize1; ++i )
   {
      row = ( i / dequeSize ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] == nullptr )
         return false;

      if( map1[ row ] == nullptr && map2[ row ] != nullptr )
         return false;
   }

   for( size_t i = myOff1; i < myOff1 + mySize1; ++i )
   {
      row = ( i / dequeSize ) % mapSize1;
      if( map1[ row ] != nullptr && map2[ row ] != nullptr )
      {
         col = i % dequeSize;
         if( map1[ row ][ col ] != map2[ row ][ col ] )
            return false;
      }
   }

   return true;
}