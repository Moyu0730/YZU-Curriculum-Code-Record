// Date.cpp
// Member-function definitions for class Date.
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;
#include "Date.h"

extern bool leapYear( int year );

Date::Date()
{
   year = 2000;
   month = 0;
   day = 0;
}

void Date::setYear( int y )
{
   year = ( y >= 2000 ) ? y : 2000; // sets year
}

void Date::setMonth( int m )
{
   month = ( m <= 12 && m >= 1 ) ? m : 1; // sets month
}

void Date::setDay( int d )
{
   int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
   if( month == 2 && leapYear( year ) )
      day = ( d <= 29 && d >= 1 ) ? d : 1;
   else
      day = ( d <= days[ month ] && d >= 1 ) ? d : 1;
}

int Date::getYear() const
{
   return year;
}

int Date::getMonth() const
{
   return month;
}

int Date::getDay() const
{
   return day;
}

bool Date::operator==( const Date &date2 )
{
   return ( year == date2.year && month == date2.month && day == date2.day );
}

bool Date::operator<( const Date &date2 )
{
   if( year < date2.year )
      return true;
   if( year > date2.year )
      return false;

   if( month < date2.month )
      return true;
   if( month > date2.month )
      return false;

   if( day < date2.day )
      return true;

   return false;
}

bool Date::operator<=( const Date &date2 )
{
   return ( *this < date2 ) || ( *this == date2 );
}

bool Date::operator>=( const Date &date2 )
{
   return !( *this < date2 );
}

int toDays( int y, int m, int d ){
    int totalDays = 0;
    int daysPerMonth[20] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (int i = 0; i < y; ++i) {
        if (leapYear(i)) totalDays += 366;
        else totalDays += 365;
    }

    for (int i = 1; i < m; ++i) {
        if (i == 2 && leapYear(y)) totalDays += 29;
        else totalDays += daysPerMonth[i];
    }

    totalDays += d;

    return totalDays;
}

// return *this - date2 provided that *this > date2
int Date::operator-( const Date &date2 ){
    int days1 = toDays(year, month, day);
    int days2 = toDays(date2.year, date2.month, date2.day);

    return days1 - days2;
}