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

int n, tmp, len, arr[MAXN];

signed main(){
    cout << "Please Input N : ";
    cin >> n;

    int last, cnt = 1;
    while( len < n ){
        cout << "Input Element #" << cnt << " : ";
        cin >> tmp;

        if( len == 0 ){
            last = tmp;
            arr[len++] = tmp;
            cnt++;
            continue;
        }else{
            if( tmp <= last ) cout << "Incorrect value! Please Enter Again\n";
            else{
                last = tmp;
                arr[len++] = tmp;
                cnt++;
            }
        }
    }

    sort(arr, arr + len);

    cout << "Array : ";
    for( int i = 0 ; i < len ; i++ ) cout << arr[i] << " ";
    cout << "\n";

    cout << "Pleast Input X : ";
    cin >> arr[len];

    sort(arr, arr + len + 1);

    cout << "Array After Inserting : ";
    for( int i = 0 ; i <= len ; i++ ) cout << arr[i] << " ";
    cout << "\n";
}