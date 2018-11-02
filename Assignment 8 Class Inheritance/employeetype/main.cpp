// File: employeetypes.cpp
// Program to illustrate derived classes

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
    employee(string n="none", int i=0, float s=0.0);
    void write(ostream &out);
    void read(istream &in);
};

class manager : public employee {  
private:
    string title;       // vice-president etc
public:
    manager(string n="none", int i=0, float s=0.0, string t="none");
    void write(ostream &out);
    void read(istream &in);
};

class scientist : public employee{  
private:
    int pubs;           // number of publications

public:
    scientist(string n="none", int i=0, float s=0.0, int p=0);
    void write(ostream &out);
    void read(istream &in);
};

class labourer : public employee {    
private:
    string dept;
      
public:
    labourer(string n="none", int i=0, float s=0.0, string d="none");
    void write(ostream &out);
    void read(istream &in);
};

int main()
{
    string type;            // employee type
    ofstream fout ("employeetypesout.txt");

    while(1) { // loop until break occurs
        cout << "\n\nType of employee: "; cin >> type;
        if (type == "q") break;

        if(type == "labourer") {     
            labourer lab;
            lab.read(cin);

            cout << "\n";
            lab.write(cout);
            fout << "\n";
            lab.write(fout);

        } else if (type == "scientist") { 
            scientist sci;
            sci.read(cin);

            cout << "\n";
            sci.write(cout);
            fout << "\n";
            sci.write(fout);

        } else if (type == "manager") {        
            manager man;
            man.read(cin);

            cout << "\n";
            man.write(cout);
            fout << "\n";
            man.write(fout);

        }        
   }
   fout.close();   
   return 0;
}

///////////////// Member functions of employee /////////////////////////////

employee::employee(string n, int i, float s)
{
    name = n;
    id = i;
    salary = s;
}
void employee::write(ostream &out)
{

    out << "name  : " << name <<   "\n";
    out << "id    : " << id  <<    "\n";
    out << "salary: " << salary << "\n";
}
void employee::read(istream &in)
{
    if(in == cin) { // give a prompt to the user
        cout << "name  : ";
    }
    in >> name;

    if(in == cin) { // give a prompt to the user
        cout << "id  : ";
    }
    in >> id;
    
    if(in == cin) { // give a prompt to the user
        cout << "salary: ";
    }
    in >> salary;
}      
//////////////////// Member functions of labourer /////////////////////////

labourer::labourer(string n, int i, float s, string d):employee(n, i, s)
{
	dept = d;
}

void labourer::write(ostream &out)
{
	employee::write(out);
	out << "department: " << dept << endl;
}
void labourer::read(istream &in)
{
	employee::read(in);
	if(in == cin) { // give a prompt to the user
        cout << "department: ";
    }
    in >> dept;
}

//////////////////// Member functions of manager ///////////////////////////
manager::manager(string n, int i, float s, string t):employee(n, i, s)
{
	title = t;
}
void manager::write(ostream &out)
{
	employee::write(out);
	out << "title: " << title << endl;
}
void manager::read(istream &in)
{
	employee::read(in);
	if(in == cin) { // give a prompt to the user
        cout << "title: ";
    }
    in >> title;
}

//////////////////// Member functions of scientist ////////////////////////
scientist::scientist(string n, int i, float s, int p):employee(n, i, s)
{
	pubs = p;
}
void scientist::write(ostream &out)
{
	employee::write(out);
	out << "number of publications: " << pubs << endl;
}
void scientist::read(istream &in)
{
	employee::read(in);
	if(in == cin) { // give a prompt to the user
        cout << "number of publications: ";
    }
    in >> pubs;
}
