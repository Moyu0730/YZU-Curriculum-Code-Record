#include <iostream>
using namespace std; 

const int MAXN = 10;

int main(){
  int n;
  cin >> n;
  
  int idx = 0, arr[MAXN];
  while( n != 0 ){
    arr[idx] = n % 10;
    n /= 10;
  	idx++;
  }
  
  
  if( arr[0] == arr[4] && arr[1] == arr[3] ) cout << "palindrome\n";
  else cout << "non-palindrome\n";
}