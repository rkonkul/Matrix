/*
Matrix.h
CS340
Project 2: Matrix Library
Ryan Konkul
rkonku2
*/

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>

class Matrix {
private:
	//Stored 2d array in 1d array in row major
	double *array;
	int num_rows;
	int num_cols;

public:
    //Default constructor
    //Constructs a 2x2 matrix with 0 values
    Matrix();
	//Destructor. Deletes array from heapspace
	~Matrix();
	//Constructs a matrix with all zeros
    Matrix(int num_rows_, int num_cols_);
    //Constructs a matrix from a filename
    Matrix(char* file_name);// file_name);
    //Copy constructor
    Matrix(const Matrix& m);
    //Assigns a matrix
    Matrix& operator=(const Matrix& p);
    //Returns a reference at given row,col
    double& access(int row, int col);
    //Returns number of rows
    int getRowCount();
    //Returns number of columns
    int getColCount();
    //Adds two matrices. Row and cols must be equal.
    friend Matrix operator+(Matrix m1, Matrix m2);
    //Returns true of matrices are of equal dimensions and values
    friend bool operator==(Matrix& m1, Matrix& m2);
    //Returns true of matrices are of different dimensions and values
    friend bool operator!=(Matrix& m1, Matrix& m2);
    //Scalar multiplication
    //Multiplies a matrix by a scalar double
    friend Matrix operator*(Matrix m, double scalar);
    //Overloaded scalar multiplication
    friend Matrix operator*(double scalar, Matrix m);
    //Matrix multiplication. Requires rows of m1==cols of m2
    Matrix operator*(Matrix m);
    //Transposes the matrix where every i,j is j,i
    Matrix operator!();
    //Outputs the matrix onto a stream. Outputs row col on first line
    //then outputs the matrix.
    friend std::ostream& operator<<(std::ostream& stream, Matrix& m);
    //Receives a matrix from an input stream in the same manner as 
    //the output operator
    friend std::istream& operator>>(std::istream& stream, Matrix& m);
};

#endif /* MATRIX_H_ */
