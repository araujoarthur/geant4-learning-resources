#include <iostream>
// Write a program that asks user to enter his or her age and return the age in months.
using namespace std;

int main(void)
{
    int userAge;
    cout << "Input your age: ";
    cin >> userAge;
    cout << endl << "Your age in months is " << 12 * userAge << endl;
}