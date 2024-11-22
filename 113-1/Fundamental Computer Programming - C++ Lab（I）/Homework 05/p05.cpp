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
const int MAXN = 1e4 + 50;
const int Mod = 1e9 + 7;
const int INF = 1e9;

int m, n, val, arr[MAXN][MAXN];
int res[MAXN][2], len;

signed main(){
    cout << "Please Input M and N : ";
    cin >> m >> n;

    for( int i = 0 ; i < n ; i++ ){
        for( int j = 0 ; j < m ; j++ ) cin >> arr[i][j];
    }

    for( int i = 0 ; i < n ; i++ ){
        for( int j = 0 ; j < m ; j++ ) cout << arr[i][j] << " ";
        cout << "\n";
    }

    cout << "Input Integer : ";
    cin >> val;

    for( int i = 0 ; i < n ; i++ ){
        for( int j = 0 ; j < m ; j++ ){
            if( arr[i][j] == val ){
                res[len][0] = i;
                res[len++][1] = j;
            }
        }
    }

    cout << "The value of " << val << " appeared " << len << " time(s). Locate at ";
    for( int i = 0 ; i < len ; i++ ) cout << "[" << res[i][0] << "," << res[i][1] << "]" << " ,"[i==len-1];
    
    cout << "\n";
}