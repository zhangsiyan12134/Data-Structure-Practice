/*  File: workforce.cpp
An employee's information is stored as an object of type employee
consisting of name, employee id and employee salary.  The methods
read() and write() are defined for employee.
Information about a company's workforce is stored in an object of type
workforce consisting of the workforce size and a dynamically allocated
array of employees.  The methods read() and write() are defined for
workforce.
The read() and write() methods for workforce uses the read()and write()
methods for employee
Programmer: Siyan Zhang            Date: 2018-10-05
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class employee {
	private:
		string name;  // last name
		int id;       // employee id number
		float salary; // employee salary
	public:
		employee(string n = "nobody", int i = 0, float s = 0);
		void read(istream &in);
		void write(ostream &out) const;
};
class workforce {
	private:
		int size;           // size of workforce
		employee* list; // array of employees
	public:
		workforce(int n);   // set size = n and allocate an array of employees
		// big 3 prototypes here
		workforce(const workforce &x);
		~workforce(void);
		workforce& operator=(const workforce &x);
		void read(istream &in);
		void write(ostream &out) const;
};
int main(void)
{
	workforce w(5);
	ifstream fin("workforcein.txt"); // file containing the list of employees
	ofstream fout("workforceout.txt");
	char ch;
	w.read(fin);
	fout << "\nw = \n";
	w.write(fout);
	cout << "C to copy otherwise assign: ";
	cin >> ch;
	if(ch == 'C') {
		workforce v(w);     // v's scope is the body of the if
		fout << "\nv = \n";
		v.write(fout);
		// v is destroyed here
	} else {
		workforce u(10);    // u's scope is the body of the else
		u = w;
		fout << "\nu = \n";
		u.write(fout);
		// u is destroyed here
	}
	fout << "\nw = \n";     // check whether w is still intact
	w.write(fout);
	fin.close();
	fout.close();
	return 0;
}
////////////////////// implementation of employee ////////////////////////
employee::employee(string n, int i, float s)
{
	name = n;
	id = i;
	salary = s;
}
void employee::read(istream &in)
{
	in >> name >> id >> salary;
}
void employee::write(ostream &out) const
{
	out << name << " " << id << " " << salary << endl;
}
/////////////////////// implementation of workforce //////////////////////
workforce::workforce(int n)
{
	size = n;
	list = new employee [n];
}
workforce::workforce(const workforce &x)
{
	size = x.size;
	list = new employee[size];
	for(int i = 0; i < size; i++)
	{
		list[i] = x.list[i];
	}
}
workforce::~workforce(void)
{
	delete [] list;
}
workforce& workforce::operator=(const workforce &x)
{
	if(this != &x)
	{
		delete [] list;
		size = x.size;
		list = new employee[size];
		for(int i = 0; i < size; i++)
		{
			list[i] = x.list[i];
		}
	}
	return *this;
}
void workforce::read(istream &in)
{
	for(int i = 0; i < size; i++)
	{
		list[i].read(in);
	}
}
void workforce::write(ostream &out) const
{
	for(int i = 0; i < size; i++)
	{
		list[i].write(out);
	}
}
