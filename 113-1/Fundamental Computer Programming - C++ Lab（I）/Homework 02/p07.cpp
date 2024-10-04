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

            // 1   2   3   4   5   6   7   8   9   10  11  12
int leap[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int common[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int month, year;

bool isLeap( int year ){
    if( ( year % 4 == 0 && year % 100 != 0 ) || year % 400 == 0 ) return true;
    else return false;
}

signed main(){
    #ifdef LOCAL
        opt;
    #endif
}