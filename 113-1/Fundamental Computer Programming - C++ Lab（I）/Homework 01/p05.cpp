#include<iostream>
using namespace std;

int date, month, year, cnt;

int main(){
    cin >> date >> month >> year >> cnt;
    cout << "Your age is " << cnt - year << "\n";
}