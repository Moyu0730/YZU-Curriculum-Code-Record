#include <iostream>
using namespace std;

int main(){
  int year;
  cin >> year;

  if( year % 4 == 0 ){
    if( year % 100 == 0 && year % 400 != 0 ){
    	cout << "common year\n";
    }else{
    	cout << "leap year\n";
    }
  }else{
    cout << "common year\n";
  }
}