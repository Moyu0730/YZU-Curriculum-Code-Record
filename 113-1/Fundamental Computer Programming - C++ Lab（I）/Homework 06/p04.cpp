#include<bits/stdc++.h>
using namespace std;

string str;
map<char, int> mp;

int main(){
    cin >> str;

    for( auto i : str ){
        mp[i]++;
    }

    for( auto it = mp.begin() ; it != mp.end() ; it++ ) cout << it->first << ":" << it->second << " ";
    cout << "\n";
}