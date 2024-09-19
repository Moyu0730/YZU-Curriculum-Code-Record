#include <iostream>
using namespace::std;

long long q, val, sum;

int main()
{
  cin >> q;
  for( int i = 0 ; i < q ; i++ ){
    cin >> val;
    
    sum = 0;
    for( int j = 1 ; j < val ; j++ ){
      if( val % j == 0 ){
        sum += j;
      }
    }
    
    if( sum == val ) cout << "perfect number\n";
  	else cout << "non-perfect number\n";
  }
}