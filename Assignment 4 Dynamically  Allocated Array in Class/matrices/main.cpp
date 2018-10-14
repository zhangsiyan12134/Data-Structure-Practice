/* File: matrices.cpp
represent a matrix as a class with operator overloading
Name: Siyan Zhang   Date: 2018-10-08
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class matrix {
	private:
		int rows_;       // number of rows
		int cols_;       // number of columns
		float* elements; // pointer to a 1 dimensional array which stores the
		// columns of the matrix one after another
		/*
		the matrix                       the array elements
		+-               -+         [a00,a10,a20,...,a01,a11,a21,...,a02,a12,a22,...]
		| a00 a01 a02 ... |              ^               ^               ^
		| a10 a11 a12 ... |              |               |               |
		| a20 a21 a22 ... |              |               |               |
		|  .   .   .  ... |              |               |               |
		|  .   .   .  ... |           column 0        column 1        column 3
		+-               -+
		*/
	public:
		matrix(int m=1, int n=1, float s = 0.0);  // constructor
		~matrix(void);                            // destructor
		matrix(const matrix &other);              // copy constructor
		matrix &operator=(const matrix &rhs);     // operator=
		int rows(void) const;                     // returns rows_
		int cols(void) const;                     // returnc cols_
		float at(int i, int j) const;             // returns the (i,j) entry
		float &at (int i, int j);                 // returns the (i,j) entry
};

// prototypes for matrix operators
matrix operator+(const matrix &x, const matrix &y);
matrix operator*(const matrix &x, const matrix &y);
istream& operator>>(istream &infile, matrix &x);
ostream& operator<<(ostream &outfile, const matrix &x);

int main(void)
{
	ifstream fin("matricesin.txt");
	ofstream fout("matricesout.txt");
	matrix a(2,2), b(2,2), c(2,4);
	fin >> a >> b >> c;
	// try the copy constructor
	matrix d(a);
	fout << "The copy of a is\n";
	fout << d << "\n";
	d = a + b; // check out operator= and operator+
	fout << "The sum of \n" << a << "and\n" << b << "is\n" << d;
	d = a * c; // check out operator= and operator*
	fout << "\nThe product of \n" << a << "and\n" << c << "is\n" << d;
	fin.close();
	fout.close();
	return 0;
}
//////////////////////// implementation of matrix ///////////////////////


// constructor, fill all values with s, default 1x1, s = 0.0
matrix::matrix(int m, int n, float s)
{
	int i;
	rows_ = m;
	cols_ = n;
	elements = new float[m*n];
	for(i = 0; i < m*n; i++) {
		elements[i] = s;
	}
}
// implementation of the big 3
matrix::~matrix(void)
{
	delete [] elements;
}
matrix::matrix(const matrix &other)
{
	cols_ = other.cols_;
	rows_ = other.rows_;
	elements = new float [rows_ * cols_];
	for(int i = 0; i < rows_ * cols_; i++)
	{
		for(int j = 0; j < rows_ * cols_; j++)
		{
			elements[i] = other.elements[i];
		}
	}
}
matrix& matrix::operator=(const matrix &rhs)
{
	if(this != &rhs)
	{
		delete [] elements;
		cols_ = rhs.cols_;
		rows_ = rhs.rows_;
		elements = new float[cols_* rows_];
		for(int i = 0; i < rows_ * cols_; i++)
		{
            elements[i] = rhs.elements[i];
		}
	}
	return *this;
}

// returns the (i,j) entry of the matrix by reference
float &matrix::at(int i, int j)
{
	if( (i >= rows_) || (j >= cols_) ){
		cerr << "subscript out of bounds\n";
		exit(1);
	}
	return elements[ i +j*rows_ ];
}
// returns the (i,j) entry of the matrix
float matrix::at(int i, int j) const
{
	if( (i >= rows_) || (j >= cols_) ){
		cerr << "subscript out of bounds\n";
		exit(1);
	}
	return elements[ i +j*rows_ ];
}

int matrix::rows(void) const
{
	return rows_;
}
int matrix::cols(void) const
{
	return cols_;
}
///////////////////////////// matrix operators ///////////////////////////
matrix operator+(const matrix &x, const matrix &y)
{
	if(x.rows() == y.rows() && x.cols() == y.cols())
	{
		matrix sum(x.rows(), x.cols());
		for(int i = 0; i < x.rows(); i++)
		{
			for(int j = 0; j < x.cols(); j++)
			{
				sum.at(i,j) = x.at(i,j) + y.at(i,j);
			}
		}
		return sum;
	} else
	{
		cout << "error: size of matrices are not match!";
		exit(1);
	}
}
matrix operator*(const matrix &x, const matrix &y)
{
	if(x.cols() == y.rows())
	{
		matrix product(x.rows(), y.cols());
		for(int i = 0; i < x.rows(); i++)
		{
			for(int j = 0; j < y.cols(); j++)
			{
			    for(int k = 0; k < x.cols(); k++)
                {
                    product.at(i,j) = product.at(i,j) + x.at(i,k) * y.at(k,j);
                }
			}
		}
		return product;
	} else
	{
		cout << "error: size of matrices are not match!";
		exit(1);
	}
}

istream& operator>>(istream &infile, matrix &x)
{
    for(int i = 0; i < x.rows(); i++)
    {
        for(int j = 0; j < x.cols(); j++)
        {
            infile >> x.at(i,j);
        }
    }
    return infile;
}

ostream& operator<<(ostream &outfile, const matrix &x)
{
    for(int i = 0; i < x.rows(); i++)
    {
        for(int j = 0; j < x.cols(); j++)
        {
            outfile << setw(6)<< x.at(i,j) << "\t";
        }
        outfile << endl;
    }
    return outfile;
}
