/* File: intializearray.cpp This program uses a number of different functions to initialize an array
Programmer: Siyan Zhang       Date: 2018-09-07
*/
#include <iostream>
#include <fstream>

using namespace std;

/* prototypes */
float *init(int n = 1, float val = 0.0); //function prototype with default parameters

int main(void)
{
    float* x; float val; int n;

    n = 1; x = init();
    cout << "\nx = \n"; for(int i=0; i< n; i++) { cout << x[i] << endl; }
    delete [] x;

    n = 4; x = init(n);
    cout << "\nx = \n"; for(int i=0; i< n; i++) { cout << x[i] << endl; }
    delete [] x;

    n = 5; val = 1.27; x = init(n, val);
    cout << "\nx = \n"; for(int i=0; i< n; i++) { cout << x[i] << endl; }
    delete [] x;

    return 0;
}

float *init(int n, float val)   //function returns the address of x
{
    float* x; //init a pointer
    x = new float[n]; //create an array at pointer x with size of n
    for(int i = 0; i < n; i++) {x[i] = val;} //fill up array elements with "val"
    return x;   //return the memory address of array x
}

