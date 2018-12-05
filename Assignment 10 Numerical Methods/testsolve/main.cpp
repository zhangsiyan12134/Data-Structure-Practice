/*  File: testsolve.cpp
    test the solve function for the matrix class */

/*  File: testsolve.cpp
    test the solve function for the matrix class */

#include "matrix.h"

matrix solve(matrix a, matrix b);

int main(void)
{
    ifstream fin("testsolvein.txt");

    matrix a(2,2), b(2,4), c, x;

    fin >> a >> b;

    cout << "a = " << endl;
    cout << a << endl << endl;
    cout << "b = " << endl;
    cout << b << endl << endl;

    x = solve(a,b);

    cout << "x = " << endl;
    cout << x << endl << endl;

    cout << "check a * x should be b" << endl;
    cout << a * x << endl << endl;

    return 0;
}

