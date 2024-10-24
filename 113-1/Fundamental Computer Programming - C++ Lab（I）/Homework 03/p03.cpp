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

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    int n, a0, a1, a2;

    cout << "Input N ( N > 1 ) : ";
    cin >> n;

    a0 = 1, a1 = 1;

    cout << "The First " << n << "+1 = " << n+1 << " Integer of Fibonacci Series is : " << a0 << " " << a1 << " ";
    for( int i = 2 ; i <= n ; i++ ){
        a2 = a0 + a1;
        a0 = a1;
        a1 = a2;

        cout << a2 << " ";
    }
    cout << "\n";
}