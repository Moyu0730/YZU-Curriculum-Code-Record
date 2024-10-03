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

int a, b, c, d;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    cin >> a >> b >> c;

    if( a == 0 ){
        if( b == 0 && c == 0 ) cout << "we get infinite solution\n";
        else if( b == 0 && c != 0 ) cout << "we get no solution.\n";
        else cout << "we get ONE solution : x = " <<  ( -1 * c ) / b << "\n";
    }else{
        d = b * b - 4 * a * c;
        if( d < 0 ) cout << "we get complex solutions\n";
        else if( d == 0 ) cout << "we get ONE solution: x = " << ( -1 * b ) / ( 2 * a ) << "\n";
        else cout << "we get TWO solution: x = " << ( ( -1 * b ) + sqrt(d) ) / ( 2 * a ) << " & " << ( ( -1 * b ) - sqrt(d) ) / ( 2 * a ) << "\n";
    }
}