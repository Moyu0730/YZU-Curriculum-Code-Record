#include<bits/stdc++.h>
using namespace std;

struct profile {
    char fullname[40];
    double score;
    char grade[10];
} student[10000000];

int n;

int main(){
    cout << "Please Input Student Amount : ";
    cin >> n;

    cin.ignore(100, '\n');
    for( int i = 0 ; i < n ; ++i ){
        cout << "Input Student's Fullname : ";
        cin.getline(student[i].fullname, 25);

        cout << "Input Student's Score : ";
        cin >> student[i].score;
        cin.ignore( 100, '\n' );

        if( student[i].score >= 9.0 ) strcpy(student[i].grade, "A");
        else if( student[i].score >= 8.0 ) strcpy(student[i].grade, "B+");
        else if( student[i].score >= 7.0 ) strcpy(student[i].grade, "B");
        else if( student[i].score >= 6.0 ) strcpy(student[i].grade, "C+");
        else if( student[i].score >= 5.0 ) strcpy(student[i].grade, "C");
        else if( student[i].score >= 4.5 ) strcpy(student[i].grade, "D+");
        else if( student[i].score >= 4.0 ) strcpy(student[i].grade, "D");
        else strcpy(student[i].grade, "F");
    }

    cout << "\nFULL NAME \tSCORE \tGRADE\n";
    for( int i = 0 ; i < n ; i++ ) cout << student[i].fullname << " \t" << student[i].score << " \t" << student[i].grade << '\n';
}