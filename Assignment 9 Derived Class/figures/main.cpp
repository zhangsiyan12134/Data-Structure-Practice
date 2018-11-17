// File: figures.cpp

#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class location {
private:
    float x;  // position of the figure 
    float y;
   
public:
    void read(istream& in) ;
    void write(ostream& out);
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
    string type;                      // figure type
    ofstream fout ("figuresout.txt");

    while(1)  { // loop until break occurs
        cout << "\n\nType of figure: "; cin >> type;
      
        if(type == "circle") {          
            circle* p = new circle;
            p->read(cin);
            fout << "\nobject is a circle\n";
            p->write(fout);
            delete p;
        } else if (type == "triangle")  {
            triangle* p = new triangle;
            p->read(cin);
            fout << "\nobject is a triangle\n";
            p->write(fout);
            delete p;
        } else if (type == "rectangle") {
            rectangle* p = new rectangle;
            p->read(cin);
            fout << "\nobject is a rectangle\n";
            p->write(fout);
        } else break; // we are done entering data

    }

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
