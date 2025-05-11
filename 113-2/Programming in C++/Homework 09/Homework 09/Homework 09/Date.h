// Date.h
// Date class definition.
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef DATA_H
#define DATA_H

class Date
{
public:
   Date();
   void setYear( int );
   void setMonth( int );
   void setDay( int );
   int getYear() const;
   int getMonth() const;
   int getDay() const;
   bool operator==( const Date &date2 );
   bool operator<( const Date &date2 );
   bool operator<=( const Date &date2 );
   bool operator>=( const Date &date2 );
   int operator-( const Date &date2 );
   friend ostream& operator<<(ostream& output, const Date& date2);
private:
	int year;
	int month;
   int day;
};

inline ostream& operator<<(ostream& output, const Date& date2){
    output << "Year : "    << setw(4) << setfill('0') << date2.year
           << ", Month : " << setw(2) << setfill('0') << date2.month
           << ", Day : "   << setw(2) << setfill('0') << date2.day;

    return output;
}

#endif // DATA_H