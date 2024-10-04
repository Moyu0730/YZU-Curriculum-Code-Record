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

double a, b, c, d, e, avg;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    cout << "Please enter 5 scores: ";
    cin >> a >> b >> c >> d >> e;

    avg = (a + b + c + d + e) / 5;

    cout << "You got the final score of " << fixed << setprecision(1) << avg << ".";

    cout << " Your letter grade is ";
    if( avg >= 9.0 ) cout << "A\n";
    else if( avg >= 8.0 ) cout << "B+\n";
    else if( avg >= 7.0 ) cout << "B\n";
    else if( avg >= 6.0 ) cout << "C    +\n";
    else if( avg >= 5.0 ) cout << "C\n";
    else if( avg >= 4.5 ) cout << "D+\n";
    else if( avg >= 4.0 ) cout << "D\n";
    else cout << "F\n";
}