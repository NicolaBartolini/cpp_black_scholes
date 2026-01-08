#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>

class Matrix {
    int n_rows; // number of rows
    int n_cols; // number of columns
    double* elements; // pointer to store matrix elements
public:
    Matrix(); // default (no-argument) constructor
    Matrix(int, int); // constructor that initializes matrix with given dimensions
    ~Matrix(); // destructor to free memory
    Matrix(const Matrix&); // copy constructor to create a new matrix by copying another matrix

    // methods
    void set_element(double, int, int); // sets the value of a matrix element
    double get_element(int, int) const; // gets the value of a matrix element
    int get_ncolumns(); // returns the number of columns
    int get_nrows(); // returns the number of rows
    void shape(); // prints the shape (dimensions) of the matrix
    void print(); // prints the matrix elements
    Matrix T(); // Transpose of the matrix
    Matrix get_row(int); // returns a specific row of the matrix
    Matrix get_column(int); // returns a specific column of the matrix

    // operator overloading 
    Matrix& operator=(const Matrix&); // assignment operator
    Matrix operator+(const Matrix&); // sum operator between matrices
    Matrix operator+(const double); // sum operator between a matrix and a number
    Matrix operator-(const Matrix&); // difference operator between matrices
    Matrix operator-(const double); // difference operator between a matrix and a number
    Matrix operator*(const double); // multiplication by scalar

    // Matrix operations
    Matrix dot(const Matrix&); // matrix multiplication
    Matrix* luDecomposition(); // LU decomposition of the matrix
    double det(); // determinant of the matrix
    Matrix cofactor(); // cofactor matrix
    Matrix inverse(); // inverse matrix
    
    // Element operations
    double mean();
    Matrix mean(int axis);
    Matrix flatten();
    void sort();
    double max();
    double min();
};

#endif // MATRIX_HPP