/* File: date.cpp
A class representing dates in the form: day, month and year
dates are written to a stream in the form day/month/year
day_number() returns the number of days since 1/1 of the current year
including the current day
days_between() returns the number of days between two dates not
including the firstday but including the last day.
Programmer: your name Date: */
#include <iostream>
#include <fstream>
using namespace std;

class date {
private:
    int day;
    int month;
    int year;
public:
    date(int d = 1, int m = 1, int y = 1);
    void write(ostream &out);
    int day_number(void);
    int days_between(const date &e);
// you fill in the method prototypes
};
// number of days in each month
const int DAYS[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int main(void)
{
    ofstream fout("date.txt");
    date d(12, 6, 2010);
    date e(14, 9, 2012);
    fout << "For the date is ";
    d.write(fout);
    fout << endl;
    fout << "Day number is " << d.day_number() << endl;
    fout << "\nFor the date is ";
    e.write(fout);
    fout << endl;
    fout << "Day number is " << e.day_number() << endl;
    fout << "\nDays between ";
    d.write(fout);
    fout << " and ";
    e.write(fout);
    fout << " = " << d.days_between(e) << endl;
    fout.close();
    return 0;
}

date::date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

void date::write(ostream &out)
{
    out << day << "/" << month << "/" << year;
}

int date::day_number(void)
{
    int n = 0;
    for(int i = 0; i < month - 1; i++)
    {
        n += DAYS[i];
    }
    return n + day;
}

int date::days_between(const date &e)
{
    int n = 0;

    if(year != e.year)
    {
        n = (DAYS[month - 1] - day) + e.day;
        for(int i = month; i < 12; i++)
        {
            n += DAYS[i];
        }
        for(int i = 0; i < e.month -1; i++)
        {
            n += DAYS[i];
        }
        n += (e.year - year -1)*365;
    }
    if(year == e.year)
    {
        n = (DAYS[month - 1] - day) + e.day;

        for(int i = month; i < e.month -1; i++)
        {
            n += DAYS[i];
        }
    }
    return n;
}
