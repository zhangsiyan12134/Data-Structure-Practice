/* File: intializearray.cpp This program uses a number of different functions to initialize an array
Programmer: Siyan Zhang       Date: 2018-09-07
*/
#include <iostream>
#include <fstream>

using namespace std;

float *init();
float *init(int n);
float *init(int n, float val);

/* prototypes */
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

float *init()   //function returns the address of x
{
    float* x; //init a pointer
    x = new float[1]; //create an array at pointer x with size of n
    x[0] = {0.0}; //fill up array with 0.0
    return x;   //return the memory address of array x
}


float *init(int n)   //function returns the address of x
{
    float* x; //init a pointer
    x = new float[n]; //create an array at pointer x with size of n
    for(int i = 0; i < n; i++) {x[i] = 0.0;} //fill up array elements with 0.0
    return x;   //return the memory address of array x
}

float *init(int n, float val)   //function returns the address of x
{
    float* x; //init a pointer
    x = new float[n]; //create an array at pointer x with size of n
    for(int i = 0; i < n; i++) {x[i] = val;} //fill up array elements with "val"
    return x;   //return the memory address of array x
}

