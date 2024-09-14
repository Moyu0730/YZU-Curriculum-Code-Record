#include<iostream>
#include<cmath>
using namespace std;

double a, b, c, p, s;

int main(){
    cin >> a >> b >> c;
    p = a + b + c;
    s = p / 2;

    cout << "Perimeter : " << p << "\n";
    cout << "Area : " << sqrt( s * (s - a) * (s - b) * (s - c) ) << "\n";
}