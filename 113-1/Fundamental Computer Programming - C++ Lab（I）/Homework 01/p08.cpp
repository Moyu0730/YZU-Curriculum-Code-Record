#include<iostream>
#include<iomanip>
using namespace std;

double avg, a, b, c, d, e;
string name;

signed main(){
    #ifdef LOCAL
        opt;
    #endif

    getline(cin, name);
    cin >> a >> b >> c >> d >> e;

    avg = ( a + b + c + d + e ) / 5;

    cout << "Hi " + name + ", you got " << fixed << setprecision(1) << avg  << " as final score\n";
}