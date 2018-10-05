#include <iostream>
#include <string>
using namespace std;
int main()
{
    //Accept input from user
    int age, boundaries;
    string studentStatus, destination;
    cout << "Age of rider: ";
    cin >> age;
    cin.ignore(10000,'\n'); //Ignores all input till the end of the line
    cout << "Student? (y/n): ";
    getline(cin,studentStatus); //accepts a string input from the user
    cout << "Destination: ";
    getline(cin,destination);
    cout << "Number of zone boundaries crossed: ";
    cin >> boundaries;
    
    cout << "---" << endl;
    double fare; //variable to store the final fare
    
    //Check for specific conditions and calculate the fare accordingly
    if (age >= 65 && boundaries == 0) //Cheapest rate for a senior rider
        fare = 0.45;
    else if ((age < 18 && boundaries <= 1) || (studentStatus=="y" && age >= 18 && boundaries <= 1))
        //if the rider is under 18 or is a student above 18 and crosses at most 1 boundary
        fare = 0.65;
    else if (age >= 65 && boundaries > 0) //fare for a senior rider who is not a student
        fare = 0.55 + (0.25 * boundaries);
    else //standard fare
        fare = 1.35 + (0.55 * boundaries);
    
    cout.setf(ios::fixed);
    cout.precision(2); //set precision of double values to 2 decimal places
    
    //Check for errors and display appropriate message
    if (age < 0)
        cout << "The age must not be negative" << endl;
    else if (studentStatus != "y" && studentStatus != "n") //For any input other than y or n for student status
        cout << "You must enter y or n" << endl;
    else if (destination == "") //If destination is an empty string
        cout << "You must enter a destination" << endl;
    else if (boundaries < 0)
        cout << "The number of zone boundaries crossed must not be negative" << endl;
    else //If there are no errors, just display the fare
        cout << "The fare to " << destination << " is $" << fare << endl;
}
