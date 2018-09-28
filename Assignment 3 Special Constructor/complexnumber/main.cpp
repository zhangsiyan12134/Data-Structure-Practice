/*  File: complexnumbers.cpp
Implement complex numbers as a class using operators */
#include <iostream>
#include <fstream>
using namespace std;
class complex {
	private:
		float x; // real part
		float y; // imaginary part
	public:
		complex(float re = 0.0, float im = 0.0);
		float real(void) const; // return real part
		float imag(void) const; // return imag part
		void real(float re);    // set real part
		void imag(float im);    // set imag part
};
////////////////////// prototypes of complex operators //////////////////////
istream& operator>>(istream &in, complex &x);
ostream& operator<<(ostream &out, complex &x);
complex operator+(complex &x, complex &y);
complex operator-(complex &x, complex &y);
complex operator*(complex &x, complex &y);
complex operator/(complex &x, complex &y);

int main(void)
{
	complex a, b, c;
	cout << "Enter two complex numbers in the form (re, im): ";
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
///////////////////////// implementation of complex ////////////////////
complex::complex(float re, float im)
{
	x = re;
	y = im;
}

float complex::real(void) const
{
	return x;
}

float complex::imag(void) const
{
	return y;
}

void complex::real(float re)
{
	x = re;
}

void complex::imag(float im)
{
	y = im;
}
//////////////////////// implementation of complex operators /////////////
istream& operator>>(istream &in, complex &x)
{
	char blank;
	float r,i;
	in >> blank >> r >> blank >> i >> blank;
	x.real(r);
	x.imag(i);
	return in;
}
ostream& operator<<(ostream &out, complex &x)
{
	out << '(' << x.real() << ", " << x.imag() <<')';
	return out;
}
complex operator+(complex &x, complex &y)
{
	complex temp(x.real()+y.real(),x.imag()+y.imag());
	return temp;
}
complex operator-(complex &x, complex &y)
{
	complex temp(x.real()-y.real(),x.imag()-y.imag());
	return temp;
}
complex operator*(complex &x, complex &y)
{
	complex temp(x.real()*y.real()-x.imag()*y.imag(),x.real()*y.imag()+x.imag()*y.real());
	return temp;
}
complex operator/(complex &x, complex &y)
{
	float real, imag;
	real = (x.real()*y.real()+x.imag()*y.imag())/(y.real()*y.real()+y.imag()*y.imag());
	imag = (x.imag()*y.real()-x.real()*y.imag())/(y.real()*y.real()+y.imag()*y.imag());
	complex temp(real,imag);
	return temp;
}
