// 10083 - Division
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

const int maxSize = 200;

template< typename ValueType >
struct ListNode // list node
{
   ListNode *next;  // successor node, or first element if head
   ListNode *prev;  // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
      mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      // cout << "Default Constructor Applied\n";
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   ////////////////////////////////////////
   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      // cout << "[ Fill Constructor Applied ]\n";
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      for (int i = 0; i < count; ++i) {
         nodePtr newNode = new node();

         newNode->myVal = Ty();
         newNode->prev = myData.myHead->prev;
         newNode->next = myData.myHead;
         myData.myHead->prev->next = newNode;
         myData.myHead->prev = newNode;
     }

     myData.mySize = count;
   //   cout << "[ Fill Constructor Finished ]\n";
   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   ////////////////////////////////////////
   list( const list &right )
      : myData()
   {
      // cout << "[ Copy Constructor Applied ]\n";

      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      for(int i = 0; i < right.size(); ++i ){
         // cout << "   Copy Constructor " << i << " Round Start\n";

         nodePtr newNode = new node();

         newNode->myVal = Ty();
         newNode->prev = myData.myHead->prev;
         newNode->next = myData.myHead;
         myData.myHead->prev->next = newNode;
         myData.myHead->prev = newNode;

         // cout << "   Copy Constructor " << i << " Round Finished\n";
      }

      // cout << "   Copy Constructor for Finished\n";

      myData.mySize = right.size();

      nodePtr newIt = myData.myHead->next;
      nodePtr rightIt = right.myData.myHead->next;

      while( newIt != myData.myHead ){
         newIt->myVal = rightIt->myVal;
         newIt = newIt->next;
         rightIt = rightIt->next;
      }

      // cout << "[ Copy Constructor Finished ]\n";
   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   ////////////////////////////////////////
   list& operator=( const list &right ){
      if( this != &right ){
         if( right.myData.mySize == 0 ) // the right list is empty
         {
            if( myData.mySize != 0 ) // the left list is not empty
               clear();
         }else // the right list is not empty
         {
            int difSize = right.myData.mySize - myData.mySize;
            myData.mySize += difSize;

            if ( difSize > 0 ) {
               for (int i = 0; i < difSize; ++i) {
                  node* newNode = new node();

                  newNode->myVal = Ty();
                  newNode->prev = myData.myHead->prev;
                  newNode->next = myData.myHead;
                  myData.myHead->prev->next = newNode;
                  myData.myHead->prev = newNode;
               }
            } else if ( difSize < 0 ) {
               difSize *= -1;
               for (int i = 0; i < difSize; ++i) {
                  myData.myHead->prev = myData.myHead->prev->prev;
                  delete myData.myHead->prev->next;
                  myData.myHead->prev->next = myData.myHead;
               }
            }

            node* newIt = myData.myHead->next;
            node* rightIt = right.myData.myHead->next;

            while (newIt != myData.myHead) {
               newIt->myVal = rightIt->myVal;
               newIt = newIt->next;
               rightIt = rightIt->next;
            }
         }
      }

      return *this;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin(){
      return myData.myHead->next;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return myData.myHead;
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference front()
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   // The container is extended by inserting a new element
   // before the element at the specified position.
   // This effectively increases the list size by the amount of elements inserted.
   // Returns an iterator that points to the newly inserted element.
   ////////////////////////////////////////
   iterator insert( const_iterator where, const Ty &val ) // insert val at where
   {
      nodePtr newNode = new node;
      newNode->myVal = val;

      nodePtr cnt = where->prev->next;

      newNode->prev = cnt->prev;
      newNode->next = cnt;
      cnt->prev->next = newNode;
      cnt->prev = newNode;

      myData.mySize += 1;

      return iterator( newNode );
   }

   // Removes from the list container the element at the specified position.
   // This effectively reduces the container size one, which is destroyed.
   // Returns an iterator pointing to the element that followed the element erased.
   // This is the container end if the operation erased the last element in the sequence.
   ////////////////////////////////////////
   iterator erase( const_iterator where ){
      if (myData.mySize == 0) return iterator(where);

      nodePtr temp = where->next;
      where->prev->next = where->next;
      where->next->prev = where->prev;

      delete where;

      --myData.mySize;

      return iterator(temp);
   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   ////////////////////////////////////////
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
         while( myData.myHead->next != myData.myHead )
         {
            myData.myHead->next = myData.myHead->next->next;
            delete myData.myHead->next->prev;
         }

         myData.myHead->prev = myData.myHead;
         myData.mySize = 0;
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
////////////////////////////////////////
template< typename Ty >
bool operator==( const list< Ty > &left, const list< Ty > &right ){
   if( left.size() != right.size() ) return false;

   typename list<Ty>::const_iterator leftIt = left.begin();
   typename list<Ty>::const_iterator rightIt = right.begin();

   while( leftIt != left.end() ){
      if( leftIt->myVal != rightIt->myVal ) return false;
      
      leftIt = leftIt->next;
      rightIt = rightIt->next;
   }

   return true;
}

template< typename Ty >
bool operator!=( const list< Ty > &left, const list< Ty > &right )
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
   const HugeInteger& operator=( const HugeInteger &right ){
      if( &right != this ) // avoid self-assignment
         integer = right.integer;

      return *this; // enables x = y = z, for example
   }

   // function that tests if two HugeIntegers are equal
   bool operator==( const HugeInteger &right ){
      return ( integer == right.integer );
   } // end function operator==

   // function that tests if one HugeInteger is less than another
   ////////////////////////////////////////
   bool operator<( HugeInteger &right ){
      if( size() < right.size() ) return true;
      if( size() > right.size() ) return false;

      ListNode<value_type>* It = integer.end()->prev;
      ListNode<value_type>* rightIt = right.integer.end()->prev;

      while( It != integer.end() ){
         if( It->myVal < rightIt->myVal ) return true;
         if( It->myVal > rightIt->myVal ) return false;

         It = It->prev;
         rightIt = rightIt->prev;
      }

      return false;
   } // end function operator<

   // function that tests if one HugeInteger is less than or equal to another
   bool operator<=( HugeInteger &right )
   {
      return ( *this == right || *this < right );
   }

   // subtraction operator; HugeInteger - HugeInteger provided that
   // the minuend is greater than or equal to the subtrahend
   ////////////////////////////////////////
   HugeInteger operator-( const HugeInteger &op2 ){
      HugeInteger zero;
      if( *this == op2 ) return zero;

      HugeInteger difference( *this );

      typename T::iterator op2It = const_cast<typename T::iterator>(op2.integer.begin());
      typename T::iterator differenceIt = const_cast<typename T::iterator>(difference.integer.begin());

      for( size_t i = 0 ; i < op2.integer.size() ; ++i ){
         differenceIt->myVal += 10;
         differenceIt->myVal -= op2It->myVal;

         if( differenceIt->myVal < 10 ){
            differenceIt->next->myVal -= 1;
         }

         differenceIt->myVal %= 10;

         differenceIt = differenceIt->next;
         op2It = op2It->next;
      }

      while( difference.size() > 1 && difference.integer.end()->prev->myVal == 0 ){
         difference.integer.erase(difference.integer.end()->prev);
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
   HugeInteger operator*( HugeInteger &op2 ){
      HugeInteger zero;
      if( isZero() || op2.isZero() ) return zero;

      // cout << "      operator* Start\n";
      // cout << integer;
      // cout << " * ";
      // cout << op2.integer << "\n";
      // cout << integer << "\n";

      HugeInteger product( integer.size() + op2.integer.size() );

      // cout << "      Product Initial Value : " << product << "\n";

      size_t start = 0;
      for( typename T::iterator It = integer.begin() ; It != integer.end() ; It = It->next, ++start ){
         typename T::iterator productIt = product.integer.begin();
         for( size_t i = 0 ; i < start ; ++i ) productIt = productIt->next;
         
         for( typename T::iterator op2It = op2.integer.begin() ; op2It != op2.integer.end() ; op2It = op2It->next ){
            productIt->myVal += op2It->myVal * It->myVal;
            productIt = productIt->next;
         }
      }

      // cout << "         operator* for Finished with Value " << product << "\n";

      for( typename T::iterator productIt = product.integer.begin() ; productIt != product.integer.end() ; productIt = productIt->next ){
         if( productIt->myVal >= 10 ){
            productIt->next->myVal += productIt->myVal / 10;
            productIt->myVal %= 10;
         }
      }

      while( product.size() > 1 && product.integer.end()->prev->myVal == 0 ){
         product.integer.erase(product.integer.end()->prev);
      }

      if( product.leadingZero() ) cout << "product has a leading zero!\n";

      // cout << "      operator* Finished with Value " << product << "\n";

      return product;
   }

   // multiplication assignment operator; HugeInteger *= HugeInteger
   void operator*=( HugeInteger &op2 ){
      *this = *this * op2;
   }

   // division operator; HugeInteger / HugeInteger
   // provided that the op2 is not equal to 0
   ////////////////////////////////////////
   HugeInteger operator/( HugeInteger &op2 ){
      HugeInteger zero;
      if( *this < op2 ) return zero;

      HugeInteger remainder = *this; // diviend

      size_t n = remainder.size() - op2.integer.size();

      HugeInteger buffer( remainder.size() );
      
      typename T::iterator bufferIt = buffer.integer.end()->prev;
      typename T::iterator op2It = op2.integer.end()->prev;
      for( size_t i = 1 ; i <= op2.size() ; ++i ){
         bufferIt->myVal = op2It->myVal;

         bufferIt = bufferIt->prev;
         op2It = op2It->prev;
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

      for( typename T::iterator quotientIt = quotient.integer.end()->prev ; quotientIt != quotient.integer.end() ; quotientIt = quotientIt->prev ){
         // cout << "\n----------\n";
         // cout << "Inside\n";
         // cout << "REM : " << remainder << "\n";
         // cout << "BUF : " << buffer << "\n";
         // cout << "QUO : " << quotient << "\n";
         // cout << "----------\n";

         while( buffer <= remainder ){
            remainder -= buffer;
            ++quotientIt->myVal;

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
   void convert( const value_type &number )
   {
      integer.erase( integer.end()->prev );
      for( value_type i = number; i > 0; i /= 10 )
         integer.insert( integer.end(), i % 10 );
   }

   // compute base raised to the power of expon
   void power( HugeInteger &base, const value_type &expon )
   {
      // cout << "power Start\n";

      integer.begin()->myVal = 1;
      for( value_type i = 0; i < expon; ++i ){
         // cout << "   power " << i << " Round Start\n";

         *this *= base;
         // cout << "      THIS : " << *this << "\n";
         // cout << "      BASE : " << base << "\n";
         // cout << "      RESL : " << *this * base << "\n";

         // cout << "   power " << i << " Round Finished\n";

         if( integer.size() > maxSize - base.integer.size() ) break;
      }

      // cout << "power Finished\n";
   }

   size_type size(){
      return integer.size();
   }

   // return true if and only if all digits are zero
   bool isZero()
   {
      typename T::iterator it = integer.begin();
      for( ; it != integer.end(); it = it->next )
         if( it->myVal != 0 )
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
   void divideByTen()
   {
      typename T::iterator it = integer.begin()->next;
      for( ; it != integer.end(); it = it->next )
         ( it->prev )->myVal = it->myVal;
      integer.erase( integer.end()->prev );
   }

   // function to help increment the integer
   void helpIncrement()
   {
      typename T::iterator it = integer.begin();
      ( it->myVal )++;
      typename T::iterator it2 = it;
      for( it2 = it2->next; it2 != integer.end(); it = it->next, it2 = it2->next )
         if( it->myVal == 10 )
         {
            it->myVal = 0;
            ( it2->myVal )++;
         }

      if( ( it->myVal ) == 10 )
      {
         it->myVal = 0;
         integer.insert( integer.end(), 1 );
      }
   }

   // function to help decrement the integer
   void helpDecrement()
   {
      typename T::iterator it = integer.begin();
      for( ; it->myVal == 0; it = it->next )
         it->myVal = 9;

      ( it->myVal )--;

      if( !isZero() && integer.back() == 0 )
         integer.erase( integer.end()->prev );
   }
}; // end class HugeInteger


// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<( ostream &output, HugeInteger< T > hugeInteger )
{
   // cout << "operator<< Start\n";

   typename T::iterator it = hugeInteger.integer.end()->prev;
   for( ; it != hugeInteger.integer.begin()->prev; it = it->prev )
      if( it->myVal < 10 )
         output << it->myVal;

   // cout << "operator<< Finished\n";

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
         // cout << "\n\n[ Program Start ]\n\n";

         HugeInteger< list< T > > base;

         // cout << "Base (" << base << ") Finished\n";

         base.convert( t ); // put all digits of t into base

         // cout << "Base Finished\n";

         HugeInteger< list< T > > dividend( 1 );
         dividend.power( base, a ); // dividend = pow( t, a )

         // cout << "DIVIDEND : " << dividend << "\n";

         if( dividend.size() > maxSize - base.size() )
            cout << "is not an integer with less than 100 digits.\n";
         else
         {
            HugeInteger< list< T > > divisor( 1 );
            divisor.power( base, b ); // divisor = pow( t, b )

            if( divisor.size() > maxSize - base.size() )
               cout << "is not an integer with less than 100 digits.\n";
            else
            {
               --dividend; // pow( t, a ) - 1
               --divisor;  // pow( t, b ) - 1

               // cout << "\n----------\n";
               // cout << "DIVIDEND : " << dividend << "\n";
               // cout << "DIVSOR   : " << divisor << "\n";
               // cout << "----------\n";
               // system("pause");

               HugeInteger< list< T > > quotient = dividend / divisor;
               HugeInteger< list< T > > remainder = dividend % divisor;

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