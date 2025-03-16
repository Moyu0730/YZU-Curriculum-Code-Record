// SourceLine class member-function definitions.

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip> 

#include "SourceLine.h" // SourceLine class definition

#include "string.h"

// default constructor
SourceLine::SourceLine()
   : sourceLine()
{
}

SourceLine& SourceLine::operator=( const char * const ptr ){
   sourceLine = ptr;
   return *this;
}

void SourceLine::delComments()
{
   size_t length = sourceLine.size();
   if( length > 1 )
      for( size_t i = 0; i < length - 1; i++ )
         if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' )
         {
            sourceLine.erase( i, length );
            break;
         }
}

void SourceLine::delStrConst(){
   for( size_t i = 0 ; i < sourceLine.size() ; ++i ){
	   if( sourceLine[i] == '"' ){
		   for( size_t j = i + 1 ; j < sourceLine.size() ; ++j ){
			   if ( sourceLine[j] == '"' && sourceLine[j-1] != '\\' ) {
				   sourceLine.erase(i, j - i + 1);
				   break;
			   }
		   }
	   }
   }
}

void SourceLine::delCharConst(){
   for( size_t i = 0 ; i < sourceLine.size() ; ++i ){
	   if( sourceLine[i] == '\'' ){
		   for( size_t j = i + 1 ; j < sourceLine.size() ; ++j ){
			   if ( sourceLine[j] == '\'' && sourceLine[j-1] != '\\' ) {
				   sourceLine.erase(i, j - i + 1);
				   break;
			   }
		   }
	   }
   }

   for( size_t i = 0 ; i < sourceLine.size() ; ++i ){
	   if( isalpha(sourceLine[i]) || sourceLine[i] == '_' ) continue;
      if( isalnum(sourceLine[i]) && isalpha(sourceLine[i-1]) ) continue;

      sourceLine[i] = ' ';
   }
}

void SourceLine::extractIdentifiers( vector< Identifier > &identifiers ){
   // cout << sourceLine << " | ";

   for( int i = 0 ; i < sourceLine.size() ; ++i ){
      if( sourceLine[i] != ' ' ) {
         int count = 0;
         for( int j = i ; j <= sourceLine.size() ; ++j ){
            if( ( j == sourceLine.size() && sourceLine[j] != ' ' ) || sourceLine[j] == ' ' ) {

               /* Solution 1 - Valid */
               // Identifier result;
               // result = sourceLine.substr(i, count);
               // identifiers.push_back( result );

               /* Solution 2 - Valid */
               // Identifier resultresult = sourceLine.substr(i, count);
               // identifiers.push_back( result );

               /* Solution 3 - Valid */
               identifiers.push_back( sourceLine.substr(i, count) );

               i = j;
               break;
            }

            ++count;
         }
      }
   }

   /*if( sourceLine[sourceLine.size()-1] != ' ' ){
      for( int i = sourceLine.size() - 1 ; i >= 0 ; --i ){
         int count = 0;
         
         if( sourceLine[i] == ' ' ){
            Identifier result;
            result = sourceLine.substr(i, count);
            
            identifiers.push_back( result );
            break;
         }

         count++;
      }
   }*/

   // cout << "\n";
}

// void SourceLine::print(){
//    size_t length = sourceLine.size();
//    for( size_t i = 0 ; i < length ; ++i ) cout << sourceLine[i];
//    cout << "\n";
// }

bool operator==( const SourceLine &lhs, const SourceLine &rhs )
{
   return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=( const SourceLine &lhs, const SourceLine &rhs )
{
   return !( lhs == rhs );
}