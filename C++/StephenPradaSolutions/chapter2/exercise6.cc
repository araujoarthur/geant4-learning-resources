#include <iostream>

// Write a program that has main() call a user defined function that takes a distance in lightyears and returns it in astronomical units.
float ly_to_au(float ly);

int main(void)
{
    using namespace std; // Just as example that it could be used inside function only too.
    float lyears;
    cout << "Input a distance in Light Years: ";
    cin >> lyears;
    cout << endl << "The distance in Astronomical Units (AU) is: " << ly_to_au(lyears) << endl;
}

float ly_to_au(float ly)
{
    return ly * 63241.1;
}