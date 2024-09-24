#include <iostream>
using namespace std;

int main()
{
   int t, val, res;
   
    cin >> t;
    for( int i = 0 ; i < t ; i++ ){
      cin >> val;
      
      res = 0;
      while( val > 0 ){
        res += val % 10;
      	val /= 10;
      }
      
      cout << res << "\n";
    }
}