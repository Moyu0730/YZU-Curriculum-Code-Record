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

int n;

int factorial( int val ){
    if( val <= 0 ) return 1;
    return val * factorial(val-1);
}

int combination( int k, int n ){
    if( int )
    return factorial(n) / ( factorial(k) * factorial(n-k) );
}

signed main(){
    opt;

    cin >> n;

    for( int i = 0 ; i <= n ; i++ ){
        cout << "Line " << i << " : ";
        for( int j = 0 ; j <= i ; j++ ) cout << combination(i, j) << "\t";
        cout << "\n";
    }
}