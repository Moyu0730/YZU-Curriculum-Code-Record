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

int num, sum;

int getSumofDigits( int val ){
    if( val == 0 ) return 0;
    else return val % 10 + getSumofDigits(val / 10);
}

signed main(){
    opt;

    cin >> num;

    sum = getSumofDigits(num);

    cout << "Sum of the digits is " << sum << ", so " << sum << " is ";
    
    if( sum % 3 ) cout << "not ";
    
    cout << "divisible by 3\n";
}