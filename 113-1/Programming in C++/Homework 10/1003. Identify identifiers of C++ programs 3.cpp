#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the vector program
void load( vector< char * > &program );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char *sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( char *sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( char *sourceLine );

// extracts all identifiers from sourceLine, and
// put them into the vector identifiers
void extractIdentifiers( char *sourceLine, vector< char * > &identifiers );

// stores all non-keyword strings in the vector identifiers into a text file
void store( vector< char * > &identifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true iff identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< char * > &identifiers, int pos );

const char keywords[][ 20 ] = { "auto", "break", "case", "char", "const",
                                "continue", "default", "define","do", "double",
                                "else", "enum", "extern", "float", "for",
                                "goto", "if", "int", "long", "register",
                                "return", "short", "signed", "sizeof",
                                "static", "struct", "switch", "typedef",
                                "union", "unsigned", "void", "volatile",
                                "while", "bool", "catch", "class",
                                "const_cast", "delete", "dynamic_cast",
                                "explicit", "false", "friend", "inline",
                                "mutable", "namespace", "new", "operator",
                                "private", "protected", "public",
                                "reinterpret_cast", "static_cast", "template",
                                "this", "throw", "true", "try", "typeid",
                                "typename", "using", "virtual", "include" };

int main(){
    vector< char * > program;

    // reads in a C++ program from a cpp file, and put it to the vector program
    load( program );

    vector< char * > identifiers;
    for( size_t i = 0; i < program.size(); i++ )
    {
        delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
        delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

        if( strlen(program[ i ]) != 0 )
            extractIdentifiers( program[ i ], identifiers );
            // extracts all identifiers from program[ i ], and put them into the vector identifiers
    }

    // for( auto i : identifiers ) cout << i << "\n";

    // stores all non-keyword strings in the vector identifiers into a text file
    store( identifiers );

    for( size_t i = 0; i < identifiers.size(); i++ )
        delete[] identifiers[ i ];

    for( size_t i = 0; i < program.size(); i++ )
        delete[] program[ i ];
}

void load( vector< char * > &program ){
    char filename[100];
    cin >> filename;
    ifstream inFile(filename, ios::in );

    if( !inFile ){
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    char temp[500];
    while (inFile.getline(temp, 500, '\n')) {
        char* line = new char[strlen(temp) + 1];
        strcpy(line, temp);
        program.push_back(line);
    }

    return;
}

void delComment( char *sourceLine )
{
   size_t length = strlen( sourceLine );
   if( length > 1 )
      for( size_t i = 0; i < length - 1; i++ )
         if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' )
         {
            sourceLine[ i ] = '\0';
            return;
         }
}

void delStrConsts( char *sourceLine ){
    size_t len = strlen(sourceLine);

    if( len <= 0 ) return;

    int st = -1, ed = -1;
    char cnt;
    for( size_t i = 0 ; i < len ; ++i ){

        if( st == -1 && ( sourceLine[i] == '"' || sourceLine[i] == '\'' ) ){
            st = i;
            cnt = sourceLine[i];
            continue;
        }

        if( st != -1 && ( sourceLine[i] == cnt && sourceLine[i-1] != '\\' )  ){
            ed = i;
            for( int j = 0 ; j < len - 1 ; ++j ){
                if( ed + 1 + j >= len ) break;

                sourceLine[st+j] = sourceLine[ed+1+j];
            }

            i = st;
            len -= ed - st + 1;
            st = -1;
            sourceLine[len] = '\0';
        }
    }
}

void delCharConsts( char *sourceLine ){
    size_t len = strlen(sourceLine);

    if( len <= 0 ) return;

    for( size_t i = 0 ; i < len ; ++i ){
        if( !(sourceLine[i] >= 'A' && sourceLine[i] <= 'Z') && !(sourceLine[i] >= 'a' && sourceLine[i] <= 'z') 
            && sourceLine[i] != ' ' && !(sourceLine[i] >= '0' && sourceLine[i] <= '9') && sourceLine[i] != '_' ){
            sourceLine[i] = ' ';
        }

        if( (sourceLine[i] >= '0' && sourceLine[i] <= '9') && sourceLine[i-1] == ' ' ){
            sourceLine[i] = ' ';
        }
    }

    sourceLine[len] = '\0';

    for( size_t i = 0 ; i < len ; ++i ){
        if( sourceLine[i] == ' ' ) continue;

        for( size_t j = 0 ; j < len - i ; ++j ) sourceLine[j] = sourceLine[j+i];

        len -= i;
        sourceLine[len] = '\0';
        break;
    }

    for( size_t i = 0 ; i < len ; ++i ){
        if( sourceLine[i] == ' ' && sourceLine[i+1] == ' ' ){
            for( size_t j = i+1 ; j < len ; ++j ) sourceLine[j] = sourceLine[j+1];
            len--;
            i--;
        }
    }

    for( size_t i = strlen(sourceLine) - 1 ; i >= 0 ; --i ){
        if( sourceLine[i] == ' ' ){
            sourceLine[i] = '\0';
            len--;
            continue;
        }

        break;
    }
}

void extractIdentifiers( char *sourceLine, vector< char * > &identifiers ){
    size_t len = strlen(sourceLine);
    
    char identifier[32], ind = 0;
    for( size_t i = 0 ; i <= len ; ++i ){
        if( sourceLine[i] == ' ' || i == len ){
            if( ind == 0 ) continue;

            identifier[ind] = '\0';
            ind = 0;

            if( keyword(identifier) ) continue;

            char* tempIdentifier = new char[strlen(identifier) + 1];
            strcpy(tempIdentifier, identifier);
            identifiers.push_back(tempIdentifier);

            if (duplicate(identifiers, identifiers.size() - 1)) {
                delete[] identifiers.back();
                identifiers.pop_back();
            }

            continue;
        }

        identifier[ind] = sourceLine[i];
        ind++;
    }

    return;
}

void store( vector< char * > &identifiers ){
    ofstream outFile( "identifiers.txt", ios::out );
    
    if( !outFile ){
        cout << "File could not be opened\n";
        system( "pause" );
        exit( 1 );
    }

    for( auto i : identifiers ) outFile << i << "\n";
}

bool keyword( char str[] )
{
   size_t numKeywords = sizeof( keywords ) / 20;
   for( size_t i = 0; i < numKeywords; i++ )
      if( strcmp( keywords[ i ], str ) == 0 )
         return true;

   return false;
}

bool duplicate( vector< char * > &identifiers, int pos )
{
   for( int i = 0; i < pos; i++ )
      if( strcmp( identifiers[ i ], identifiers[ pos ] ) == 0 )
         return true;

   return false;
}