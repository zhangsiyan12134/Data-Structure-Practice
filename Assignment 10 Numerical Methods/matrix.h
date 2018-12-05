/*  File: matrix.h
    represent a matrix using a vector with operator overloading and various
    matrix functions.
*/
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;


/** a matrix is stored column by column in a vector */
class matrix {
private:
    int rows_;       // number of rows
    int cols_;       // number of columns
    vector<float> elements; 

/**
     the matrix                       the array elements
     
+-               -+         [a00,a10,a20,...,a01,a11,a21,...,a02,a12,a22,...]
| a00 a01 a02 ... |           ^               ^               ^
| a10 a11 a12 ... |           |               |               |
| a20 a21 a22 ... |           |               |               |
|  .   .   .  ... |           |               |               |
|  .   .   .  ... |        column 0        column 1        column 2
+-               -+                                                   

*/

public:
    /** constructor, fill all values with s, default 1x1, s = 0.0 */
    matrix(int m=1, int n=1, float s = 0.0); // constructor
    
    // no need for the big 3 as we use a vector object to store the matrix
    
    int rows(void) const;                    // returns rows_
    int cols(void) const;                    // returnc cols_
    float operator( )(int i, int j) const;   // returns the (i,j) entry
    float& operator( )(int i, int j);        // returns the (i,j) entry

    /** use tiny when checking for zero */
    static float tiny;

};

//////////////////////// matrix operators ////////////////////////

/** write a matrix to a stream with each row on a separate line */
ostream& operator<< (ostream& out, const matrix& a);

/** read a matrix from a stream row by row */
istream& operator>> (istream& in, matrix& a);

/** add two matrices */
matrix operator+ (const matrix& a, const matrix& b);

/** subtract two matrices */
matrix operator- (const matrix& a, const matrix& b);

/** multiply two matrices */
matrix operator* (const matrix& a, const matrix& b);

/** multiply scalar times matrix */
matrix operator* (float a, const matrix& b);


//////////////////////// matrix functions ////////////////////////

/** returns the n x n identity matrix */
matrix eye(int n);

/** returns the transpose of a matrix */
matrix transpose(const matrix& a);

/** returns the trace of a matrix */
float trace(const matrix& a);

/** returns the dot product of column vectors */
float dotproduct(const matrix& a, const matrix& b);

/** returns the Euclidean length of a matrix( sqrt of sum of squares) */
float length(const matrix& a);

/** returns the solution, x, to the matrix equation a*x = b using
    Gauss-Jordan Elimination (pass by value as a and b are modified) */
matrix solve(matrix a, matrix b);

/** returns the inverse of a square matrix if it exists */
matrix inverse(const matrix& a);

/** returns the least squares solution, x, to an overdetermined 
    system a*x = b. */
matrix leastsquares(const matrix& a, const matrix& b);

/** returns the pseudoinverse of a matrix if it exists */
matrix pseudoinverse(const matrix& a);


#endif
