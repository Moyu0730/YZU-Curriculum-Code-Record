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

    int num;
    cin >> num ;
    cout << "The prime numbers: ";
    for(int i = 2 ; i <= num ; i++ ){
        int detect = 0;

        for( int j = 2 ; j < i ; j++ ){
            if( i % j == 0 ){
                detect = 1;
                break;
            }
        }

        if( detect == 0 ) cout << i << " ";
    }
}