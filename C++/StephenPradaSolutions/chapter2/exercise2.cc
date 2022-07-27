#include <iostream>

// Write a program that asks for a distance in furlongs and converts it to yards (1 furlong = 220 yards)

using namespace std;

int main(void)
{
    float furlong;
    cout << "Input a distance in furlong: " << endl;
    cin >> furlong;
    cout << furlong * 220 << " yards" << endl;
}