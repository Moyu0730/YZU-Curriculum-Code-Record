#include<bits/stdc++.h>
using namespace std;

string str;

int main(){
    getline(cin, str);

    int count = 0;
    for( int i = 0 ; i < str.size() ; ++i ){
        if( str[i] == '"' || str[i] == '"' ){
            cout << str[i];
            continue;
        }

        if( str[i] == ' ' ){
            if( count != 0 && count != 3 ) cout << str[i];
            continue;
        }

        if( str[i+1] == ' ' ) ++count;
        cout << str[i];
    }
}