#include <iostream>
#include <cstring>
#include <fstream>
using namespace::std;

struct Member
{
   char email[ 40 ];
   char password[ 24 ];
   char IDNumber[ 12 ];
   char name[ 12 ];
   char phone[ 12 ];
};

void loadMemberInfo( ifstream &inMemberFile, Member memberDetails[], int &numMembers );

// input an integer from the keyboard, and
// returns the integer if it belongs to [ begin, end ], returns -1 otherwise.
int inputAnInteger( int begin, int end );

void login( Member memberDetails[], int numMembers );

// returns true if there is a member
// whose email and password are equal to the specified email and password, respectively
bool legal( char email[], char password[], Member memberDetails[], int numMembers, int &recordNumber );

void accountInfor( Member memberDetails[], int numMembers, int recordNumber );

void newMember( Member memberDetails[], int &numMembers );

// returns true if there is a member whose IDNumber is equal to newIDNumber
bool existingID( char newIDNumber[], Member memberDetails[], int &numMembers );

// returns true if there is a member whose email is equal to newEmail
bool existingEmail( char newEmail[], Member memberDetails[], int &numMembers );

void saveMemberInfo( ofstream &outMemberFile, Member memberDetails[], int numMembers );

int main()
{
   Member memberDetails[ 100 ] = { "", "", "", "", "" };
   int numMembers = 0;

   ifstream inMemberFile;
   ofstream outMemberFile;

   loadMemberInfo( inMemberFile, memberDetails, numMembers );

   // cout << "-----\n";
   // for( int i = 0 ; i < numMembers ; ++i ){
   //    cout << i << " | " 
   //         << memberDetails[i].email << " " << memberDetails[i].IDNumber << " "
   //         << memberDetails[i].name << " " << memberDetails[i].password << " "
   //         << memberDetails[i].phone << "\n";
   // }
   // cout << "-----\n";

   cout << "Welcome to Vieshow Cinemas member system\n\n";

   int choice;

   while( true )
   {
      cout << "Enter your choice:" << endl;
      cout << "1. Sign In\n";
      cout << "2. New Member\n";
      cout << "3. Sign Out\n? ";

      choice = inputAnInteger( 1, 3 );
      cout << endl;

      switch( choice ){
         case 1:
            login( memberDetails, numMembers );
            break;

         case 2:
            newMember( memberDetails, numMembers );
            break;

         case 3:
            saveMemberInfo( outMemberFile, memberDetails, numMembers );
            cout << "Thank you...\n\n";
            return 0;

         default:
            cout << "Input Error!\n\n";
            break;
      }
   }

   system( "pause" );
}

void loadMemberInfo( ifstream &inMemberFile, Member memberDetails[], int &numMembers ){
   inMemberFile.open( "MemberInfo.dat", ios::in | ios::binary );

   if( !inMemberFile ) {
      cerr << "File could not be opened." << endl;
      system( "pause" );
      exit( 1 );
   }

   int ind = 0;
   
   while( inMemberFile.read( reinterpret_cast< char * >( &memberDetails[ind] ), sizeof( Member ) ) ){
      ind++;
   }

   numMembers = ind;

   return;
}

// input an integer from the keyboard, and
// returns the integer if it belongs to [ begin, end ], returns -1 otherwise.
int inputAnInteger( int begin, int end ){
   string str; cin >> str;

   int res = 0;
   for( int i = 0 ; i < str.size() ; ++i ){
      if( !isdigit(str[i]) ) return -1;
      else{
         res *= 10;
         res += str[i] - '0';
      }
   }

   if( res >= begin && res <= end ) return res;
   else return -1;
}

void login( Member memberDetails[], int numMembers ){
   char email[40], password[24];
   cout << "Enter email address: ";
   cin >> email;

   cout << "Enter password: ";
   cin >> password;

   int ind = 0;
   if( legal(email, password, memberDetails, numMembers, ind) ){
      int choice;
      while( true ){
         cout << "\nEnter your choice:" << endl;
         cout << "1. Account Information\n";
         cout << "2. Buy Tickets\n";
         cout << "3. End\n? ";

         choice = inputAnInteger( 1, 3 );
         cout << "\n";

         switch( choice ){
            case 1:
               accountInfor(memberDetails, numMembers, ind);
               break;

            case 2:
               // No Way QQ
               break;

            case 3:
               return;

            default:
               cout << "Input Error!\n";
               break;
         }
      }
   }else{
      cout << "\nSorry, unrecognized email or password.\n\n";
      login(memberDetails, numMembers);
   }
}

