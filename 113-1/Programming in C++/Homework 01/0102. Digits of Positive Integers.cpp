#include <iostream>
using namespace std;

const int MAXN = 10;

int main(){
  int n, arr[MAXN];
  cin >> n;
  
  int idx = 0;
  while( n != 0 ){
    arr[idx] = n % 10;
    n /= 10;
  	idx++;
  }
  
  for( int i = idx - 1 ; i >= 0 ; i-- ){
  	cout << arr[i] << " \n"[i==0];
  }
}