#include<bits/stdc++.h>
using namespace std;

string str, res = "";

int main(){
    getline(cin, str);

    int count = 0;
    for( int i = 0 ; i < str.size() ; ++i ){
        if( str[i] == '"' || str[i] == '"' ){
            res.push_back(str[i]);
            continue;
        }

        if( str[i] == ' ' ){
            if( count != 0 && count != 3 ) res.push_back(str[i]);
            continue;
        }

        if( str[i+1] == ' ' ) ++count;
        res.push_back(str[i]);
    }

    for( int i = 0 ; i < res.size() ; i++ ) cout << (char)tolower(res[i]);
    cout << "\n";
    for( int i = 0 ; i < res.size() ; i++ ) cout << (char)toupper(res[i]);
}