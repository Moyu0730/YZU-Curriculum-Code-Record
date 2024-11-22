#include<iostream>
#include<iomanip>
using namespace std;

const int MAXN = 1e8 + 50;

int n, sum, arr[MAXN];

int main() {
    cout << "Please Input N : ";
    cin >> n;

    for( int i = 0 ; i < n ; i++ ){
        cin >> arr[i];

        if( arr[i] < 0 ) sum += arr[i] * arr[i];
    }

    cout << "The sum of squares of negative numbers : " << sum << " ";
}