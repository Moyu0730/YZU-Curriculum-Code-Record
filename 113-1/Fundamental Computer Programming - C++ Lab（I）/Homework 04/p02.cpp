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

int x, y, gcdres;

int gcd( int a, int b ){
    if( a < b ) swap(a, b);

    if( a % b == 0 )return b;
    else return gcd(b, a%b);
}

signed main(){
    opt;

    cin >> x >> y;

    if( ( gcdres = gcd(x, y) ) == 1 ) cout << "The fraction is already simplified.\n";
    else{
        cout << "The greatest common divisor is " << gcdres << ". The simplified fraction is ";
        cout << x / gcdres << "/" << y / gcdres << "\n";
    }
}