#include<iostream>
#include<ctime>
using namespace std;

int date, month, year;

int main(){
    cin >> date >> month >> year;
    time_t now = time(0);
    tm *ltm = localtime(&now);
    cout <<  "Your age is " << ( 1900 + ltm->tm_year ) - year << "\n";
}