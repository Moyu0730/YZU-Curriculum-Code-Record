// MakeReservation.cpp
// Member-function definitions for class MakeReservation.
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include "MakeReservation.h" // MakeReservation class definition

extern bool leapYear( int year );
extern Date computeCurrentDate();
extern int inputAnInteger(int begin, int end);

MakeReservation::MakeReservation( ReservationDatabase &theReservationDatabase,
                                  AvailRoomDatabase &theAvailableRoomsDatabase )
   : reservationDatabase( theReservationDatabase ),
     availableRoomDatabase( theAvailableRoomsDatabase )
{
}

void MakeReservation::execute()
{
   Date currentDate = computeCurrentDate();

   Date availableMonths[ 7 ];

   computeAvailableMonths( currentDate, availableMonths );

   int checkInYMCode;
   int firstDay;
   int lastDay;

   Date checkInDate;
   Date checkOutDate;

   inputCheckInDates( checkInDate, currentDate, availableMonths, checkInYMCode, firstDay, lastDay );
   inputCheckOutDates( checkOutDate, checkInDate, availableMonths, checkInYMCode, firstDay, lastDay );

   cout << "\nCheck in date: " << checkInDate.getYear() << '-'
        << setw( 2 ) << setfill( '0' ) << checkInDate.getMonth() << '-'
        << setw( 2 ) << checkInDate.getDay() << endl;

   cout << "Check out date: " << checkOutDate.getYear() << '-'
        << setw( 2 ) << checkOutDate.getMonth() << '-'
        << setw( 2 ) << checkOutDate.getDay() << endl;

   int minRoomsArray[] = { 0, 0, 0, 0, 0, 0, -1 };
   bool hasRooms = false;
   for (int i = 1; i <= 5; ++i) {
       //cout << availableRoomDatabase.compMinNumRooms(i, checkInDate, checkOutDate) << "\n";
       if (availableRoomDatabase.compMinNumRooms(i, checkInDate, checkOutDate) != 0) {
           hasRooms = true;
       }

       minRoomsArray[i] = availableRoomDatabase.compMinNumRooms(i, checkInDate, checkOutDate);
   }

   if ( !hasRooms ) {
       cout << "\nThere are no rooms available!\n";
       return;
   }

   availableRoomDatabase.displayAvailableRooms( checkInDate, checkOutDate );

   const char roomTypeName[ 6 ][ 20 ] = { "", "Superior Room", "Deluxe Room", "Deluxe Twin Room",
                                              "Superior Suite", "Deluxe Suite" };

   int roomType = 0;
   do {
       cout << "\nSelect Room Type¡G\n";
       for (int i = 1; i <= 5; ++i) {
           if (minRoomsArray[i] != 0) {
               cout << i << ". " << roomTypeName[i] << "\n";
           }
       }
       cout << "6. Give up\n? ";
   } while ( (roomType = inputAnInteger(1, 6) ) == -1 || minRoomsArray[roomType] == 0 );

   if (roomType == 6) return;

   int numRooms;
   do {
       cout << "\nNumber of rooms ( " << minRoomsArray[roomType] << " rooms available ): ";
   } while ((numRooms = inputAnInteger(1, minRoomsArray[roomType])) == -1);

   availableRoomDatabase.decreaseAvailRooms( roomType, numRooms, checkInDate, checkOutDate );

   cout << "\nID Number: ";
   string idNumber;
   cin >> idNumber;

   cout << "\nName: ";
   string name;
   cin >> name;

   cout << "\nMobile Phone: ";
   string mobile;
   cin >> mobile;
   cin.ignore();

   newReservation.setReservation( roomType, numRooms, checkInDate, checkOutDate, idNumber, name, mobile );

   cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";
   newReservation.displayReservation();

   reservationDatabase.pushBack( newReservation );

   cout << "\nReservation successfully!" << endl;
}

void MakeReservation::computeAvailableMonths( Date currentDate, Date availableMonths[] )
{
    for (int i = 1; i <= 6; ++i) {
        availableMonths[i].setMonth( ( currentDate.getMonth() + i - 1 ) % 12);

        if (currentDate.getMonth() + i > 12)  availableMonths[i].setYear( currentDate.getYear() + 1);
        else  availableMonths[i].setYear( currentDate.getYear() );
    }
}

void MakeReservation::inputCheckInDates( Date &checkInDate, Date currentDate,
     Date availableMonths[], int &checkInYMCode, int &firstDay, int &lastDay )
{
    int daysPerMonth[20] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int choice;
    do {
        cout << "\nPlease Input Check In Date\n\n";
        cout << "Month¡G\n";
        for (int i = 1; i <= 6; ++i) {
            cout << i << ". " << availableMonths[i].getYear() << "-"
                << setw(2) << setfill('0') << availableMonths[i].getMonth() << "\n";
        }
        cout << "? ";
    } while ((choice = inputAnInteger(1, 6)) == -1);

    checkInDate.setYear(availableMonths[choice].getYear());
    checkInDate.setMonth(availableMonths[choice].getMonth());

    int start = choice == 1 ? currentDate.getDay() : 1;
    int end = choice == 6 ? daysPerMonth[checkInDate.getMonth()] - 1: daysPerMonth[checkInDate.getMonth()];
    int day;
    do cout << "\nDay (" << start << " ~ " << end << "): ";
    while ((day = inputAnInteger(start, end)) == -1);

    checkInDate.setDay(day);
}

void MakeReservation::inputCheckOutDates( Date &checkOutDate, Date checkInDate,
     Date availableMonths[], int checkInYMCode, int firstDay, int lastDay )
{
    int daysPerMonth[20] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    cout << "\nPlease Input Check Out Date\n\n";
    cout << "Month¡G\n";

    for (int i = 1; i <= 6; ++i) {
        if (availableMonths[i].getMonth() >= checkInDate.getMonth()) {
            cout << i << ". " << availableMonths[i].getYear() << "-"
                << setw(2) << setfill('0') << availableMonths[i].getMonth() << "\n";
        }
    }
    cout << "? ";

    int choice;
    while ((choice = inputAnInteger(1, 6)) == -1 || availableMonths[choice].getMonth() < checkInDate.getMonth()) {
        cout << "? ";
    }

    cout << "\n";

    checkOutDate.setYear(availableMonths[choice].getYear());
    checkOutDate.setMonth(availableMonths[choice].getMonth());

    int start = checkOutDate.getMonth() == checkInDate.getMonth() ? checkInDate.getDay() + 1 : 1;
    int end = daysPerMonth[checkOutDate.getMonth()];
    int day;
    do cout << "Day (" << start << " ~ " << end << "): ";
    while ((day = inputAnInteger(start, end)) == -1);

    checkOutDate.setDay(day);
}