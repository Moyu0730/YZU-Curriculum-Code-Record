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

    cin >> a;
    double S0[a] = {}, S1_sum = 0, S2_sum = 0;
    S0[0] = 1;
    for( int i = 1 ; i <= a ; i++ ){
        S0[i] = S0[i-1] * i;
        S1_sum = (double) 1 / i + S1_sum;
        S2_sum = (double) 1 / S0[i] + S2_sum;
    }

    cout << "S0 = " << S0[a] << "\n";
    cout << "S1 = " << S1_sum << "\n";
    cout << "S2 = " << S2_sum << "\n";
}