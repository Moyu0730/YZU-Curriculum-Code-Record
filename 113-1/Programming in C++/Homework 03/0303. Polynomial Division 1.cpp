#include <iostream>
using namespace std;

const int arraySize = 105;

void division(int A[], int B[], int Q[], int R[], int A_Len, int B_Len, int &Q_Len, int &R_Len) {
    for (int i = 0; i <= A_Len; i++) R[i] = A[i];
    Q_Len = A_Len - B_Len;
    R_Len = A_Len;

    for (int i = A_Len; i >= B_Len; i--) {
        Q[i - B_Len] = R[i] / B[B_Len];
        for (int j = B_Len; j >= 0; j--) {
            R[i - (B_Len - j)] -= Q[i - B_Len] * B[j];
        }
    }

    while (R_Len >= 0 && R[R_Len] == 0) R_Len--;

    return;
}

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int A_Len, B_Len, Q_Len, R_Len, A[arraySize], B[arraySize], Q[arraySize], R[arraySize];

        cin >> A_Len;
        for (int i = A_Len; i >= 0; i--) cin >> A[i];

        cin >> B_Len;
        for (int i = B_Len; i >= 0; i--) cin >> B[i];

        division(A, B, Q, R, A_Len, B_Len, Q_Len, R_Len);

        cout << Q_Len;
        for (int i = Q_Len; i >= 0; i--) cout << " " << Q[i];
        cout << "\n";

        if( R_Len >= 0 ){
           cout << R_Len;
           for (int i = R_Len; i >= 0; i--) cout << " " << R[i];
           cout << "\n";
        }else cout << "0 0\n";
    }
}
