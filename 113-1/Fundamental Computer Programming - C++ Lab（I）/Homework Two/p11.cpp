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

string tenth[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
string tw_num[10] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
string num[10] = {"zero", "one", "two", "three", "four",  "five",  "six",  "seven", "eight", "nine" };
int a;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    cin >> a;
    if( a < 10 ) cout << num[a] << "\n";
    else if( a < 20 && a > 10 ) cout << tenth[a-10] << "\n";
    else if( a % 10 == 0 ) cout << tw_num[a/10] << "\n";
    else cout << tw_num[a/10] << "-" << num[a%10];
}