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

double n, tmp, sum, MAX, MIN, MAX_SUB, MIN_SUB;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    cout << "Input the number of the subjects is : "; cin >> n;

    MAX = -1, MIN = INF;
    for( int i = 1 ; i <= n ; i++ ){
        cout << "Input the score of subject " << i << " is : ";
        cin >> tmp;

        if( tmp > MAX ){
            MAX = tmp;
            MAX_SUB = i;
        }

        if( tmp < MIN ){
            MIN = tmp;
            MIN_SUB = i;
        }

        sum += tmp;
    }

    cout << "The average score of the student is : " << sum / n << "\n";
    cout << "The highest score of the student is : " << MAX << ". And the subject is : " << MAX_SUB << "\n";
    cout << "The lowest score of the student is : " << MIN << ". And the subject is : " << MIN_SUB << "\n";
}