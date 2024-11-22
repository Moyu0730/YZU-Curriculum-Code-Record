#include<iostream>
#include<iomanip>
using namespace std;

const int MAXN = 1e8 + 50;

int n, arr[MAXN];

int main() {
    cout << "Please Input N : ";
    cin >> n;

    for( int i = 0 ; i < n ; i++ ) cin >> arr[i];
    for( int i = 0 ; i < n/2 ; i++ ) swap(arr[i], arr[n-i-1]);

    for( int i = 0 ; i < n ; i++ ) cout << arr[i] << " ";
    cout << "\n";
}