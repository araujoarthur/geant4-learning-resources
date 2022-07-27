#include <iostream>

// Write a program that asks the user to input an hour value and a minute value then prints Hour:Minute
using namespace std;

int main(void)
{
    int hour, minute;
    cout << "Input an hour value: ";
    cin >> hour;
    cout << endl << "Input a minute value: ";
    cin >> minute;
    cout << endl << hour << ":" << minute << endl;
}