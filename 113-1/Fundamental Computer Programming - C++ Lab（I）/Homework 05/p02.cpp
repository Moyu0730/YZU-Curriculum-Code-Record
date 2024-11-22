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
const int MAXN = 1e7 + 50;
const int Mod = 1e9 + 7;
const int INF = 1e9;

int n, arr[MAXN];

signed main(){
    cout << "Please Input N : ";
    cin >> n;

    for( int i = 0 ; i < n ; i++ ) cin >> arr[i];

    sort(arr, arr + n);

    int last = arr[0];
    cout << arr[0] << " ";
    for( int i = 0 ; i < n ; i++ ){
        if( arr[i] != last ){
            cout << arr[i] << " ";
            last = arr[i];
        }
    }
    cout << "\n";
}