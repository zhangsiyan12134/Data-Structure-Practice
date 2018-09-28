/* File: time24big3.cpp
the class time24 represents time on 24 hour clock
times are written to a stream in the form hour:minute
the big 3 methods are implemented
Programmer: your name Date: */
#include <iostream>
#include <fstream>
using namespace std;

class time24 {
	private:
		int hour_; // hour between 0 and 23
		int minute_; // minute between 0 and 59
	public:
		time24(int h = 0 , int m = 0); // constructor with default args
		/* put big 3 prototypes here */
		~time24(void);
		time24& operator=(const time24 &rhs);
		time24(const time24 &source);
		void write(ostream& out) const; // prints hour:minute to out
};

int main (void) // test the class
{
	time24 x(18, 34);
	time24 y(x);
	time24 z;
	time24* p;
	p = new time24(5,8);
	cout << "The time x is: ";
	x.write(cout);
	cout << "The time y is: ";
	y.write(cout);
	cout << "The time z is: ";
	z.write(cout);
	cout << "The time *p is: ";
	p->write(cout);
	z = x = *p;
	cout << "The time z is: ";
	z.write(cout);
	x = x; // nothing should be printed
	delete p;
	return 0;
}
//////////////////// Implementation of time24 ///////////////////////////
time24::time24(int h, int m)
{
	hour_ = h;
	minute_ = m;
	cout << "constructing: ";
	write(cout);
}
/* put big 3 implementations here */
time24::~time24(void)
{
	cout << "destroying: ";
	write(cout);
}
time24& time24::operator=(const time24 &rhs)
{
	if(this != &rhs)
	{
		hour_ = rhs.hour_;
		minute_ = rhs.hour_;
		cout << "Assigning: ";
		write(cout);
	}
	return *this;
}
time24::time24(const time24 &source)
{
	hour_ = source.hour_;
	minute_ = source.minute_;
	cout << "Copying: ";
	write(cout);
}
void time24::write(ostream& out) const
{
	out << hour_ /10 << hour_ % 10 << ":" << minute_ / 10 << minute_ %10;
	out << " stored at address " << this << endl;
}
