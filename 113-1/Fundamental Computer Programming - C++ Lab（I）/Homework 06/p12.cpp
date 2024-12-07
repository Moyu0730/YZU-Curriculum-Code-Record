#include<bits/stdc++.h>
using namespace std;

int q;
string name[10000000], a, b;

int main(){
    cout << "Input N : ";
    cin >> q;

    for( int i = 0 ; i < q ; ++i ){
        cin >> a >> b;

        a[0] = toupper(a[0]);
        b[0] = toupper(b[0]);
        
        for( int i = 0 ; i < b.size() ; ++i ){
            if( b[i] == '-' ){
                b[i+1] = toupper(b[i+1]);
                break;
            }
        }

        name[i] = a + " " + b;
    }

    sort(name, name + q, greater<string>());

    for( int i = 0 ; i < q ; ++i ) cout << name[i] << "\n";
}