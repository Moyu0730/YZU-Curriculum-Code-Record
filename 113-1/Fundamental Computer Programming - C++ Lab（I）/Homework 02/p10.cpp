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
const int MAXN = 3 + 50;
const int Mod = 1e9 + 7;
const int INF = 1e9;

int arr[MAXN], MIN;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    cin >> arr[0] >> arr[1] >> arr[2];

    for( int i = 0 ; i < 3 ; i++ ){
        MIN = INF;

        for( int j = 0 ; j < 3 ; j++ ){
            if( arr[j] < MIN ) MIN = arr[j];
        }

        for( int j = 0 ; j < 3 ; j++ ){
            if( arr[j] == MIN ) arr[j] = INF;
        }

        cout << MIN << " ";
    }

    cout << "\n";
}