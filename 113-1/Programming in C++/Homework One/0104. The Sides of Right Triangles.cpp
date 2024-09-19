#include <bits\stdc++.h>
using namespace std; 

const int MAXN = 10;

int sqr( int val ){
	return val * val;
}

int main(){
  int s[MAXN];
  cin >> s[0] >> s[1] >> s[2];
  
  sort(s, s+3);

  if( sqr(s[2]) == sqr(s[0]) + sqr(s[1]) ) cout << "These integers form a right triangle\n";
  else cout << "These integers do not form a right triangle\n";
}