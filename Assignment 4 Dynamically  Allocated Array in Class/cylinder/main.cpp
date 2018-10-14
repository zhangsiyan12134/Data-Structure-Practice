/*  File: cylinder.cpp
classes which represents points, circles and cylinders in the plane
Name: Siyan Zhang   Date: 2018-10-05
*/
#include <iostream>
#include <fstream>
using namespace std;
class point {
	private:
		float x;
		float y;
	public:
		point(float h, float v);            // x = h and y = v
		void write(ostream &out) const;     // write a point in the form (x,y)
};
class circle {
	private:
		point centre;
		float radius;
	public:
		circle(const point &p, float r);
		void write(ostream &out) const;
};
class cylinder {
	private:
		circle base;
		float height;
	public:
		cylinder(const circle &c, float ht);
		void write(ostream &out) const;
};
int main(void)
{
	point p(1.0, 2.0);
	cout << "p = ";
	p.write(cout);
	cout << endl;
	circle cir(p, 3.0);
	cout << "cir = ";
	cir.write(cout);
	cout << endl;
	cylinder cyl(cir, 7.0);
	cout << "cyl = ";
	cyl.write(cout);
	cout << endl;
	return 0;
}
//////////////////////////// implementation of point //////////////////////
point::point(float h, float v) // x = h and y = v
{
	x = h;
	y = v;
}
void point::write(ostream &out) const // write a point in the form (x,y)
{
	out << "(" << x << "," << y << ")";
}
/////////////////////////// implementation of circle ///////////////////////
circle::circle(const point &p, float r) :centre(p)
{
	radius = r;
}
void circle::write(ostream &out) const
{
	out << "(center = ";
	centre.write(out);
	out << ", radius = " << radius << ")";
}
/////////////////////////// implementation of cylinder//////////////////////
cylinder::cylinder(const circle &c, float ht) :base(c)
{
	height = ht;
}
void cylinder::write(ostream &out) const
{
	out << "(base = ";
	base.write(out);
	out << ", height = " << height << ")";
}
