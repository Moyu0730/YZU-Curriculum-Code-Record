// AvailRoomDatabase.cpp
// Member-function definitions for class AvailRoomDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
#include "AvailRoomDatabase.h" // AvailRoomDatabase class definition

extern bool leapYear( int year );
extern Date computeCurrentDate();
//char availFileName[] = "Available Rooms 2024-11-6.dat";
//char availFileName[] = "Available Rooms 2025-2-4.dat";
char availFileName[] = "Available Rooms 2025-5-5.dat";
//char availFileName[] = "Available Rooms blank.dat";

AvailRoomDatabase::AvailRoomDatabase()
{
   loadAvailableRooms();

   if( availRooms.size() == 0 )
      initAvailRooms(); // create available rooms information for 6 months
   else
      appendAvailRooms(); // append new available rooms information
}

AvailRoomDatabase::~AvailRoomDatabase()
{
   saveAvailableRooms();
}

void AvailRoomDatabase::loadAvailableRooms()
{
    ifstream inFile;
    inFile.open(availFileName, ios::in | ios::binary);

    if (!inFile) {
        cerr << "File could not be opened." << endl;
        system("pause");
        exit(1);
    }

    Date today = computeCurrentDate();
    AvailRoom buffer;

    while (inFile.read(reinterpret_cast<char*>(&buffer), sizeof(AvailRoom))) {
        if (buffer.getDate() >= today) {
            availRooms.push_back(buffer);
        }
    }

    return;
}

void AvailRoomDatabase::initAvailRooms()
{
    Date today = computeCurrentDate();
    int daysPerMonth[20] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if ( leapYear( today.getYear() ) ) daysPerMonth[2] = 29;

    for (int month = today.getMonth(); month < today.getMonth() + 6; ++month) {
        int year = today.getYear();
        if (month > 12) {
            ++year;
            month %= 12;
        }

        for (int i = 1; i <= daysPerMonth[month]; ++i) {
            AvailRoom buffer;

            buffer.setDate(year, month, i);
            buffer.initAvailRooms();

            availRooms.push_back(buffer);
        }
    }
}

void AvailRoomDatabase::appendAvailRooms()
{
    Date today = computeCurrentDate();
    int daysPerMonth[20] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (leapYear(today.getYear())) daysPerMonth[2] = 29;

    for (int month = availRooms.back().getDate().getMonth(); month < today.getMonth() + 6; ++month){
        int year = today.getYear();
        if (month > 12) {
            ++year;
            month %= 12;
        }

        for (int i = 1; i <= daysPerMonth[month]; ++i) {
            AvailRoom buffer;

            buffer.setDate(year, month, i);
            buffer.initAvailRooms();

            availRooms.push_back(buffer);
        }
    }
}

void AvailRoomDatabase::displayAvailableRooms( Date checkInDate, Date checkOutDate )
{
   cout << "\nThe number of available rooms of each room type:\n\n";
   cout << "      Date   Superior Room   Deluxe Room   Deluxe Twin Room   Superior Suite   Deluxe Suite\n";

   vector< AvailRoom >::iterator checkInIterator;
   vector< AvailRoom >::iterator checkOutIterator;

   findIterators( checkInDate, checkOutDate, checkInIterator, checkOutIterator );

   for( vector< AvailRoom >::iterator it = checkInIterator; it < checkOutIterator; ++it )
      cout << it->getDate().getYear() << "-"
           << setw( 2 ) << setfill( '0' ) << it->getDate().getMonth() << "-"
           << setw( 2 ) << it->getDate().getDay()
           << setw( 16 ) << setfill( ' ' ) << it->getAvailRoom( 1 )
           << setw( 14 ) << it->getAvailRoom( 2 )
           << setw( 19 ) << it->getAvailRoom( 3 )
           << setw( 17 ) << it->getAvailRoom( 4 )
           << setw( 15 ) << it->getAvailRoom( 5 ) << "\n";
}

int AvailRoomDatabase::compMinNumRooms( int roomType,
                       const Date &checkInDate, const Date &checkOutDate )
{
    int idx = 0;

    while ( !(availRooms[idx].getDate() == checkInDate) ) ++idx;

    int res = availRooms[idx].getAvailRoom(roomType);
    for (; !(availRooms[idx].getDate() == checkOutDate); ++idx ){
        res = min(res, availRooms[idx].getAvailRoom(roomType));
    }
    
    return res;
}

void AvailRoomDatabase::decreaseAvailRooms( int roomType, int numRooms,
                        const Date &checkInDate, const Date &checkOutDate )
{
    vector< AvailRoom >::iterator checkInIterator;
    vector< AvailRoom >::iterator checkOutIterator;

    findIterators(checkInDate, checkOutDate, checkInIterator, checkOutIterator);

    for (vector< AvailRoom >::iterator it = checkInIterator; it < checkOutIterator; ++it) {
        //cout << "Amount From " << (*it).getAvailRoom(roomType) << " into ";
        (*it).decreaseAvailRooms(roomType, numRooms);
        //cout << (*it).getAvailRoom(roomType) << "\n";
    }

    saveAvailableRooms();

    return;
}

void AvailRoomDatabase::saveAvailableRooms(){
    ofstream outFile;
    outFile.open(availFileName, ios::out | ios::binary);

    for (int i = 0; i < availRooms.size(); ++i) {
        outFile.write(reinterpret_cast<const char*>(&availRooms[i]), sizeof(AvailRoom));
    }

    return;
}

void AvailRoomDatabase::findIterators( const Date &checkInDate, const Date &checkOutDate,
                                       vector< AvailRoom >::iterator &checkInIterator,
                                       vector< AvailRoom >::iterator &checkOutIterator )
{
    vector< AvailRoom >::iterator it = availRooms.begin();

    for (; !((*it).getDate() == checkOutDate); ++it) {
        if ((*it).getDate() == checkInDate) checkInIterator = it;
    }

    checkOutIterator = it;

    return;
}