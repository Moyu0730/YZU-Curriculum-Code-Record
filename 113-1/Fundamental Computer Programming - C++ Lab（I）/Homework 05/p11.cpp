/* Question : OJ Number */

#include<bits/stdc++.h>
using namespace std;

#define opt ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define mem(x, value) memset(x, value, sizeof(x));
#define pii pair<int, int>
#define pdd pair<double, double>
#define pb push_back
#define F first
#define S second
#define X first
#define Y second
#define int long long

const auto dir = vector< pair<int, int> > { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
const int MAXN = 1e4 + 50;
const int Mod = 1e9 + 7;
const int INF = 1e9;

int k, n, val, a[MAXN], b[MAXN][MAXN], res[MAXN];

signed main(){
    cout << "Please Input K and N : ";
    cin >> k >> n;

    cout << "Please Input Matrix A : \n";
    for( int i = 0 ; i < k ; i++ ) cin >> a[i];

    cout << "\nComfirm Your Matrix A : \n";
    for( int i = 0 ; i < k ; i++ ) cout << a[i] << " ";

    cout << "\n";    

    cout << "\nPlease Input Matrix B : \n";
    for( int i = 0 ; i < k ; i++ ){
        for( int j = 0 ; j < n ; j++ ) cin >> b[i][j];
    }

    cout << "\nComfirm Your Matrix B : \n";
    for( int i = 0 ; i < k ; i++ ){
        for( int j = 0 ; j < n ; j++ ) cout << b[i][j] << " ";
        cout << "\n";
    }

    cout << "\n";

    cout << "Here is Matrix C : \n";
     for( int i = 0 ; i < n ; i++ ){
        for( int j = 0 ; j < k ; j++ ) res[i] += a[j] * b[j][i];

        cout << res[i] << " ";
    }
    cout << "\n";
}