/*  File: complexstd.cpp
Use the standard complex class */
#include <iostream>
#include <fstream>
#include <complex>
using namespace std;
int main(void)
{
	complex<float>  a, b, c;
	cout << "Enter two  complex numbers in the form (re, im): ";
	cin >> a >> b;
	c = a + b;
	cout << "The sum of " << a << " and " << b << " is " << c << endl;
	c = a - b;
	cout << "The difference of " << a << " and " << b << " is " << c << endl;
	c = a * b;
	cout << "The product of " << a << " and " << b << " is " << c << endl;
	c = a / b;
	cout << "The division of " << a << " and " << b << " is " << c << endl;
	return 0;
}
