#include <iostream>
#include <cmath>
using namespace std;

// returns true if and only if n has a factor in { 2, 3, ..., end }
bool hasFactor( int n, int end );

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int numCases;
    cin >> numCases;
    for( int i = 1; i <= numCases; i++ ){
        int n;
        cin >> n;

        if( n == 2 || n == 3 ) cout << "prime" << endl;
        else if( hasFactor( n, static_cast< int >( sqrt( n ) ) ) ) cout << "composite" << endl;
        else cout << "prime" << endl;
    }
}

// returns true if and only if n has a factor in { 2, 3, ..., end }
bool hasFactor( int n, int end ){
    if( end == 1 ) return false;
    if( n % end == 0 ) return true;

    return hasFactor(n, end-1);
}