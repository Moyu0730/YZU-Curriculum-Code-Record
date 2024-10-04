#include<iostream>
#include<ctime>
#include<iomanip>
using namespace std;

int date, month, year;

int main(){
    cin >> date >> month >> year;
    cout << setfill('0') << setw(2) << date << "/" << setw(2) << month << "/" << setw(2) << year % 100 << "\n";
}