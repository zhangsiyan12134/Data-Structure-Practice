/*  File: testleastsquares.cpp
    test the least squares function for the matrix class */

#include "matrix.h"

int main(void)
{
    ifstream fin("testleastsquaresin.txt");

    matrix a(3,2), b(3,1), x;

    fin >> a >> b;

    cout << "a = " << endl;
    cout << a << endl << endl;
    cout << "b = " << endl;
    cout << b << endl << endl;

    x = leastsquares(a,b);

    cout << "x = " << endl;
    cout << x << endl << endl;

    cout << "check a * x should be as close to b as possible" << endl;
    cout << a * x << endl << endl;

    return 0;
}


