// File: figstack.cpp

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

class location {
private:
    float x;  // position of the figure 
    float y;
   
public:
    virtual void read(istream& in) ;
    virtual void write(ostream& out);
    virtual float area(void); // returns 0 
};

class circle : public location {
private:
    float radius;

public:
    void read(istream& in);
    void write(ostream& out);
    float area(void);      // area of the figure;
};

class rectangle : public location {
private:
    float side1, side2;
   
public:
    void read(istream& in);
    void write(ostream& out);
    float area(void);      // area of the figure;
};

class triangle : public rectangle {
private:
    float angle;
   
public:
    void read(istream& in);
    void write(ostream& out);
    float area(void);      // area of the figure;
};

int main()
{
    ofstream fout("figstack.out");
    stack<location*> mystack;
    char ch;       // response to prompt
    string type;   // type of figure
    location* ptr; // pointer to object pushed or popped
   
    while(1) {
        // print a little menu
        cout << "\n\np = push \n";
        cout << "o = pop\n";
        cout << "q = quit\n\n";
      
        cin >> ch;
      
        if (ch == 'p') {
            cout <<"\nEnter type of data to push : ";
            cin >> type;
            ptr = NULL;

            if(type == "circle") ptr = new circle;
            else if(type == "triangle") ptr = new triangle;
            else if (type == "rectangle") ptr = new rectangle;
         
            if(ptr != NULL) { // got a valid type
                ptr->read(cin);
                mystack.push(ptr);
            }
        }
      
        if(ch == 'o') {
            if(mystack.empty()) cout << "stack is empty\n";
            else {
                ptr = mystack.top();         
                mystack.pop();
                cout << "popped:\n"; ptr->write(cout); cout << "\n";
                fout << "popped:\n"; ptr->write(fout); fout << "\n";
            }
        }
        
        if(ch == 'q') break;
    }
    fout.close();  
    return 0;
}

////////////////// implementation of location /////// ///////////

void location::read(istream& in)
{
    if(&in == &cin) cout <<"x coordinate: "; 
    in >> x;
   
    if(&in == &cin) cout <<"y coordinate: "; 
    in >> y;
}

float location::area(void)
{
    return 0.0;
}

void location::write(ostream& out)
{
    out << "x coordinate: " << x << "\n";
    out << "y coordinate: " << y << "\n";
    out << "area = " << area() << endl;
   
}

////////////////// implementation of circle /////// ///////////
void circle::read(istream& in)
{
	location::read(in);
	if(&in == &cin) cout <<"redius of circle: "; 
	in >> radius;
}

void circle::write(ostream& out)
{
	location::write(out);
	out << "radius = " << radius << endl;
}

float circle::area(void)      // area of the figure;
{
	return 3.1415926535*radius*radius;
}

////////////////// implementation of rectangle /////// ///////////
void rectangle::read(istream& in)
{
	location::read(in);
	if(&in == &cin) cout <<"length of first side: "; 
	in >> side1;
	if(&in == &cin) cout <<"length of second side: "; 
	in >> side2;
}
void rectangle::write(ostream& out)
{
	location::write(out);
	out << "side1 = " << side1 << endl;
	out << "side2 = " << side2 << endl;
}
float rectangle::area(void)      // area of the figure;
{
	return side1*side2;
}

////////////////// implementation of triangle /////// ///////////
void triangle::read(istream& in)
{
	rectangle::read(in);
	if(&in == &cin) cout <<"angle of triangle: ";
	in >> angle;
}
void triangle::write(ostream& out)
{
	rectangle::write(out);
	out << "angle = " << angle << endl;
}
float triangle::area(void)      // area of the figure;
{
	return rectangle::area() / 2;
}
