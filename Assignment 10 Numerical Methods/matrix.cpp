/*  File: matrix.cpp
    represent a matrix using a vector with operator overloading and various
    matrix functions.
*/
   
#include "matrix.h"

float matrix::tiny = 0.00001;

/////////////////////// matrix methods ////////////////////////

/** constructor, fill all values with s, default 1x1, s = 0.0 */
matrix::matrix(int m, int n, float s) : elements(m*n, s)
{
    rows_ = m;
    cols_ = n;
}

/** returns the (i,j) entry of the matrix */
float& matrix::operator(  )(int i, int j)
{
    if( (i >= rows_) || (j >= cols_) ){
        cerr << "subscript out of bounds\n";
        exit(1);
    }
   
    return elements[ i + j*rows_ ];
}

/** returns the (i,j) entry of the matrix */
float matrix::operator( )(int i, int j) const
{
    if( (i >= rows_) || (j >= cols_) ){
       cerr << "subscript out of bounds\n";
       exit(1);
    }
   
    return elements[ i + j*rows_ ];
}

/** returns the number of rows in the matrix */
int matrix::rows(void) const
{
    return rows_;
}

/** returns the number of columns in the matrix */
int matrix::cols(void) const
{
    return cols_;
}

//////////////////////// matrix operators ////////////////////////

/** write a matrix to a stream with each row on a separate line  */
ostream& operator<< (ostream& out, const matrix& a)
{
    int i, j;
   
    // used 5 after the decimal point
    out << fixed << setprecision(5);
     
    for(i=0; i<a.rows(); i++) {
        for(j=0; j< a.cols(); j++) {
            out << setw(12) << a(i, j);
        }
        out << "\n";
     }
   return out;
}

/** read the matrix row by row */
istream& operator>> (istream& in, matrix& a)
{
    int i, j;

    for(i=0; i<a.rows(); i++){ 
        for(j=0; j< a.cols(); j++){ 
            in >> a(i, j);
        }
    }              
   
   return in;
}

/** add two matrices */
matrix operator + (const matrix& a, const matrix& b)
{
    int i, j;
    if( (a.rows() != b.rows() ) || (a.cols() != b.cols() ) ) {
        cerr << "matrices not compatible\n";
        exit(1);
    }
   
    matrix c(a.rows(), a.cols());
   
    for(i=0; i<a.rows(); i++) {
        for(j=0; j<a.cols(); j++) {
            c(i, j) = a( i, j) + b(i, j);
         }
     }
   
    return c;
}

/** subtract two matrices */
matrix operator - (const matrix& a, const matrix& b)
{
    matrix c = a + (-1.0) * b;
    return c;
}

/** multiply two matrices */
matrix operator * (const matrix& a, const matrix& b)
{
    int i, j, k;
    if(a.cols() != b.rows()) {
        cerr << "matrices not compatible\n";
        exit(1);
    }
   
    matrix c(a.rows(), b.cols());
   
    for(i=0; i<a.rows(); i++) {
        for(j=0; j<b.cols(); j++) {
            for(k=0; k<a.cols(); k++) {
                c(i, j) = c(i, j) + a(i, k)*b(k, j);
            }
        }
    }
   
    return c;
}

/** multiply scalar times matrix */
matrix operator* (float a, const matrix& b)
{
    int i, j;
    matrix c(b);
    
    for(i = 0; i < b.rows(); i++) {
        for(j = 0 ; j < b.cols(); j++) {
            c(i,j) = a*c(i,j);
        }
    }
    return c;
}
    
//////////////////////// matrix functions ////////////////////////

/** returns the nxn identity matrix */
matrix eye(int n)
{
    int i,j;
    matrix x(n, n, 0.0);
   
    for(i=0; i<n; i++) {
        x(i,i) = 1.0;
    }
         
    return x;
}

/** returns the transpose of a matrix */
matrix transpose(const matrix& a)
{
    matrix b(a.cols(), a.rows());
    int i, j;
    
    for(i=0; i < b.rows(); i++) {
        for(j = 0; j < b.cols(); j++) {
            b(i,j) = a(j,i);
        }
    }
    return b;
}

/** returns the trace of a matrix */
float trace(const matrix& a)
{
    float t = 0.0;;
    int i;
    int h = a.rows();
    if (h > a.cols()) h = a.cols();
    
    for (i=0; i< h; i++) {
        t = t + a(i,i);
    }
    return t;
}

/** returns the dot product of two column vectors */
float dotproduct(const matrix& a, const matrix& b)
{
    float t = 0.0;
    int i;
    
    if(a.cols() == 1 && b.cols() ==1 && a.rows() == b.rows()) {
        for(i = 0; i < a.rows(); i++) {
                t = t + a(i,0)*b(i,0);
        }
    } else {
        cerr << "not column vectors of the same size\n";
        exit(1);
    
    }

    return t;
}


/** returns the Euclidean length of a matrix (sqrt of sum of squares) */
float length(const matrix& a)
{
    float t = 0.0;
    int i, j;
    for(i = 0; i < a.rows(); i++) {
        for(j=0; j < a.cols(); j++) {
            t = t + a(i,j)*a(i,j);
        }
    }
    t = sqrt(t);       

    return t;
}



