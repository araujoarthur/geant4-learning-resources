#include <iostream>

using namespace std;
// Write a program that has main() to call a user defined function that asks user for input a number in Celsius and returns it in Farenheit

float toFarenheit(int celsius);

int main(void)
{   
    float celsius;
    cout << "Input a Celsius Temperature Value: ";
    cin >> celsius;
    cout << endl << "The temperature in Farenheit is: " << toFarenheit(celsius) << endl;
}

float toFarenheit(int celsius)
{
    return celsius * 1.8 + 32;
}