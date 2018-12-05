/*  File: testpseudoinverse.cpp
    test the pseudoinversefunction for the matrix class */

#include "matrix.h"

int main(void)
{
    ifstream fin("testpseudoinversein.txt");

    matrix a(3,2), x;

    fin >> a;

    cout << "a = " << endl;
    cout << a << endl << endl;

    x = pseudoinverse(a);

    cout << "x = " << endl;
    cout << x << endl << endl;

    cout << "check x * a should be the identity matrix" << endl;
    cout << x * a << endl << endl;

    return 0;
}
