#include<bits/stdc++.h>
using namespace std;

int q;
string a, b, c;

int main(){
    cout << "Input N : ";
    cin >> q;

    while( q-- ){
        cin >> a >> b >> c;

        a[0] = toupper(a[0]);
        b[0] = toupper(b[0]);
        c[0] = toupper(c[0]);
        
        cout << a << " " << b << " " << c << "\n";
    }
}