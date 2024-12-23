#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

struct Movie
{
   int movieCode;
   char dates[ 12 ] = "";
   int numSessions;
   char sessionTimes[ 3 ][ 8 ] = { "" };
};

void loadMovieNames( char movieNames[][ 40 ], int &numMovies );
void loadMovies( Movie movies[], int &numRecords );
void buyTickets( char movieNames[][ 40 ], Movie movies[], int numMovies, int numRecords );
int inputAnInteger( int begin, int end );

int main()
{
   char movieNames[ 12 ][ 40 ];
   int numMovies = 0;
   loadMovieNames( movieNames, numMovies );

   Movie movies[ 60 ];
   int numRecords = 0;
   loadMovies( movies, numRecords );

   buyTickets( movieNames, movies, numMovies, numRecords );

   system( "pause" );
}

void loadMovieNames( char movieNames[][ 40 ], int &numMovies )
{





}

void loadMovies( Movie movies[], int &numRecords )
{





}

void buyTickets( char movieNames[][ 40 ], Movie movies[], int numMovies, int numRecords )
{





}

int inputAnInteger( int begin, int end )
{





}