#include<bits/stdc++.h>
using namespace std;

struct profile{
    int num, den;
};

int main(){
    profile formula[3];
    string operatorer;
    cout << "Please input fraction A: ";
    cin >> formula[0].num >>  formula[0].den;
    cout << "Please input fraction B: ";
    cin >> formula[1].num >>  formula[1].den;
    cout << "Please input the operator (+,-,*,/): ";
    cin >> operatorer;

    if( operatorer == "+" ){
        if( formula[1].den == formula[0].den ){
            formula[2].den = formula[1].den;
            formula[2].num = formula[0].num + formula[1].num;
        }
        else{
            formula[2].den = formula[0].den * formula[1].den;
            formula[2].num = ( formula[0].num * formula[1].den ) + ( formula[1].num * formula[0].den );
        }
    }else if( operatorer == "-" ){
        if( formula[1].den == formula[0].den ){
            formula[2].den = formula[1].den;
            formula[2].num = formula[0].num - formula[1].num;
        }
        else{
            formula[2].den = formula[0].den * formula[1].den;
            formula[2].num = ( formula[0].num * formula[1].den ) - ( formula[1].num * formula[0].den );
        }
    }
    else if( operatorer == "*" ){
        formula[2].den = formula[0].den * formula[1].den;
        formula[2].num = formula[0].num * formula[1].num;
    }
    else if( operatorer == "/" ){
        formula[2].den = formula[0].den * formula[1].num;
        formula[2].num = formula[0].num * formula[1].den;
    }
    int number = __gcd( formula[2].den, formula[2].num );
    cout << "Result: " << formula[2].num / number << "/" << formula[2].den / number << "\n";
}
