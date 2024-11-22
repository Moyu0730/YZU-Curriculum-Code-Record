#include<iostream>
#include<iomanip>
using namespace std;

const int MAXN = 1e8 + 50;

int len_a, len_b, a[MAXN], b[MAXN];

int main() {
    cout << "Please Input Number of Array A : ";
    cin >> len_a;

    for( int i = 0 ; i < len_a ; i++ ) cin >> a[i];

    cout << "Please Input Number of Array B : ";
    cin >> len_b;

    for( int i = 0 ; i < len_b ; i++ ) cin >> b[i];

    int idx_a = 0, idx_b = 0;
    for( int i = 0 ; i < len_a + len_b ; i++ ){
        if( idx_a == len_a ){
            cout << b[idx_b] << " ";
            idx_b++;
            continue;
        }

        if( idx_b == len_b ){
            cout << a[idx_a] << " ";
            idx_a++;
            continue;
        }

        if( a[idx_a] < b[idx_b] ){
            cout << a[idx_a] << " ";
            idx_a++;
        }else{
            cout << b[idx_b] << " ";
            idx_b++;
        }
    }

    cout << "\n";
}