/* File: time24methods.cpp
the class time24 represents time on 24 hour clock
times are written to a stream in the form hour:minute
when a time is added to the current time the minutes are added and if
the sum is 60 or more then 60 is subtracted from the sum but the the
hour is increased by 1. If the hour is 24 or more then 24 is subtrated
from the hour.
Programmer: Siyan Zhang Date: */
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class time24 {
private:
    int hour_; // hour between 0 and 23
    int minute_; // minute between 0 and 59
public:
    time24(int h = 0 , int m = 0); // constructor with default args
    void write(ostream &out); // prints hour:minute to out
    time24 add(const time24 &y) const; // add y to current time
};

int main(void) // test the class
{
    time24 x(18, 34), y(10,56), z;
    cout << "The time x is: ";
    x.write(cout);
    cout << "\nThe time y is: ";
    y.write(cout);
    // try conversion
    z = 12;
    cout << "\nThe time z is: ";
    z.write(cout);
    // try adding
    z = x.add(y);
    cout << "\nThe sum of ";
    x.write(cout);
    cout << " and ";
    y.write(cout);
    cout << " is ";
    z.write(cout);
    cout << endl;
    return 0;
}

time24::time24(int h, int m)
{
    hour_ = h;
    minute_ = m;
}

void time24::write(ostream &out)
{
     cout << setfill('0') << setw(2) << hour_ << ":" << setfill('0') << setw(2)  << minute_; //output time in "hh:mm" format
}

time24 time24::add(const time24 &y) const
{
    time24 z;
    int Carry = 0;  //carry flag if sum of minutes is greater than 60

    if(minute_ + y.minute_ < 60)
    {
        z.minute_ = minute_ + y.minute_;  //if sum of minutes is less than 60, set time as is
    } else
    {
        z.minute_ = minute_ + y.minute_ - 60; //otherwise subtract 60 then set time
        Carry = 1;  //set flag for additional 1 hour
    }

    if(hour_ + y.hour_ + Carry < 24)
    {
        z.hour_ = hour_ + y.hour_ + Carry;    //if sum of hours is less than 24, set time as is
    } else
    {
        z.hour_ = hour_ + y.hour_ + Carry - 24;   //otherwise subtract 24 then set time
    }
    return z;   //return member z
}
