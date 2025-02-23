#include "vector 1-2.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector(){
   myFirst = myLast = myEnd = nullptr;
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector(const size_type count) {
    if (count == 0) {
        myFirst = nullptr;
        myLast = nullptr;
        myEnd = nullptr;
    }
    else {
        myFirst = new int[count]();
        myLast = myFirst + count;
        myEnd = myLast;
    }
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector(){
   if( myFirst != nullptr )
      delete[] myFirst;
}

// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right ){
   if( this != &right ) // avoid self-assignment
   {
      size_type rightSize = right.myLast - right.myFirst;

      if( rightSize > capacity() ){
         if( size() > 0 )
            delete[] myFirst; // release space

         size_type newCapacity = capacity() * 3 / 2;
         if( newCapacity < rightSize )
            newCapacity = rightSize;
         
         myFirst = new int[newCapacity]();
         myEnd = myFirst + newCapacity;
      }

      myLast = myFirst + rightSize;

      for (int i = 0; i < size(); ++i) {
          myFirst[i] = right.myFirst[i];
      }
   }

   return *this; // enables x = y = z, for example
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear(){
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin(){
   return myFirst;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end(){
   return myLast;
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty(){
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size(){
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity(){
   return static_cast< size_type >( myEnd - myFirst );
}

// Returns a reference to the element at position "pos" in the vector container.
vector::value_type& vector::at( const size_type pos ){
   return myFirst[ pos ];
}