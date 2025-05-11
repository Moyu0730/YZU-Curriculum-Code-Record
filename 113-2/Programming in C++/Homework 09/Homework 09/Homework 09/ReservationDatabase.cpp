// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;
#include "ReservationDatabase.h" // ReservationDatabase class definition

extern Date computeCurrentDate();

ReservationDatabase::ReservationDatabase()
{
	loadReservations();
}

ReservationDatabase::~ReservationDatabase()
{
	saveToReservationFile();
}

void ReservationDatabase::loadReservations()
{
    ifstream inFile;
    inFile.open("Reservations.dat", ios::in | ios::binary);

    if (!inFile) {
        cerr << "File could not be opened." << endl;
        system("pause");
        exit(1);
    }

    Reservation buffer;
    while (inFile.read(reinterpret_cast<char*>(&buffer), sizeof(Reservation))) {
        reservations.push_back(buffer);
    }

    return;
}

void ReservationDatabase::pushBack( Reservation newReservation )
{
   reservations.push_back( newReservation );
}

int ReservationDatabase::numReservations( string idNumber )
{
    int res = 0;

    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i].getIDNumber() == idNumber) ++res;
    }

    return res;
}

void ReservationDatabase::displayReservations( string idNumber )
{
	cout << "\n    Name   Fare       Mobile          Room type   Number of rooms   Check in date   Check out date\n";

   for( vector< Reservation >::iterator it = reservations.begin(); it < reservations.end(); it++ )
      if( it->equalID( idNumber, it->getIDNumber() ) )
         it->displayReservation();
}

void ReservationDatabase::saveToReservationFile()
{
    ofstream outFile;
    outFile.open("Reservations.dat", ios::out | ios::binary);

    for (int i = 0; i < reservations.size(); ++i) {
        outFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
    }

    return;
}