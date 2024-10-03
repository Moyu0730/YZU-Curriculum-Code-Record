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

float price[6] = { 1.63, 2.38, 3.52, 4.80, 5.66, 6.99 };
int level[6] = { 120, 210, 170, 200, 300, 1000 };
float a, b, sum, elecprice;

signed main(){
    #ifdef LOCAL
        opt;
    #endif
    
    cout << "Input old indicator: "; cin >> a;
    cout << "Input new indicator: "; cin >> b;

    sum = b - a;

    cout << "Amount of kWh was used: " << sum << ",";

    for( int i = 0 ; i < 6 ; i++ ){
        if( sum - level[i] >= 0 ){
            sum -= level[i];
            elecprice += level[i] * price[i];
        }
        else elecprice += sum * price[i];
    }

    cout << " subtotal: " << elecprice << " TWD" << "\n";
}