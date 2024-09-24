// Polynomial addition
#include <iostream>
using namespace std;

// sum = addend + adder provided that
// neither addend nor adder is the zero polynomial
void addition( int A[], int B[], int sum[], int A_len, int B_len, int &S_len ){
    // cout << "\n";
    // for( int i = 0 ; i < A_len ; i++ ) cout << A[i] << " \n"[i==A_len-1];
    // for( int i = 0 ; i < B_len ; i++ ) cout << B[i] << " \n"[i==B_len-1];
    // cout << "\n";

    for( int i = 0 ; i < min(A_len, B_len) ; i++ ){
        sum[i] = A[i] + B[i];
        // cout << i << " " << addend[i] << " " << adder[i] << " " << sum[i] << "\n";
    }

    if( A_len > B_len ){
      for( int i = B_len ; i < A_len ; i++ ) sum[i] = A[i];
    }else if( B_len > A_len ){
      for( int i = A_len ; i < B_len ; i++ ) sum[i] = B[i];
    }

    for( int i = max(B_len, A_len) - 1 ; i >= 0 ; i-- ){
      if( sum[i] != 0 ){
        S_len = i;
        break;
      }		
    }

    // for( int i = 0 ; i < max(A_len, B_len) ; i++ ) cout << sum[i] << " \n"[i==max(A_len, B_len)-1];
    
    return;
}

const int arraySize = 105;

signed main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    for( int t = 0 ; t < T ; t++ ){
        int A_len, A[arraySize];
        cin >> A_len;
        A_len++;
        for( int i = A_len - 1 ; i >= 0 ; i-- ) cin >> A[i];

        int B_len, B[arraySize];
        cin >> B_len;
        B_len++;
        for( int i = B_len - 1 ; i >= 0 ; i-- ) cin >> B[i];

        // cout << "\n-----------\n";

        int S_len = 0, sum[arraySize];
        addition( A, B, sum, A_len, B_len, S_len );
        
        cout << S_len;
        for( int i = S_len ; i >= 0 ; i-- ) cout << " " << sum[i];
        cout << "\n";

        if( S_len != 0 && sum[S_len] == 0 ) cout << "Leading coefficient of sum cannot be zero!\n";

        // cout << "\n-----------\n";
    }
}