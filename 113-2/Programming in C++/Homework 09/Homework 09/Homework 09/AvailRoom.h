// AvailRoom.h
// AvailRoom class definition. Represents the number of available rooms of each type for one day.
#ifndef AVAIL_ROOM_H
#define AVAIL_ROOM_H

#include <iostream>
using namespace std;

#include "Date.h" // Date class definition

class AvailRoom
{
public:
   AvailRoom();
   void setDate( int year, int month, int day );
   Date getDate();
   void initAvailRooms();
   int getAvailRoom( int i ); // return availRooms[ i ]
   void decreaseAvailRooms( int roomType, int numRooms ); // availRooms[ roomType ] -= numRooms

   friend ostream& operator<<(ostream& output, const AvailRoom& data);
private:
   Date date;
   int availRooms[ 6 ] = {}; // number of available rooms for each room type
}; // end class AvailRoom

inline ostream& operator<<(ostream& output, const AvailRoom& data) {
    output << data.date << " | ";

    for (int i = 0; i < 6; ++i) {
        output << data.availRooms[i] << " ";
    }

    return output;
}

#endif // AVAIL_ROOM_H