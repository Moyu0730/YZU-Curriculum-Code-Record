#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <iomanip>

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
   using size_type = typename MyDeque::size_type;

public:
   using value_type = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer = typename MyDeque::const_pointer;
   using reference = const value_type &;

   // construct with null pointer
   DequeConstIterator()
      : myOff( 0 ),
      myCont( nullptr )
   {
   }

   // construct with offset off in *pDeque
   DequeConstIterator( size_type off, const MyDeque *pDeque )
      : myOff( off ),
      myCont( pDeque )
   {
   }

   DequeConstIterator( const DequeConstIterator &right ) // copy constructor
      : myOff( right.myOff ),
      myCont( right.myCont )
   {
   }

   ~DequeConstIterator() // destructor
   {
   }

   // const return avoids: ( a1 = a2 ) = a3
   const DequeConstIterator& operator=( const DequeConstIterator &right )
   {
      if( &right != this ) // avoid self-assignment
      {
         myCont = right.myCont;
         myOff = right.myOff;
      }
      return *this; // enables x = y = z, for example
   }

   reference operator*() const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

//      size_type block = myOff % ( dequeSize * myCont->mapSize ) / dequeSize;
      size_type block = myCont->getBlock( myOff );
      size_type off = myOff % dequeSize;
      return myCont->map[ block ][ off ];
   }

   pointer operator->() const
   {
      return &( operator*() );
   }

   DequeConstIterator& operator++() // preincrement
   {
      ++myOff;
      return *this;
   }

   DequeConstIterator operator++( int ) // postincrement
   {
      DequeConstIterator tmp = *this;
      ++*this;
      return tmp;
   }

   DequeConstIterator& operator--() // predecrement
   {
      --myOff;
      return *this;
   }

   DequeConstIterator operator--( int ) // postdecrement
   {
      DequeConstIterator tmp = *this;
      --*this;
      return tmp;
   }

   // increment by integer
   DequeConstIterator& operator+=( const difference_type off )
   {
      myOff += off;
      return *this;
   }

   // return this + integer
   DequeConstIterator operator+( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeConstIterator& operator-=( const difference_type off )
   {
      return *this += -off;
   }

   // return this - integer
   DequeConstIterator operator-( const difference_type off ) const
   {
      DequeConstIterator tmp = *this;
      return tmp -= off;
   }

   // return difference of iterators
   difference_type operator-( const DequeConstIterator &right ) const
   {
      return ( static_cast< difference_type >( this->myOff - right.myOff ) );
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return *( *this + off );
   }

   // test for iterator equality
   bool operator==( const DequeConstIterator &right ) const
   {
      return this->myCont == right.myCont && this->myOff == right.myOff;
   }

   // test for iterator inequality
   bool operator!=( const DequeConstIterator &right ) const
   {
      return !( *this == right );
   }

   // test if this < right
   bool operator<( const DequeConstIterator &right ) const
   {
      return this->myOff < right.myOff;
   }

   // test if this > right
   bool operator>( const DequeConstIterator &right ) const
   {
      return right < *this;
   }

   // test if this <= right
   bool operator<=( const DequeConstIterator &right ) const
   {
      return !( right < *this );
   }

   // test if this >= right
   bool operator>=( const DequeConstIterator &right ) const
   {
      return !( *this < right );
   }

   const MyDeque *myCont; // keep a pointer to deque
   size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
   using size_type = typename MyDeque::size_type;
   using MyBase = DequeConstIterator< MyDeque >;

public:
   using value_type = typename MyDeque::value_type;
   using difference_type = typename MyDeque::difference_type;
   using pointer = typename MyDeque::pointer;
   using reference = value_type &;

   DequeIterator() // construct with null deque pointer
   {
   }

   DequeIterator( size_type off, const MyDeque *pDeque )
      : MyBase( off, pDeque ) // construct with offset off in *pDeque
   {
   }

   reference operator*() const // return designated object
   {
      return const_cast< reference >( MyBase::operator*() );
   }

   pointer operator->() const // return pointer to class object
   {
      return const_cast< pointer >( MyBase::operator->() );
      //      return &( operator*() );
   }

   DequeIterator& operator++() // preincrement
   {
      MyBase::operator++();
      return *this;
   }

   DequeIterator operator++( int ) // postincrement
   {
      DequeIterator tmp = *this;
      MyBase::operator++();
      return tmp;
   }

   DequeIterator& operator--() // predecrement
   {
      MyBase::operator--();
      return *this;
   }

   DequeIterator operator--( int ) // postdecrement
   {
      DequeIterator tmp = *this;
      MyBase::operator--();
      return tmp;
   }

   // increment by integer
   DequeIterator& operator+=( const difference_type off )
   {
      MyBase::operator+=( off );
      return *this;
   }

   // return this + integer
   DequeIterator operator+( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp += off;
   }

   // decrement by integer
   DequeIterator& operator-=( const difference_type off )
   {
      MyBase::operator-=( off );
      return *this;
   }

   using MyBase::operator-; // return difference of iterators

   // return this - integer
   DequeIterator operator-( const difference_type off ) const
   {
      DequeIterator tmp = *this;
      return tmp -= off;
   }

   reference operator[]( const difference_type off ) const // subscript
   {
      return const_cast< reference >( MyBase::operator[]( off ) );
   }
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;
   using MapPtr = Ty **;

   DequeVal() // initialize values
      : map(),
      mapSize( 0 ),
      myOff( 0 ),
      mySize( 0 )
   {
   }

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      // elements per block (a power of 2)
      size_type dequeSize = sizeof( value_type ) <= 1 ? 16 :
                            sizeof( value_type ) <= 2 ?  8 :
                            sizeof( value_type ) <= 4 ?  4 :
                            sizeof( value_type ) <= 8 ?  2 : 1;

      return off / dequeSize % mapSize;
//      return off % ( dequeSize * mapSize ) / dequeSize;
//      return ( off / dequeSize ) & ( mapSize - 1 );
   }

   MapPtr map;        // pointer to array of pointers to blocks
   size_type mapSize; // size of map array, zero or 2^N
   size_type myOff;   // offset of initial element
   size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
   using MapPtr = Ty **;
   using ScaryVal = DequeVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = DequeIterator< ScaryVal >;
   using const_iterator = DequeConstIterator< ScaryVal >;

   // construct empty deque
   deque()
      : myData()
   {
   }

   // destroy the deque
   ~deque()
   {
      clear();
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   deque& operator=( const deque &right )
   {
      //cout << "\n-----Start operator=-----\n";

      //cout << "Before A\n";
      //for (int i = 0; i < myData.mapSize; ++i) {
      //    cout << "\t" << myData.map[i] << "\n";
      //}

      if( &right != this ) // avoid self-assignment
      {
         // elements per block (a power of 2)
         size_type dequeSize = compDequeSize();

         //cout << "Enter\n";

         if( myData.mySize < right.myData.mySize )
         {  // allocate memory space in the current object
            size_type newMapSize = 8;
            while( right.myData.mySize > dequeSize * newMapSize )
               newMapSize *= 2;

            if( ( myData.myOff % dequeSize == 0 && right.myData.mySize > dequeSize * ( newMapSize - 1 ) &&
                  myData.mySize <= dequeSize * ( newMapSize - 1 ) ) ||
                ( myData.myOff % dequeSize > 0 && myData.myOff % dequeSize + right.myData.mySize > dequeSize * newMapSize ) )
               newMapSize *= 2;

            //cout << "A NewMapSize : " << newMapSize << ", OldMapSize : " << myData.mapSize << "\n";
            if (newMapSize > myData.mapSize) {
                enlargeMap(newMapSize); // reuse the original memory space in the current object
            }

            int Filled = myData.myOff / dequeSize;
            int Finished = 0;
            int sufficientSize = right.myData.mySize + (myData.myOff - Filled * dequeSize);

            //cout << "A " << Filled << " " << Finished << " " << sufficientSize << " " << myData.myOff - Filled * dequeSize << "\n";
            while ( Finished < sufficientSize ) {
                if (myData.map[Filled] == nullptr) {
                    //cout << "New  " << Filled << "\n";
                    myData.map[Filled] = new value_type[dequeSize];
                }

                Finished += dequeSize;
                ++Filled;
                Filled %= myData.mapSize;

                //cout << "Finished : " << Finished << " Filled : " << Filled << "\n";
            }

            //cout << "\n";
         }

         //cout << "Before B\n";
         //for (int i = 0; i < myData.mapSize; ++i) {
         //    cout << "\t" << myData.map[i] << "\n";
         //}

         myData.mySize = right.myData.mySize;

         if( right.myData.mySize == 0 )
             myData.myOff = 0;
         else{  // copy data from right to the current object
             int Finished = 0, rightFinished = right.myData.myOff;
             //cout << "B " << "Deque Size : " << dequeSize << "\n";
             //cout << "B " << "rightSize : " << right.myData.mySize << ", rightMapSize : " << right.myData.mapSize << ", rightOff : " << right.myData.myOff << "\n";
             //cout << "B " << "mySize    : " << myData.mySize       << ", myMapSize    : " << myData.mapSize       << ", myOff    : " << myData.myOff << "\n";
             while (Finished < right.myData.mySize) {
                 size_t I = ((myData.myOff + Finished) / dequeSize) % myData.mapSize;
                 size_t J = (myData.myOff + Finished) % dequeSize;
                 size_t rightI = (rightFinished / dequeSize) % right.myData.mapSize;
                 size_t rightJ = rightFinished % dequeSize;

                 //cout << Finished << " Assign (" << rightI << ", " << rightJ << ") to (" << I << ", " << J << ") ";
                 //cout << "Value (" << myData.map[I][0] << ")";

                 //if (myData.map[I] == nullptr && right.myData.map[rightI] == nullptr)cout << "Both NULL";
                 //else if (myData.map[I] == nullptr) cout << "My NULL";
                 //else if (right.myData.map[rightI] == nullptr) cout << "Right NULL";

                 //cout << "\n";

                 myData.map[I][J] = right.myData.map[rightI][rightJ];

                 ++Finished;
                 ++rightFinished;
             }

             //cout << "\n" << Finished << "\n";
             //system("pause");
         }
      }

      //cout << "-----Finish operator=-----\n";

      return *this; // enables x = y = z, for example
   } // end function operator=

   // return iterator for beginning of mutable sequence
   iterator begin()
   {
      return iterator( myData.myOff, &myData );
   }

   // return iterator for beginning of nonmutable sequence
   const_iterator begin() const
   {
      return const_iterator( myData.myOff, &myData );
   }

   // return iterator for end of mutable sequence
   iterator end()
   {
      return iterator( myData.myOff + myData.mySize, &myData );
   }

   // return iterator for end of nonmutable sequence
   const_iterator end() const
   {
      return const_iterator( myData.myOff + myData.mySize, &myData );
   }

   // return length of sequence
   size_type size() const
   {
      return myData.mySize;
   }

   // test if sequence is empty
   bool empty() const
   {
      return myData.mySize == 0;
   }

// erase all
void clear()
{
   if( myData.mapSize > 0 )
   {
      for( size_type i = 0; i < myData.mapSize; i++ )
         if( myData.map[ i ] != nullptr )
            delete[] myData.map[ i ];
      delete[] myData.map;

      myData.mapSize = 0;
      myData.mySize = 0;
      myData.myOff = 0;
      myData.map = MapPtr();
   }
}

private:

   // determine block from offset
   size_type getBlock( size_type off ) const
   {
      return myData.getBlock( off );
//      return ( ( myData.off / compDequeSize() ) & ( myData.mapSize - 1 ) );
   }

   void enlargeMap( size_type newMapSize )
   {
       size_type oldMapSize = myData.mapSize;
       myData.mapSize = newMapSize;
       value_type** newMap = new value_type * [myData.mapSize]();

       size_type dequeSize = compDequeSize();

       if (myData.mySize > 0) {
           int Finished = myData.myOff / dequeSize;

           while ( Finished < oldMapSize && myData.map[Finished] != nullptr) {
               //cout << "Copy " << Finished << "\n";
               newMap[Finished] = myData.map[Finished];

               ++Finished;
           }

           delete[] myData.map;
       }

       myData.map = newMap;
   }

   size_type compDequeSize()
   {
      return sizeof( value_type ) <= 1 ? 16 : sizeof( value_type ) <= 2 ? 8 :
             sizeof( value_type ) <= 4 ?  4 : sizeof( value_type ) <= 8 ? 2 : 1;
   }

   ScaryVal myData;
};

#endif