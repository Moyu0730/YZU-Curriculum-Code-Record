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

int ksm( int base, int power ){
    int res = 1;
    while( power > 0 ){
        if( power & 1 ) res *= base;
        
        power >>= 1;
        base *= base;
    }

    return res;
}

int base, power;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    cout << "Input the Base : "; cin >> base;
    cout << "Input the Power : "; cin >> power;
    cout << "The Result of " << base << " to the power of " << power << " is " << ksm(base, power) << "\n";
}