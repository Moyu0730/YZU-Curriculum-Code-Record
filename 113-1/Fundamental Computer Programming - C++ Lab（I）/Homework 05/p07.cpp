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
const int MAXN = 1e8 + 50;
const int Mod = 1e9 + 7;
const int INF = 1e9;

int n, arr[MAXN];

bool isPrime( int val ){
    if( val == 1 ) return false;

    for( int i = 2 ; i * i <= val ; i++ ){
        if( val % i == 0 ) return false;
    }

    return true;
}

signed main(){
    cout << "Please Input N : ";
    cin >> n;

    for( int i = 0 ; i < n ; i++ ) cin >> arr[i];

    cout << "Odd Numbers : ";
    for( int i = 0 ; i < n ; i++ ){
        if( arr[i] % 2 ) cout << arr[i] << " ";
    }
    cout << "\n";

    cout << "Even Numbers : ";
    for( int i = 0 ; i < n ; i++ ){
        if( arr[i] % 2 == 0 ) cout << arr[i] << " ";
    }
    cout << "\n";

    cout << "Prime Numbers : ";
    for( int i = 0 ; i < n ; i++ ){
        if( isPrime(arr[i]) ) cout << arr[i] << " ";
    }
    cout << "\n";

    cout << "Non-Prime Numbers : ";
    for( int i = 0 ; i < n ; i++ ){
        if( !isPrime(arr[i]) ) cout << arr[i] << " ";
    }
    cout << "\n";
}