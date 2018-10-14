/*  File: employeetime.cpp
Illustrates composition of classes
Name: Siyan Zhang   Date: 2018-10-05
*/
#include <iostream>
#include <string>

using namespace std;

class time24 {
	private:
		int hour_;                         // hour between 0 and 23
		int minute_;                       // minute between 0 and 59
	public:
		time24(int h, int m);              // constructor
		void write(ostream &out) const;     // prints hour:minute to out
};

class employee {
	private:
		string name;  // last name
		int id;       // employee id number
		float salary; // employee salary
		time24 start; // workday start time
	public:
		employee(string n, int i, float s, const time24 &t);
		employee(string n, int i, float s, int h, int m);
		void write(ostream &out) const;
};

int main(void)
{
	time24 u(8, 0);
	employee x("Jones", 123, 45000.0, u);
	employee y("Smith", 124, 50000.0, 8, 30);
	cout << "x =  "; x.write(cout); cout << endl;
	cout << "y =  "; y.write(cout); cout << endl;
	return 0;
}
//////////////////// Implementation of time24 ///////////////////////////
time24::time24(int h, int m)
{
	hour_ = h;
	minute_ = m;
}
void time24::write(ostream &out) const
{
	out << hour_ /10 << hour_ % 10 << ":" << minute_ / 10 << minute_ %10;
}
////////////////////// implementation of employee /////////////////////
employee::employee(string n, int i, float s, const time24 &t) :start(t)
{
	name = n;
	id = i;
	salary = s;
}
employee::employee(string n, int i, float s, int h, int m) :start(h,m)
{
	name = n;
	id = i;
	salary = s;
}
void employee::write(ostream &out) const
{
	out << "{" << name << ", " << id << ", " << salary << ", ";
	start.write(out);
	out << "}";
}
