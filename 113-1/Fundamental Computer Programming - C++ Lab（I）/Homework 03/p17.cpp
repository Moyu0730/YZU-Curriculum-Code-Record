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

    int sumeven = 0, sumnum = 0;
    double sumodd = 0;
    int num;
    cout << "Input numbers:" << "\n";
    cin >> num;
    do{
        bool flag = false;
        for(int i = 2 ; i < num ; i++ ){
            if( num % i == 0 ){
                flag = true;
                break;
            }
        }
        
        if( num % 2 == 1 ){
            sumodd += num;
            sumnum++;
        } else sumeven += num;

        if( !detect ) break;
    }while( cin >> num );

    cout << "Sum of even numbers is: " << sumeven << "\n";
    cout << "Average of odd numbers is: " << sumodd / sumnum << "\n";
}