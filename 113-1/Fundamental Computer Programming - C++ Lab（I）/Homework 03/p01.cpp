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

int getS3( int n ){
    int res = 0;

    int sgn;
    for( int i = 1 ; i <= n ; i++ ){
        sgn = i % 2 ? -1 : 1;
        res += sgn * i;
    }

    return res;
}

double getS2( int n ){
    double res = 0.0;

    for( double i = 1 ; i <= n ; i++ ) res += i / (i+1);
    
    return res;
}

int getS1( int n ){
    int res = 0;

    for( int i = 1 ; i <= n ; i++ ) res += i;
    
    return res;
}

int n;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    cout << "Input N : ";
    cin >> n;

    cout << "Sum Type 01 : " << getS1(n) << "\n";
    cout << "Sum Type 02 : " << fixed << setprecision(3) << getS2(n) << "\n";
    cout << "Sum Type 03 : " << getS3(n) << "\n";
}