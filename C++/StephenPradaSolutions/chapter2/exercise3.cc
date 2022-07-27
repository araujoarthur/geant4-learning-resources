#include <iostream>
using namespace std;

// Write a program that uses three user defined functions (counting main()) and produce the given output.
void tbm(void);
void srtr(void);

int main(void)
{
    tbm();
    tbm();
    srtr();
    srtr();
}

void tbm(void)
{
   cout << "Three blind mice" << endl;
}

void srtr(void)
{
    cout << "See how they run" << endl;
}

