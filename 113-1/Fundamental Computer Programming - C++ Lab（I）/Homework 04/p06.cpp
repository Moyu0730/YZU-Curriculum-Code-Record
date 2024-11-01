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

int x, n;

int factorial( int val ){
    if( val <= 0 ) return 1;
    return val * factorial(val-1);
}

double S1( int x, int n ){
    if( n == 0 ) return 1;
    else return pow(x, n) + S1(x, n-1);
}

int S2( int x, int n ){
    if( n == 0 ) return 1;
    return pow(-1, n) * pow(x, n) + S2(x, n-1);
}

double S3( int x, int n ){
    if( n == 0 ) return 1;
    else return pow(x, n) / factorial(n) + S3(x, n-1);
}

signed main(){
    opt;

    cin >> x >> n;
    cout << "S1 : " << S1(x, n) << "\n";
    cout << "S2 : " << S2(x, n) << "\n";
    cout << "S3 : " << S3(x, n) << "\n";
}