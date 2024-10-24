/* Question : OJ Number */

#include<bits/stdc++.h>
using namespace std;

#define opt ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
#define mem(x, value) memset(x, value, sizeof(x));
#define pii pair<int, int>
#define pdd pair<double, double>
#define pb push_back
#define F first
// #define S second
#define X first
#define Y second
#define int long long

const auto dir = vector< pair<int, int> > { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
const int MAXN = 1e8 + 50;
const int Mod = 1e9 + 7;
const int INF = 1e9;

double S, sum = 0, n = 2;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    
    cout << "Input the number S: ";
    cin >> S;

    while( sum < S ){
        sum += (double) 1 / n;
        cout << (double) 1 / n  << " " << sum << endl;
        n++;
    }

    cout << "The biggest number n that the sum of 1/2 + 1/3 + ... to 1/n is smaller than " << S << " is " << n-2 << "\n";
}