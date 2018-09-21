/* File: minmax.cpp
Programmer: Siyan Zhang  Date: 2018-09-06
*/

#include <iostream>
#include <fstream>

using namespace std;

const int N = 100; // maximum array size

void readdata(int &n, float *x);
void minmax(int n, float *x, float &min, float &max);

int main(void)
{
    ofstream outfile("minmaxout.txt");

    float x[N]; // the array
    int n ; // the actual array size
    float max; // the maximum
    float min; // the minimum
    /* read the data into the array */
    readdata(n, x);
    /* compute the maximum and minimum */
    minmax(n, x, min, max);
    outfile << "The array has " << n << " elements\n";
    outfile << "The maximum value in the array is " << max << endl;
    outfile << "The minimum value in the array is " << min << endl;
    outfile.close();
    return 0;
}

void readdata(int &n, float *x)
{
    int i;  //init a temp counter
    ifstream infile ("minmax.txt"); //open file for read
    infile >> n;    //read very first value
    for(i = 0; i < n; i++)  //for loop for data reading
    {
        infile >> x[i]; //read each line into array
    }
    infile.close(); //close file
    return;
}

void minmax(int n, float *x, float &min, float &max)
{
    int i;  //init a temp counter
    for(i = 0; i < n; i++)  //for loop for data comparison
    {
        if(i == 0)    //init "min" & "max" with extreme value
        {
            min = 3.4E+38;  //assign maximum value of float for "min" to avoid true data is smaller than random data inside.
            max = 1.8E-38;  //assign minimum value of float for "max" to avoid true data is bigger than random data inside.
        }
        if(x[i] <= min) {min = x[i];}   //compare data in "min" with array element, replace data in "min" if current array element is smaller
        if(x[i] >= max) {max = x[i];}   //compare data in "max" with array element, replace data in "max" if current array element is greater
    }
    return;
}
// put your function definitions here