// returns true if there is a member
// whose email and password are equal to the specified email and password, respectively
bool legal( char email[], char password[], Member memberDetails[], int numMembers, int &recordNumber ){
   for( int i = 0 ; i < numMembers ; ++i ){
      if( !strcmp( memberDetails[i].email, email ) && !strcmp( memberDetails[i].password, password ) ){
         recordNumber = i;
         return true;
      }
   }

   return false;
}

void accountInfor( Member memberDetails[], int numMembers, int recordNumber ){
   Member tmp;

   cout << "1. Name: " << memberDetails[recordNumber].name << "\n";
   cout << "2. Email Address: " << memberDetails[recordNumber].email << "\n";
   cout << "3. Phone Number: " << memberDetails[recordNumber].phone << "\n";
   cout << "4. ID Number: " << memberDetails[recordNumber].IDNumber << "\n";
   cout << "5. Password: " << memberDetails[recordNumber].password << "\n\n";

   cout << "Which one do you want to modify (0 - not modify)? ";

   int choice;
   while( true ){
      choice = inputAnInteger( 0, 5 );
      cout << "\n";

      switch( choice ){
         case 0:
            return;

         case 1:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].name;

            cout << "\nSuccessful!\n";
            return;

         case 2:
            cout << "Enter correct data: ";
            
            cin >> tmp.email;
            if( existingEmail(tmp.email, memberDetails, numMembers) ){
               cout << "\nAn account already exists with the ID number!\n\n";
               return;
            }

            strcpy(memberDetails[recordNumber].email, tmp.email);

            cout << "\nSuccessful!\n";
            return;

         case 3:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].phone;

            cout << "\nSuccessful!\n";
            return;

         case 4:
            cout << "Enter correct data: ";

            cin >> tmp.IDNumber;
            if( existingID(tmp.IDNumber, memberDetails, numMembers) ){
               cout << "\nAn account already exists with the ID number!\n\n";
               return;
            }
            
            strcpy(memberDetails[recordNumber].IDNumber, tmp.IDNumber);

            cout << "\nSuccessful!\n";
            return;

         case 5:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].password;

            cout << "\nSuccessful!\n";
            return;

         default:
            cout << "Input Error! Please Try again: ";
            break;
      }
   }
}

void newMember( Member memberDetails[], int &numMembers ){
   Member tmp;

   cout << "Enter your ID number: ";
   cin >> tmp.IDNumber;

   if( existingID(tmp.IDNumber, memberDetails, numMembers) ){
      cout << "\nAn account already exists with the ID number!\n\n";
      return;
   }

   cout << "Enter your name: ";
   cin >> tmp.name;

   cout << "Enter an email address: ";
   cin >> tmp.email;

   if( existingEmail(tmp.email, memberDetails, numMembers) ){
      cout << "\nAn account already exists with the ID number!\n\n";
      return;
   }

   cout << "Enter a password: ";
   cin >> tmp.password;

   cout << "Enter your phone number: ";
   cin >> tmp.phone;

   cout << "\nSuccessful!\n\n";

   memberDetails[numMembers] = tmp;
   numMembers++;
}

// returns true if there is a member whose IDNumber is equal to newIDNumber
bool existingID( char newIDNumber[], Member memberDetails[], int &numMembers ){
   for( int i = 0 ; i < numMembers ; ++i ){
      if( strcmp(newIDNumber, memberDetails[i].IDNumber) == 0 ) return true;
   }

   return false;
}

// returns true if there is a member whose email is equal to newEmail
bool existingEmail( char newEmail[], Member memberDetails[], int &numMembers ){
   for( int i = 0 ; i < numMembers ; ++i ){
      if( strcmp(newEmail, memberDetails[i].email) == 0 ) return true;
   }

   return false;
}

void saveMemberInfo( ofstream &outMemberFile, Member memberDetails[], int numMembers ){
   // for( int i = 0 ; i < numMembers ; ++i ){
   //    cout << memberDetails[i].email << " " << memberDetails[i].IDNumber << " "
   //         << memberDetails[i].name << " " << memberDetails[i].password << " "
   //         << memberDetails[i].phone << "\n";
   // }

   // cout << "-----\n";

   outMemberFile.open( "MemberInfo.dat", ios::out | ios::binary );

   for( int i = 0 ; i < numMembers ; ++i ){
      outMemberFile.write( reinterpret_cast< const char * >(&memberDetails[i]), sizeof(Member) );
   }

   return;
}