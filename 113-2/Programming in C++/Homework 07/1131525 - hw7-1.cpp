// 10083 - Division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

const int maxSize = 200;

#include <cstddef>

// CLASS TEMPLATE VectorVal
template< typename ValueType >
class VectorVal
{
public:
   using value_type = ValueType;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   VectorVal()
      : myFirst(),
      myLast(),
      myEnd()
   {
   }

   pointer myFirst; // pointer to beginning of array
   pointer myLast;  // pointer to current end of sequence
   pointer myEnd;   // pointer to end of array
};


// CLASS TEMPLATE vector
template< typename Ty >
class vector // varying size array of values
{
public:
   using value_type = Ty;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = Ty &;
   using const_reference = const Ty &;
   using size_type = size_t;
   using difference_type = ptrdiff_t;

private:
   using ScaryVal = VectorVal< Ty >;

public:
   using iterator = value_type *;
   using const_iterator = const value_type *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   vector()
      : myData()
   {
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   vector( const size_type count )
      : myData()
   {
      if( count != 0 )
      {
         myData.myFirst = new value_type[ count ]();
         myData.myLast = myData.myFirst + count;
         myData.myEnd = myData.myFirst + count;
      }
   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   ////////////////////////////////////////
   vector( const vector &right )
      : myData()
   {
      if( right.size() != 0 ){
         myData.myFirst = new value_type[right.size()]();
         myData.myLast = myData.myFirst + (right.size());
         myData.myEnd = myData.myLast;

         for( int i = 0 ; i < right.size() ; ++i ) myData.myFirst[i] = right.myData.myFirst[i];
      }else{
         myData.myFirst = nullptr;
         myData.myLast = nullptr;
         myData.myEnd = nullptr;
      }
   }

   // Vector destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the vector.
   ~vector()
   {
      if( myData.myFirst != nullptr )
         delete[] myData.myFirst;
   }

   // The vector is extended by inserting a new element before the element
   // at the specified position, effectively increasing the container size by one.
   // This causes an automatic reallocation of the allocated storage space
   // if and only if the new vector size surpasses the current vector capacity.
   // Relocates all the elements that were after "where" to their new positions.
   ////////////////////////////////////////
   iterator insert( const_iterator where, const value_type &val ){
      if( where >= myData.myFirst && where <= myData.myLast ){
         size_type originalSize = size();
         size_type originalCapacity = capacity();
         int idx = where - begin();
         
         if( originalSize == originalCapacity ){
            size_type newCapacity;
            if( originalCapacity <= 1 ) newCapacity = originalCapacity + 1;
            else newCapacity = originalCapacity * 3 / 2;

            iterator buffer = myData.myFirst;

            myData.myFirst = new value_type[newCapacity]();

            for (int i = 0; i < idx; ++i) {
               myData.myFirst[i] = buffer[i];
            }

            myData.myFirst[idx] = val;

            for (int i = idx; i < originalSize; ++i) {
               myData.myFirst[i + 1] = buffer[i];
            }

            delete[] buffer;

            myData.myLast = myData.myFirst + (originalSize + 1);
            myData.myEnd = myData.myFirst + newCapacity;
         }else{
            for (int i = originalSize; i > idx; --i) {
               myData.myFirst[i] = myData.myFirst[i - 1];
            }
   
            myData.myFirst[idx] = val;
   
            myData.myLast = myData.myFirst + originalSize + 1;
         }

         return myData.myFirst + idx;
      }
      else return nullptr;
   }

   // overloaded assignment operator
   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   ////////////////////////////////////////
   vector& operator=( const vector &right ){
      if( this != &right ) // avoid self-assignment
      {
         size_type rightSize = right.size();

         if( rightSize > capacity() ){
            if( size() > 0 ) delete[] myData.myFirst; // release space

            size_type newCapacity = capacity() * 3 / 2;
            if( newCapacity < rightSize ) newCapacity = rightSize;

            myData.myFirst = new value_type[newCapacity]();
            myData.myEnd = myData.myFirst + newCapacity;
         }

         myData.myLast = myData.myFirst + rightSize;

         for( size_t i = 0 ; i < size() ; ++i ){
            myData.myFirst[i] = right.myData.myFirst[i];
         }
      }

      return *this; // enables x = y = z, for example
   }

   // Removes from the vector a single element (where).
   // This effectively reduces the container size by one, which is destroyed.
   // Relocates all the elements after the element erased to their new positions.
   ////////////////////////////////////////
   iterator erase( const_iterator where ){
      if( where >= myData.myFirst && where < myData.myLast ){
         int idx = where - begin();

         for( int i = idx ; i < size() - 1 ; ++i ) myData.myFirst[i] = myData.myFirst[i + 1];
  
         --myData.myLast;
  
         return myData.myFirst + idx;
      }
      else return nullptr;
   }

   // Removes all elements from the vector (which are destroyed),
   // leaving the container with a size of 0.
   // A reallocation is not guaranteed to happen,
   // and the vector capacity is not guaranteed to change due to calling this function.
   void clear(){
      myData.myLast = myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin(){
      return myData.myFirst;
   }

   // Returns an iterator pointing to the first element in the vector.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myFirst );
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   iterator end(){
      return myData.myLast;
   }

   // Returns an iterator referring to the past-the-end element in the vector container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the vector.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as vector::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myLast );
   }

   // Returns a const_iterator pointing to the first element in the container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator cbegin() const
   {
      return begin();
   }

   // Returns a const_iterator pointing to the past-the-end element in the container.
   // If the container is empty, this function returns the same as vector::cbegin.
   // The value returned shall not be dereferenced.
   const_iterator cend() const
   {
      return end();
   }

   // Returns whether the vector is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.myFirst == myData.myLast;
   }

   // Returns the number of elements in the vector.
   // This is the number of actual objects held in the vector,
   // which is not necessarily equal to its storage capacity.
   size_type size() const
   {
      return static_cast< size_type >( myData.myLast - myData.myFirst );
   }

   // Returns the size of the storage space currently allocated for the vector,
   // expressed in terms of elements.
   // This capacity is not necessarily equal to the vector size.
   // It can be equal or greater, with the extra space allowing to accommodate
   // for growth without the need to reallocate on each insertion.
   size_type capacity() const
   {
      return static_cast< size_type >( myData.myEnd - myData.myFirst );
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& front()
   {
      return *myData.myFirst;
   }

   // Returns a reference to the first element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& front() const
   {
      return *myData.myFirst;
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   value_type& back()
   {
      return myData.myLast[ -1 ];
   }

   // Returns a reference to the last element in the vector.
   // Calling this function on an empty container causes undefined behavior.
   const value_type& back() const
   {
      return myData.myLast[ -1 ];
   }

private:

   ScaryVal myData;
};

// determine if two Arrays are equal and return true, otherwise return false
////////////////////////////////////////
template< typename Ty >
bool operator==( const vector< Ty > &left, const vector< Ty > &right ){
   if( left.size() != right.size() ) return false;

   for( int i = 0 ; i < left.size() ; i++ ){
      if( left.begin()[i] != right.begin()[i] ) return false;
   }

   return true;
}

// inequality operator; returns opposite of == operator
template< typename Ty >
bool operator!=( const vector< Ty > &left, const vector< Ty > &right )
{
   return !( left == right );
}


template< typename T >
class HugeInteger
{
   template< typename U >
   friend ostream& operator<<( ostream &output, HugeInteger< U > hugeInteger );
public:
   using value_type = typename T::value_type;
   using size_type = typename T::size_type;

   // constructor; construct a zero HugeInteger with size n
   HugeInteger( unsigned int n = 0 )
      : integer( ( n == 0 ) ? 1 : n )
   {
   }

   // copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
   HugeInteger( const HugeInteger &integerToCopy )
      : integer( integerToCopy.integer )
   {
   }

   // destructor; destroys the HugeInteger
   ~HugeInteger()
   {
   }

   // overloaded assignment operator;
   // return avoids: ( a1 = a2 ) = a3
   const HugeInteger& operator=( const HugeInteger &right )
   {
      if( &right != this ) // avoid self-assignment
         integer = right.integer;

      return *this; // enables x = y = z, for example
   }

   // function that tests if two HugeIntegers are equal
   bool operator==( const HugeInteger &right )
   {
      return ( integer == right.integer );
   } // end function operator==

   // function that tests if one HugeInteger is less than another
   ////////////////////////////////////////
   bool operator<( HugeInteger &right ){
      if( size() > right.size() ) return false;
      if( size() < right.size() ) return true;

      for( size_t i = size() - 1 ; i >= 0 ; --i ){
         if( integer.begin()[i] > right.integer.begin()[i] ) return false;
         if( integer.begin()[i] < right.integer.begin()[i] ) return true;
      }

      return false;
   } // end function operator<

   // function that tests if one HugeInteger is less than or equal to another
   bool operator<=( HugeInteger &right ){
      return ( *this == right || *this < right );
   }

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   ////////////////////////////////////////
   HugeInteger operator-( const HugeInteger &op2 ){
      HugeInteger zero;
      if( *this == op2 )
         return zero;

      HugeInteger difference( *this );

      for( size_t i = 0 ; i < op2.integer.size() ; ++i ){
         difference.integer.begin()[i] += 10;
         difference.integer.begin()[i] -= op2.integer.begin()[i];

         if( difference.integer.begin()[i] < 10 ){
            difference.integer.begin()[i+1] -= 1;
         }

         difference.integer.begin()[i] %= 10;
      }

      while( difference.size() > 1 && difference.integer.begin()[difference.size() - 1] == 0 ){
         difference.integer.erase(difference.integer.end() - 1);
      }

      if( difference.leadingZero() )
         cout << "difference has a leading zero!\n";

      return difference;
   }

   // subtraction assignment operator; HugeInteger -= HugeInteger
   void operator-=( HugeInteger &op2 )
   {
      *this = *this - op2;
   }

   // multiplication operator; HugeInteger * HugeInteger
   ////////////////////////////////////////
   HugeInteger operator*( HugeInteger &op2 )
   {
      HugeInteger zero;
      if( isZero() || op2.isZero() )
         return zero;

      HugeInteger product( integer.size() + op2.integer.size() );

      for( size_t i = 0 ; i < integer.size() ; ++i ){
         for( size_t j = 0 ; j < op2.integer.size() ; ++j ){
            product.integer.begin()[i+j] += integer.begin()[i] * op2.integer.begin()[j];
         }
      }

      for( size_t i = 0 ; i < product.size() ; ++i ){
         if( product.integer.begin()[i] >= 10 ){
            product.integer.begin()[i+1] += product.integer.begin()[i] / 10;
            product.integer.begin()[i] %= 10;
         }
      }

      while( product.size() > 1 && product.integer.begin()[product.size() - 1] == 0 ){
         product.integer.erase(product.integer.end() - 1);
      }

      if( product.leadingZero() )
         cout << "product has a leading zero!\n";

      return product;
   }

   // multiplication assignment operator; HugeInteger *= HugeInteger
   void operator*=( HugeInteger &op2 )
   {
      *this = *this * op2;
   }

   // division operator; HugeInteger / HugeInteger
   // provided that the op2 is not equal to 0
   ////////////////////////////////////////
   HugeInteger operator/( HugeInteger &op2 ){
      HugeInteger zero;

      // cout << "\n----------\n";
      // cout << "OP2  : " << op2 << "\n";
      // cout << "This : " << *this << "\n";
      // cout << "Comp : " << std::boolalpha << (*this < op2) << "\n";
      // cout << "----------\n";

      if( *this < op2 ) return zero;
      
      HugeInteger remainder = *this; // diviend

      size_t n = remainder.size() - op2.integer.size();

      HugeInteger buffer( remainder.size() );
      for( size_t i = 1 ; i <= op2.size() ; ++i ){
         buffer.integer.begin()[buffer.size() - i] = op2.integer.begin()[op2.size() - i];
      }
      
      // cout << "\n----------\n";
      // cout << "REM   : " << remainder << "\n";
      // cout << "BUF   : " << buffer << "\n";
      // cout << remainder << " < " << buffer << " : " << std::boolalpha << (remainder < buffer) << "\n";
      // cout << "----------\n";

      size_t quotientSize = n;
      if( remainder < buffer ) buffer.divideByTen();
      else ++n;

      HugeInteger quotient( n );

      // cout << "\n----------\n";
      // cout << "REM : " << remainder << "\n";
      // cout << "BUF : " << buffer << "\n";
      // cout << "QUO : " << quotient << "\n";
      // cout << "----------\n";
      // system("pause");

      for( int i = quotient.size() - 1 ; i >= 0 ; i-- ){
         // cout << "\n----------\n";
         // cout << "Inside | " << i << "\n";
         // cout << "REM : " << remainder << "\n";
         // cout << "BUF : " << buffer << "\n";
         // cout << "QUO : " << quotient << "\n";
         // cout << "----------\n";

         while( buffer <= remainder ){
            remainder -= buffer;
            ++quotient.integer.begin()[i];

            // cout << "\n----------\n";
            // cout << "While\n";
            // cout << "REM : " << remainder << "\n";
            // cout << "BUF : " << buffer << "\n";
            // cout << "QUO : " << quotient << "\n";
            // cout << "----------\n";
            // system("pause");
            
            if( remainder.isZero() ) return quotient;
         }

         buffer.divideByTen();
      }

      return quotient;
   } // end function operator/

   // modulus operator; HugeInteger % HugeInteger
   // provided that the op2 is not equal to 0
   HugeInteger operator%( HugeInteger &op2 )
   {
      return *this - ( ( *this / op2 ) * op2 );
   }

   // overloaded prefix increment operator 
   HugeInteger& operator++()
   {
      helpIncrement(); // increment integer
      return *this; // reference return to create an lvalue
   }

   // overloaded postfix increment operator;
   // note that the dummy integer parameter does not have a parameter name
   HugeInteger operator++( int )
   {
      HugeInteger temp = *this; // hold current state of object
      helpIncrement();

      // return unincremented, saved, temporary object
      return temp; // value return; not a reference return
   }

   // overloaded prefix decrement operator 
   HugeInteger& operator--()
   {
      helpDecrement(); // increment integer
      return *this; // reference return to create an lvalue
   }

   // overloaded postfix decrement operator;
   // note that the dummy integer parameter does not have a parameter name
   HugeInteger operator--( int )
   {
      HugeInteger temp = *this; // hold current state of object
      helpDecrement();

      // return unincremented, saved, temporary object
      return temp; // value return; not a reference return
   }

   // convert an integer into a HugeInteger
   void convert( const value_type &number ){
      integer.erase( integer.end() - 1 );
      for( value_type i = number; i > 0; i /= 10 )
         integer.insert( integer.end(), i % 10 );
   }

   // compute base raised to the power of expon
   void power( HugeInteger &base, const value_type &expon ){
      *integer.begin() = 1;
      for( value_type i = 0; i < expon; ++i ){
         *this *= base;
         if( integer.size() > maxSize - base.integer.size() ) break;
      }
   }

   size_type size()
   {
      return integer.size();
   }

   // return true if and only if all digits are zero
   bool isZero()
   {
      typename T::iterator it = integer.begin();
      for( ; it != integer.end(); ++it )
         if( *it != 0 )
            return false;

      return true;
   }

   // return true if and only if the leftmost digit is zero
   bool leadingZero()
   {
      return ( integer.size() > 1 && integer.back() == 0 );
   }

private:
   T integer;

   // function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
   void divideByTen(){
      typename T::iterator it = integer.begin() + 1;
      for( ; it != integer.end(); ++it )
         *( it - 1 ) = *it;
      integer.erase( integer.end() - 1 );
   }

   // function to help increment the integer
   void helpIncrement(){
      typename T::iterator it = integer.begin();
      ( *it )++;
      typename T::iterator it2 = it;
      for( ++it2; it2 != integer.end(); ++it, ++it2 )
         if( *it == 10 )
         {
            *it = 0;
            ( *it2 )++;
         }

      if( ( *it ) == 10 ){
         *it = 0;
         integer.insert( integer.end(), 1 );
      }
   }

   // function to help decrement the integer
   void helpDecrement()
   {
      typename T::iterator it = integer.begin();
      for( ; *it == 0; ++it )
         *it = 9;

      ( *it )--;

      if( !isZero() && integer.back() == 0 )
         integer.erase( integer.end() - 1 );
   }
}; // end class HugeInteger


// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   typename T::iterator it = hugeInteger.integer.end() - 1;
   for( ; it != hugeInteger.integer.begin() - 1; --it )
      if( *it < 10 )
         output << *it;

   return output; // enables cout << x << y;
}


template< typename T >
void solution()
{
   T t, a, b;
   while( cin >> t >> a >> b )
   {
      cout << "(" << t << "^" << a << "-1)/(" << t << "^" << b << "-1) ";

      if( t == 1 )
         cout << "is not an integer with less than 100 digits.\n";
      else if( a == b )
         cout << "1\n";
      else if( a < b )
         cout << "is not an integer with less than 100 digits.\n";
      else
      {
         HugeInteger< vector< T > > base;
         base.convert( t ); // put all digits of t into base

         HugeInteger< vector< T > > dividend( 1 );
         dividend.power( base, a ); // dividend = pow( t, a )

         if( dividend.size() > maxSize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            HugeInteger< vector< T > > divisor( 1 );
            divisor.power( base, b ); // divisor = pow( t, b )

            if( divisor.size() > maxSize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               --dividend; // pow( t, a ) - 1
               --divisor;  // pow( t, b ) - 1

               HugeInteger< vector< T > > quotient = dividend / divisor;
               HugeInteger< vector< T > > remainder = dividend % divisor;

               if( quotient.leadingZero() )
                  cout << "quotient has a leading zero!\n";

               if( remainder.leadingZero() )
                  cout << "remainder has a leading zero!\n";

               // quotient is an integer with less than 100 digits
               if( quotient.size() < 100 && remainder.isZero() )
                  cout << quotient << endl;
               else
                  cout << "is not an integer with less than 100 digits.\n";
            }
         }
      }
   }
}

int main()
{
   // execute the following 6 instructions one by one, each of them should get an AC
   solution< int >();
   // solution< unsigned int >();
   // solution< long int >();
   // solution< unsigned long int >();
   // solution< long long int >();
   // solution< unsigned long long int >();
}