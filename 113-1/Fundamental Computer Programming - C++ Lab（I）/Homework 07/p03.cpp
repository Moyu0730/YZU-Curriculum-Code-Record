#include<bits/stdc++.h>
using namespace std;

struct employee{
    char firstname[20], lastname[10];
    string address;
    int age;
    double salary;
};

int main(){
    int num;
    cout << "Please in put n: ";
    cin >> num;
    employee man[num];
    for( int i = 0 ; i < num ; i++ ){
        cout << "Input employee #" << i+1 << ":" << endl;
        cout << "First name: ";
        cin >> man[i].firstname;
        cout << "Last name: ";
        cin >> man[i].lastname;
        cout << "Age: ";
        cin >> man[i].age;
        cin.ignore( 30, '\n' );
        cout << "Address: ";
        getline( cin, man[i].address );
        cout << "Salary: ";
        cin >> man[i].salary;
    }
    cout << "\n" << left
         << setw(15) << "FULL NAME"
         << setw(5) << "Age"
         << setw(25) << "Address"
         << setw(10) << "Salary" << '\n';
    for( int i = 0 ; i < num ; i++ ){
        string fullname = string(man[i].lastname) + " " + string(man[i].firstname);
        cout << left
             << setw(15) << fullname
             << setw(5) << man[i].age
             << setw(25) << man[i].address
             << setw(10) << man[i].salary
             << '\n';
    }
}
