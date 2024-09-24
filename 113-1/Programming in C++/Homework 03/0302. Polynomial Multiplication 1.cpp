// Polynomial multiplication
#include <bits/stdc++.h>
using namespace std;

const int arraySize = 101;

// res = A * B provided that
// neither A nor B is the zero polynomial
void multiplication( int A[], int B[], int res[], int A_Len, int B_Len, int &res_Len ){
    for( int i = 0 ; i < 2*arraySize ; i++ ) res[i] = 0;

    for( int i = 0 ; i <= A_Len ; i++ ){
        for( int j = 0 ; j <= B_Len ; j++ ) res[i+j] += A[i] * B[j];
    }

    int sum = A_Len + B_Len;
    for( int i = sum ; i >= 0 ; i++ ){
        if( res[i] != 0 ){
            res_Len = i;
            break;
        }
    }
    // cout << "\n";

    return;
}

int main(){
    int T;
    cin >> T;
    for( int t = 0; t < T; t++ ){
        int A_Len, A[arraySize];
        cin >> A_Len;
        for( int i = A_Len ; i >= 0 ; i-- ) cin >> A[i];

        int B_Len, B[arraySize];
        cin >> B_Len;
        for( int i = B_Len ; i >= 0 ; i-- ) cin >> B[i];

        int res[2*arraySize];
        int res_Len;
        multiplication( A, B, res, A_Len, B_Len, res_Len );

        cout << res_Len;
        for( int i = res_Len ; i >= 0 ; i-- ) cout << " " << res[i];
        cout << "\n";
    }
}