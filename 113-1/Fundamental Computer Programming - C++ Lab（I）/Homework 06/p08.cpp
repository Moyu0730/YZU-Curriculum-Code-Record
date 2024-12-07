#include <iostream>
#include <string>
using namespace std;

string ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
string teens[] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
string tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
string thousands[] = {"", "thousand", "million", "billion"};

int main() {
    int amount;
    cin >> amount;

    if( amount == 0 ) cout << "zero TWD";
    else{
         string result = "";
        int place = 0;

        while( amount > 0 ){
            int chunk = amount % 1000;
            if( chunk > 0 ){
                string chunkWords = "";
                
                if( chunk / 100 > 0 ){
                    chunkWords += ones[chunk / 100] + " hundred";
                    chunk %= 100;
                    if (chunk > 0) chunkWords += " and ";
                }

                if( chunk >= 10 && chunk < 20 ) chunkWords += teens[chunk - 10];
                else{
                    if( chunk / 10 > 0 ){
                        chunkWords += tens[chunk / 10];
                        chunk %= 10;
                        if (chunk > 0) chunkWords += " ";
                    }

                    if(chunk > 0) chunkWords += ones[chunk];
                }

                if( place > 0 && !chunkWords.empty() ) chunkWords += " " + thousands[place];

                if( !result.empty() && !chunkWords.empty() )  result = chunkWords + " " + result;
                else result = chunkWords + result;
            }

            amount /= 1000;
            place++;
        }

        cout << result << " TWD";
    }
}
