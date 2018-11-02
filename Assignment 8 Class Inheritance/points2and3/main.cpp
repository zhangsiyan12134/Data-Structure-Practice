/*  File: points2and3.cpp
    investigate the big3 with inheritance*/
    
#include <iostream>
#include <fstream>

using namespace std;

class point2 {
private:
    float x;
    float y;
public:
    point2(float xval = 0.0, float yval = 0.0);
    point2(const point2 &other);
    ~point2(void);
    point2& operator=(const point2 &rhs);

    void write(ostream &out) const;
};

class point3 : public point2 {
private:
    float z;
public:
    point3(float xval = 0.0, float yval = 0.0, float zval = 0.0);
    point3(const point3 &other);
    ~point3(void);
    point3 &operator=(const point3 &rhs);

    void write(ostream &out) const;
};

int main(void)
{
    point3 a(1.0, 2.0, 3.0), b(a), c;
    
    c = a;
    
    return 0;
}

////////////////////// implementation of point2 ////////////////////////

point2::point2(float xval, float yval) 
{
    x = xval;
    y = yval;
    cout << "creating point2: ";
    write(cout);
    cout << endl;
}
point2::point2(const point2 &other)
{
    x = other.x;
    y = other.y;
    cout << "creating point2 copy: ";
    write(cout);
    cout << endl;
}
point2::~point2(void)
{
    cout << "desroying point2: ";
    write(cout);
    cout << endl;
}
point2 &point2::operator=(const point2 &rhs)
{
    if(this != &rhs) {
        x = rhs.x;
        y = rhs.y;
        cout << "assigning point2: ";
        write(cout);
        cout  << endl;
    }
    return *this;
}
void point2::write(ostream &out) const
{
    out << x << ", " << y;
}

////////////////////// implementation of point3 ////////////////////////
point3::point3(float xval, float yval, float zval):point2(xval, yval)
{
	z = zval;
	cout << "creating point3: ";
    write(cout);
    cout << endl;
}
point3::point3(const point3 &other):point2(other)
{
	z = other.z;
	cout << "creating point3 copy: ";
    write(cout);
    cout << endl;
}
point3::~point3(void)
{
	cout << "desroying point3: ";
    write(cout);
    cout << endl;
}
point3& point3::operator=(const point3 &rhs)
{
	if(this != &rhs)
	{
		point2::operator=(rhs);
		z = rhs.z;
		cout << "assigning point3: ";
        write(cout);
        cout  << endl;
	}
	return *this;
}

void point3::write(ostream &out) const
{
	point2::write(out);
	cout << ", " << z;
}

