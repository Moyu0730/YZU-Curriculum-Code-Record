#include <iostream>
#include <fstream>
#include <string>
using namespace::std;

// reads in a C++ program from a cpp file, and put it to the array program
void load( string *program, int &numLines );

// deletes the comment beginning with "//" from sourceLine if any
void delComment( string &sourceLine );

// deletes all string constants from sourceLine
void delStrConsts( string &sourceLine );

// deletes all character constants from sourceLine
void delCharConsts( string &sourceLine );

// extracts all identifiers from sourceLine, and
// put them into the array identifiers
void extractIdentifiers( string &sourceLine, string *identifiers,
                         int &numIdentifiers );

// stores all non-keyword strings in the array identifiers into a text file
void store( string *identifiers, int numIdentifiers );

// return true if and only if "str" is a C++ keyword
bool keyword( string str );

// returns true iff identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( string *identifiers, int pos );

const string keywords[] = { "auto", "break", "case", "char", "const",
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
    string *program = new string[ 500 ];
    int numLines = 0;

    // reads in a C++ program from a cpp file, and put it to the array program
    load( program, numLines );

    string *identifiers = new string[ 500 ];
    string null;
    int numIdentifiers = 0;

    for( int i = 0; i < numLines; i++ ){
        delComment( program[ i ] ); // deletes the comment beginning with "//" from program[ i ]
        delStrConsts( program[ i ] ); // deletes all string constants from program[ i ]
        delCharConsts( program[ i ] ); // deletes all character constants from program[ i ]

        if( !program[ i ].empty() )
            extractIdentifiers( program[ i ], identifiers, numIdentifiers );
            // extracts all identifiers from program[ i ], and put them into the array identifiers
    }

    // stores all non-keyword strings in the array identifiers into a text file
    store( identifiers, numIdentifiers );

    delete[] program;
    delete[] identifiers;
}

void load( string *program, int &numLines ){
    string filename;
    cin >> filename;
    ifstream inFile( filename, ios::in );

    if( !inFile ){
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    int ind = 0;
    while( getline(inFile, program[ind]) ) ind++;

    numLines = ind + 1;

    return;
}

void delComment( string &sourceLine ){
    size_t length = sourceLine.size();
    if( length > 1 ){
        for( size_t i = 0; i < length - 1; i++ ){
            if( sourceLine[ i ] == '/' && sourceLine[ i + 1 ] == '/' ){
                sourceLine.erase(sourceLine.begin() + i, sourceLine.end());
                return;
            }
        }
    }
}

void delStrConsts( string &sourceLine ){
    size_t len = sourceLine.size();

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
            sourceLine.erase(sourceLine.begin() + len, sourceLine.end());
        }
    }
}

void delCharConsts( string &sourceLine ){
    size_t len = sourceLine.size();
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

    sourceLine.erase(sourceLine.begin() + len, sourceLine.end());

    for( size_t i = 0 ; i < len ; ++i ){
        if( sourceLine[i] == ' ' ) continue;

        for( size_t j = 0 ; j < len - i ; ++j ) sourceLine[j] = sourceLine[j+i];

        len -= i;
        sourceLine.erase(sourceLine.begin() + len, sourceLine.end());
        break;
    }

    for( size_t i = 0 ; i < len ; ++i ){
        if( sourceLine[i] == ' ' && sourceLine[i+1] == ' ' ){
            for( size_t j = i+1 ; j < len ; ++j ) sourceLine[j] = sourceLine[j+1];
            len--;
            i--;
        }
    }

    return;
}

void extractIdentifiers( string &sourceLine, string *identifiers, int &numIdentifiers ){
    size_t len = sourceLine.size();    
    string identifier;

    for( size_t i = 0 ; i < len ; ++i ){
        if( sourceLine[i] == ' ' ){
            if( identifier.empty() ) continue;
            if( keyword(identifier) ){
                identifier.clear();
                continue;
            }

            identifiers[numIdentifiers] = identifier;
            numIdentifiers++;

            if( duplicate(identifiers, numIdentifiers-1) ) numIdentifiers--;

            identifier.clear();
            continue;
        }

        identifier.push_back(sourceLine[i]);
    }

    // cout << "\n";

    return;
}

void store( string *identifiers, int numIdentifiers ){
    ofstream outFile( "identifiers.txt", ios::out );
    
    if( !outFile ){
        cout << "File could not be opened\n";
        system( "pause" );
        exit( 1 );
    }

    for( size_t i = 0 ; i < numIdentifiers ; ++i ) outFile << identifiers[i] << "\n";
}

bool keyword( string str )
{
   const int numKeywords = 62;
   for( int i = 0; i < numKeywords; i++ )
      if( keywords[ i ] == str )
         return true;

   return false;
}

bool duplicate( string *identifiers, int pos )
{
   for( int i = 0; i < pos; i++ )
      if( identifiers[ i ] == identifiers[ pos ] )
         return true;

   return false;
}