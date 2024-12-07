#include<bits/stdc++.h>
using namespace std;

string str;

int main(){
    cin >> str;

    for( int i = 0 ; i < str.size() / 2  ; i++ ){
        if( str[i] != str[str.size()-1-i] ){
            cout << "The s~equence " << str << " is not a symmetric string.\n";
            exit(false);
        }
    }

    cout << "The sequence " << str << " is a symmetric string.\n";
}