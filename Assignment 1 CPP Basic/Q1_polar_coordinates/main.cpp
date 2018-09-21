/* File: polar.cpp
This is a driver program for the function polar which computes the
polar coordinates of a point in the plane
Programmer: Siyan Zhang  Date: 2018-09-06
*/

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void polar(float &a, float &b);

int main()
{
    float x, y;

    ifstream fin ("polar.txt"); //open file for reading
    ofstream fout ("polarout.txt"); //open file for output

    while(fin >> x >> y)    //keep reading data from file until EOF
    {
        polar(x, y);    //call function to calculate polar coordinate
        fout << x << " " << y << endl;  //print updated x and y
    }

    fin.close();    //close file for reading
    fout.close();   //close file for output

    return 0;
}

void polar(float &a, float &b)
{
    float r;    //init an variable to temporarily store radius
    r = sqrt(pow(a, 2) + pow(b, 2));    //calculate the radius
    if(r > 0 && b > 0)  //conditions for different r&b combination
    {
        b = acos(a/r);  //update data in variable "y" with calculated angle
    }
    if(r > 0 && b <= 0)
    {
        b = -acos(a/r); //update data in variable "y" with calculated angle
    }
    if(r == 0)
    {
        b = 0;  //update data in variable "y" with calculated angle
    }
    a = r;  //update data in variable "x" with calculated radius

    return;
}
