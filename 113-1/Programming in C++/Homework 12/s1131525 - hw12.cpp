#include <cstring>
#include <iostream>
#include <fstream>
#include <ostream>

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

void loadMovieNames( char movieNames[][ 40 ], int &numMovies ){
   fstream inFile;
   
   inFile.open( "Movie Names.txt", ios::in | ios::out );

   if( !inFile ){
      cout << "File could not be opened" << "\n";
      system( "pause" );
      exit( 1 );
   }
   
   numMovies = 0;
   while ( inFile.getline(movieNames[numMovies], 120) ) numMovies++;

   inFile.close();
}

void loadMovies(Movie movies[], int &numRecords) {
   fstream inFile;

   inFile.open("Session Times.dat", ios::in | ios::out | ios::binary);

   if (!inFile) {
      cout << "File could not be opened" << "\n";
      system("pause");
      exit(1);
   }

   numRecords = 0;
   while (inFile.read(reinterpret_cast<char *>(&movies[numRecords]), sizeof(Movie))) {
      numRecords++;
   }

   inFile.close();
}

void buyTickets( char movieNames[][ 40 ], Movie movies[], int numMovies, int numRecords ){
   
   for(int i = 0; i < numMovies; ++i){
      cout << i<< ". " << movieNames[i] << "\n";
   }
   int movie_code, date_code, time_code;
   int counter = 0, f = 0;
   cout << "\n";
   
   while(true){
     cout << "Enter movie code (0 - 10):";
     movie_code = inputAnInteger(0, 10);

     cout << "\n";
     if (movie_code == -1)
       continue;

     bool flag = false;
     for (int i = 0; i < numRecords; ++i) {
       if (movies[i].movieCode > movie_code)
         break;

       if (movies[i].movieCode == movie_code) { 
         if (flag == false) {
           f = i;
           flag = true;
         }
         cout << counter++ << ". " << movies[i].dates << "\n";
       }
      } break;
   }

   while(true){
      
      cout << "Enter date code (0 - "<< counter-1 << "):";
      date_code = inputAnInteger(0, counter-1);
      
      cout << "\n";
      if (date_code == -1) continue;

      counter = 0; 
      for(int j = 0; j < movies[f + date_code].numSessions; ++j){
         cout << counter++ << ". " << movies[f + date_code].sessionTimes[j] << "\n";
      } break;
   }

   while(true){
      
      cout << "Enter session time code (0 - "<< counter-1 << "):";
      time_code = inputAnInteger(0, counter-1);
      
      cout << "\n";
      if (time_code == -1) continue;

      counter = 0; 
      for(int j = 0; j < movies[f + date_code].numSessions; ++j){
         cout << counter++ << ". " << movies[f + date_code].sessionTimes[j] << "\n";
      } break;
   }   
      cout << "\n" << movieNames[movie_code] << "\n";
      cout << movies[date_code].dates << " " << movies[f + date_code].sessionTimes[time_code] << "\n";
}

int inputAnInteger( int begin, int end ){
   char str[80];
   cin.getline(str, 80, '\n');

   if (strlen(str) == 0) {
      exit(0);
   }

   for (int i = 0; i < strlen(str); ++i){
      if( str[i] < '0' || str[i] > '9' ){
         return -1;
      }
   }
   
   int number = atoi( str);

   if( number >= begin && number <= end) return number;
   else return -1;
}