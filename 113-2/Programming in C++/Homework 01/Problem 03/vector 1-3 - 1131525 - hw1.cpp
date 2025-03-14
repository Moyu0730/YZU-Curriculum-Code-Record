#include "vector 1-3.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
{
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
{
   if( count == 0 )
      myFirst = myLast = myEnd = nullptr;
   else
   { 
      myFirst = new value_type[ count ]();
      myLast = myEnd = myFirst + count;
   }
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
vector::iterator vector::insert( const_iterator where, const value_type &val )
{
   if( where >= myFirst && where <= myLast )
   {
      size_type originalSize = size();
      size_type originalCapacity = capacity();
      int idx = where - begin();

      if( originalSize == originalCapacity )
      {
         size_type newCapacity;
         if( originalCapacity <= 1 )
            newCapacity = originalCapacity + 1;
         else
            newCapacity = originalCapacity * 3 / 2;

         pointer buffer = myFirst;

         myFirst = new value_type[newCapacity]();

         for (int i = 0; i < idx; ++i) {
             myFirst[i] = buffer[i];
         }

         myFirst[idx] = val;

         for (int i = idx; i < originalSize; ++i) {
             myFirst[i + 1] = buffer[i];
         }

         delete[] buffer;

         myLast = myFirst + (originalSize + 1);
         myEnd = myFirst + newCapacity;
      }
      else
      {
          for (int i = originalSize; i > idx; --i) {
              myFirst[i] = myFirst[i - 1];
          }

          myFirst[idx] = val;

          myLast = myFirst + originalSize + 1;
      }

      return myFirst + idx;
   }
   else
      return nullptr;
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase( const_iterator where )
{
   if( where >= myFirst && where < myLast )
   {
       int idx = where - myFirst;

       for (int i = idx; i < size() - 1; ++i)
       {
           myFirst[i] = myFirst[i + 1];
       }

       --myLast;

       return myFirst + idx;
   }
   else
      return nullptr;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear()
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
   return myFirst;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
   return myLast;
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty()
{
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size()
{
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity()
{
   return static_cast< size_type >( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::at( const size_type pos )
{
   return myFirst[ pos ];
}