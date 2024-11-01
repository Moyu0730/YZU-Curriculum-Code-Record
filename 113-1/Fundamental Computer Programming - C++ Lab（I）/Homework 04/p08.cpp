#include<iostream>
#include<iomanip>
using namespace std;

int n;
bool flag = false;

int find( int cnt, int val ){
    if( val % cnt == 0 ){
        if( !flag ){
            cout << cnt;
            flag = true;
        }else{
            cout << " * " << cnt;
        }
        
        val = find(cnt, val / cnt);
    }
    
    return val;
}

void solve( int cnt, int val ){
    if( val == 1 ) return;
    if( cnt == val && val == n ){
        cout << cnt << "\n";
        return;
    }
    
    val = find(cnt, val);
    
    solve(cnt+1, val);
}

int main() {
    cin >> n;

    solve(2, n);
    return 0;
}