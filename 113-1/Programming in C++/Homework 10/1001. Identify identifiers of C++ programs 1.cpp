#include <iostream>
#include <cstring>
#include <fstream>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( char( *program )[ 300 ], int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( char sourceLine[] );

// deletes all string constants from sourceLine
void delStrConsts( char sourceLine[] );

// deletes all character constants from sourceLine
void delCharConsts( char sourceLine[] );

// extracts all identifiers from sourceLine, and put them into the array identifiers
void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( char ( *identifiers )[ 32 ], int numIdentifiers );

// returns true if and only if str is a C++ keyword
bool keyword( char str[] );

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( char ( *identifiers )[ 32 ], int pos );

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
    char ( *program )[ 300 ] = new char[ 500 ][ 300 ];
    int numLines = 0;

    // reads in a C++ program from a cpp file, and put it to the array program
    load( program, numLines );

    char ( *identifiers )[ 32 ] = new char[ 500 ][ 32 ];
    int numIdentifiers = 0;

    for( int i = 0; i < numLines; i++ ){
        delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
        delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

        // cout << "Program : " << program[i] << "\n";

        if( strcmp( program[ i ], "" ) != 0 )
            extractIdentifiers( program[ i ], identifiers, numIdentifiers );
            // extracts all identifiers from program[ i ], and put them into the array identifiers

        // cout << "Idenfiers :\n";
        // for( size_t i = 0 ; i < numIdentifiers ; ++i ) cout << " " << identifiers[i] << "\n";
        // cout << "\n----------\n";
    }

    // for( size_t i = 0 ; i < numIdentifiers ; ++i ) cout << identifiers[i] << "\n";

    // stores all non-keyword strings in the array identifiers into a text file
    store( identifiers, numIdentifiers );

    // cout << numLines << "\n";
    // for( int i = 0 ; i < numLines ; ++i ) cout << program[i] << "\n";

    delete[] program;
    delete[] identifiers;
}

void load( char( *program )[ 300 ], int &numLines ){
    char filename[100];
    cin >> filename;
    ifstream inFile(filename, ios::in );

    if( !inFile ){
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    int ind = 0;
    while( inFile.getline(program[ind], 500, '\n') ) ind++;

    numLines = ind + 1;

    return;
}

void delComment( char sourceLine[] ){
    size_t length = strlen( sourceLine );
    if( length > 1 ){
        for( size_t i = 0; i < length - 1; i++ ){
            if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' ){
                sourceLine[ i ] = '\0';
                return;
            }
        }
    }
}

void delStrConsts( char sourceLine[] ){
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

void delCharConsts( char sourceLine[] ){
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

void extractIdentifiers( char sourceLine[], char identifiers[][ 32 ], int &numIdentifiers ){
    size_t len = strlen(sourceLine);
    
    char identifier[32], ind = 0;
    // cout << "Enter : ";
    for( size_t i = 0 ; i <= len ; ++i ){
        if( sourceLine[i] == ' ' || i == len ){
            identifier[ind] = '\0';
            ind = 0;

            if( keyword(identifier) ) continue;

            strcpy(identifiers[numIdentifiers], identifier);
            numIdentifiers++;

            if( duplicate(identifiers, numIdentifiers-1) ) numIdentifiers--;
            continue;
        }

        identifier[ind] = sourceLine[i];
        ind++;
    }

    return;
}

void store( char ( *identifiers )[ 32 ], int numIdentifiers ){
    ofstream outFile( "identifiers.txt", ios::out );
    
    if( !outFile ){
        cout << "File could not be opened\n";
        system( "pause" );
        exit( 1 );
    }

    for( size_t i = 0 ; i < numIdentifiers ; ++i ) outFile << identifiers[i] << "\n";
}

bool keyword( char str[] )
{
   size_t numKeywords = sizeof( keywords ) / 20;
   for( size_t i = 0; i < numKeywords; i++ )
      if( strcmp( keywords[ i ], str ) == 0 )
         return true;

   return false;
}

bool duplicate( char ( *identifiers )[ 32 ], int pos ){
    for( int i = 0; i < pos; i++ )
        if( strcmp( identifiers[ i ], identifiers[ pos ] ) == 0 )
            return true;

   return false;
}