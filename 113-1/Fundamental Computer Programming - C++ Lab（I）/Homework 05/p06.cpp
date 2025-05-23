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

int matrix[MAXN][MAXN];

signed main(){
    for( int i = 0 ; i < 4 ; i++ ){
        for( int j = 0 ; j < 4 ; j++ ) cin >> matrix[i][j];
    }

    for( int i = 1 ; i < 4 ; i++ ){
        for( int j = 0 ; j < i ; j++ ) swap(matrix[i][j], matrix[j][i]);
    }

    cout << "\n";
    for( int i = 0 ; i < 4 ; i++ ){
        for( int j = 0 ; j < 4 ; j++ ) cout << matrix[i][j] << " ";
        cout << "\n";
    }
}