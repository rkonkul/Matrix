/*
Matrix.cpp
CS340
Project 2: Matrix Library
Ryan Konkul
rkonku2
*/

#include "Matrix.h"
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;
    
//Default constructor
//Constructs a 2x2 matrix with 0 values
Matrix::Matrix() {
    array = new double[4]; //default to 2x2 matrix
    for(int i=0; i<4; i++) {
        array[i] = 0.0;
    }
    num_rows = 2;
    num_cols = 2;
}

//Destructor. Deletes array from heapspace
Matrix::~Matrix() {
    delete[] array;
} 

//Constructs a matrix with all zeros
Matrix::Matrix(int num_rows_, int num_cols_) {
    num_rows = num_rows_;
    num_cols = num_cols_;
    array = new double[num_rows*num_cols];
    //encoding 2d array into 1d by row major
    for(int i=0; i<num_cols; i++) {
        for(int j=0; j<num_rows; j++) {
            array[i * num_rows + j] = 0.0; //fill with all zero
        }
    }
}

//Constructs a matrix from a filename
Matrix::Matrix(char* file_name) {
    ifstream infile(file_name); //open the file
    if(infile.fail()) { //if could not open the file
        cout << "Failed opening file: " << file_name << endl;
        return;   
    }
    int rows; 
    int cols;
    infile >> rows >> cols;
    if(rows<0 || cols<0) {
        cerr << "Bad row or col count in file " << file_name << endl;
        return;
    }
    Matrix res(rows, cols);
    double temp;
    for(int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++) {          
            infile >> temp;
            if(infile.eof()) {
                 cout << "Unexpected end of file in file " << file_name << endl;
            }
            res.access(i,j) = temp;
        }
    }
    num_rows = rows;
    num_cols = cols;
    array = new double[rows*cols];
    for(int i=0; i<rows*cols; i++) { //copy over temporary data
        array[i] = res.array[i];
    }
    infile.close(); //close the opened file
}

//Copy constructor
Matrix::Matrix(const Matrix& m) {
    num_rows = m.num_rows;
    num_cols = m.num_cols;
    array = new double[m.num_cols * m.num_rows];
    for(int i=0; i< (num_cols*num_rows); i++) {
        array[i] = m.array[i]; //no need for 2 for loops
    }
}

//Assigns a matrix
Matrix& Matrix::operator=(const Matrix& m) {
    if (this != &m) { //Check self assignment
        num_rows = m.num_rows;
        num_cols = m.num_cols;
        delete [] array; //delete data from calling object
        array = new double[m.num_rows * m.num_cols]; //make new array
        for(int i=0; i<(m.num_rows * m.num_cols); i++) {
            array[i] = m.array[i];
        }
    }
    return *this; //return this to allow cascading assignment
}

//Returns a reference at given row,col
double& Matrix::access(int row, int col) {
	if(row > num_rows-1 || row < 0 || col > num_cols-1 || col < 0) {
		cout << "Error in access: bad row,col: " << row << "," << col << endl;
        return array[0];
	}
    return array[((row * num_cols) + col)];
}

//Returns number of rows
int Matrix::getRowCount() {
    return num_rows;
}

//Returns number of columns
int Matrix::getColCount() {
    return num_cols;
}

//Adds two matrices. Row and cols must be equal.
Matrix operator+(Matrix m1, Matrix m2) {
    if((m1.num_rows != m2.num_rows) || (m1.num_cols != m2.num_cols)) {
        cout << "Error in matrix addition: rows and cols are not equal";
        //return error matrix
        return Matrix(1,1); 
    }
    //prepare to return a new matrix
    Matrix res(m1.num_rows, m1.num_cols); 
    for(int i=0; i<m1.num_rows; i++) {
        for(int j=0; j<m1.num_cols; j++) {
            res.access(i,j) = m1.access(i,j) + m2.access(i,j);
        }
    }
    return res;
}

//Returns true of matrices are of equal dimensions and values
bool operator==(Matrix& m1, Matrix& m2) {
    //first check dimensions
    if(m1.num_rows != m2.num_rows || m1.num_cols != m2.num_cols) {
        return false; 
    }
    //if any value is not the same, not equal
    for(int i=0; i<m1.num_rows; i++) {
        for(int j=0; j<m1.num_cols; j++) {
            if(m1.access(i,j) != m2.access(i,j))
                return false;           
        }
    }
    return true;
}

//Returns true of matrices are of different dimensions and values
bool operator!=(Matrix& m1, Matrix& m2) {
    //reusing code
    return !(m1 == m2); 
}

//Scalar multiplication
//Multiplies a matrix by a scalar double
Matrix operator*(Matrix m, double scalar) {
    Matrix res(m.num_rows, m.num_cols);
    for(int i=0; i<m.num_rows; i++) {
        for(int j=0; j<m.num_cols; j++) {
            res.access(i,j) = m.access(i,j) * scalar;
        }
    }
    return res;
}

//Overloaded scalar multiplication
Matrix operator*(double scalar, Matrix m) {
    return operator*(m, scalar);
}

//Matrix multiplication. Requires rows of m1==cols of m2
Matrix Matrix::operator*(Matrix m) { 
    //matrix mult. done as a method
    if(num_cols != m.num_rows) {
        cout << "Error in matrix multiply: m1 cols is not equal to m2 rows\n";
        cout << num_cols << " " << m.num_rows;
        //error matrix
        return Matrix(1,1); 
    }
    Matrix result(num_rows, m.num_cols);
    for (int i=0; i<num_rows; i++) {
        for (int j=0; j<m.num_cols; j++) {
            for (int k=0; k<num_cols; k++) {
                result.access(i, j) += access(i, k) * m.access(k, j);
            }
        }
    }
   return result;
}

//Transposes the matrix where every i,j is j,i
Matrix Matrix::operator!(){ 
    Matrix res(num_cols, num_rows);
    for(int i=0; i<num_cols; i++) {
        for(int j=0; j<num_rows; j++) {
            //swap values
            res.access(i,j) = access(j,i);  
        }
    }
    return res;
}

//Outputs the matrix onto a stream. Outputs row col on first line
//then outputs the matrix.
ostream& operator<<(ostream& stream, Matrix& m) {
    stream << "\n" << m.num_rows << " " << m.num_cols << "\n";
    for(int i=0; i<m.num_rows; ++i) {
        for(int j=0; j<m.num_cols; ++j) {
            //formatting
            stream << setw(12) << left << m.access(i, j); 
        }
        stream << "\n";
    }
    stream << "\n";
    return stream;
}

//Receives a matrix from an input stream in the same manner as 
//the output operator
istream& operator>>(std::istream& stream, Matrix& m) {
    int num_rows, num_cols;
    stream >> num_rows >> num_cols;
    //create a temporary matrix
    Matrix result(num_rows, num_cols); 
    for(int i=0; i<num_rows; i++) {
        for(int j=0; j<num_cols; j++) {
            stream >> result.access(i,j);
        }
    }
    //overwrite m with result
    m = result; 
    return stream;
}

