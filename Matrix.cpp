#include "Matrix.hpp"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <stdexcept>


// definition

// constructors and destructor

Matrix::Matrix() : n_cols(0), n_rows(0), elements(nullptr) {}
// elements(nullptr) means no memory is allocated yet for matrix data (it is a null pointer)

// constructor that initializes matrix with given dimensions
Matrix::Matrix(int n, int m) {
	n_rows = n;
	n_cols = m;
	elements = new double[n_rows * n_cols];
}

// copy constructor to create a new matrix by copying another matrix
Matrix::Matrix(const Matrix& M){
	n_rows = M.n_rows; // get the number of rows from the original matrix
	n_cols = M.n_cols; // get the number of columns from the original matrix
	elements = new double[n_rows * n_cols]; 
	for (int i = 0; i < n_rows * n_cols; ++i) {
		elements[i] = M.elements[i];
	}
}

// destructor to free memory
Matrix::~Matrix() {
	delete[] elements;
} 

// basic methods
void Matrix::set_element(double x, int row, int col){
	elements[row*n_cols + col] = x;
}

double Matrix::get_element(int row, int col) const{
	return elements[row*n_cols + col];
}

int Matrix::get_ncolumns(){
	return n_cols;
}

int Matrix::get_nrows(){
	return n_rows;
}

void Matrix::shape(){
	std::cout<< n_rows << "," << n_cols<<std::endl;
}

void Matrix::print(){
	for (int i = 0; i < n_rows; ++i)
	{
		for (int j = 0; j < n_cols; ++j)
		{
			double x;
			x = elements[i*n_cols + j];
			std::cout<<x<<'\t';
		}
		std::cout<<std::endl;
	}
}

Matrix Matrix::T(){

	Matrix result(n_cols, n_rows);

	for (int i = 0; i < n_rows; ++i)
	{
		for (int j = 0; j < n_cols; ++j)
		{
			double x;
			x = elements[i*n_cols + j];
			result.set_element(x, j, i);
		}
	}
	return result;
}


Matrix Matrix::get_row(int I) {
	if (I < 0 || I >= n_rows) {
		std::cerr << "Row index out of bounds!" << std::endl;
		exit(EXIT_FAILURE);
	}
	Matrix result(1, n_cols);  // 1 row, same number of columns

	for (int j = 0; j < n_cols; ++j) {
		double val = get_element(I, j);
		result.set_element(val, 0, j);  // row is always 0 in result
	}

	return result;
}


Matrix Matrix::get_column(int J) {
	if (J < 0 || J >= n_cols) {
		std::cerr << "Column index out of bounds!" << std::endl;
		exit(EXIT_FAILURE);
	}
	Matrix result(n_rows, 1);  // same number of rows, 1 column


	for (int i = 0; i < n_rows; ++i) {
		double val = get_element(i, J);
		result.set_element(val, i, 0);  // column is always 0 in result
	}
	return result;
}



// Operators

Matrix& Matrix::operator=(const Matrix& other) {
	if (this != &other) {
		delete[] elements;  // free existing memory
		n_rows = other.n_rows;
		n_cols = other.n_cols;
		elements = new double[n_rows * n_cols];
		for (int i = 0; i < n_rows * n_cols; ++i) {
			elements[i] = other.elements[i];
		}
	}
	return *this;
}


Matrix Matrix::operator+(const Matrix& other) {
    // assumes dimensions match — you can add checks!

    Matrix result(n_rows, n_cols);
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            double val = this->get_element(i, j) + other.get_element(i, j);
            result.set_element(val, i, j);
        }
    }
    return result;
}


Matrix Matrix::operator+(const double x) {
    // assumes dimensions match — you can add checks!

    Matrix result(n_rows, n_cols);
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            double val = this->get_element(i, j) + x;
            result.set_element(val, i, j);
        }
    }
    return result;
}


Matrix Matrix::operator-(const Matrix& other) {
    // assumes dimensions match — you can add checks!

    Matrix result(n_rows, n_cols);
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            double val = this->get_element(i, j) - other.get_element(i, j);
            result.set_element(val, i, j);
        }
    }
    return result;
}


Matrix Matrix::operator-(const double x) {
    // assumes dimensions match — you can add checks!

    Matrix result(n_rows, n_cols);
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            double val = this->get_element(i, j) - x;
            result.set_element(val, i, j);
        }
    }
    return result;
}


// Matrix operations

Matrix Matrix::dot(const Matrix& other) {
	if (n_cols != other.n_rows) {
		std::cerr << "Matrix dimensions do not align for multiplication!" << std::endl;
		exit(EXIT_FAILURE); // or throw std::invalid_argument
	}

	Matrix result(n_rows, other.n_cols);

	for (int i = 0; i < n_rows; ++i) {
		for (int j = 0; j < other.n_cols; ++j) {
			double sum = 0.0;
			for (int k = 0; k < n_cols; ++k) {
				sum += this->get_element(i, k) * other.get_element(k, j);
			}
			result.set_element(sum, i, j);
		}
	}
	return result;
}

Matrix* Matrix::luDecomposition() {
	// source of the code https://www.sanfoundry.com/cpp-program-perform-lu-decomposition-any-matrix/#google_vignette 
	// Crout's method
    if (n_rows != n_cols) {
        std::cerr << "LU decomposition requires a square matrix." << std::endl;
        exit(EXIT_FAILURE);
    }

    int n = n_rows;

    Matrix* result = new Matrix[2];
    Matrix& L = result[0] = Matrix(n, n);
    Matrix& U = result[1] = Matrix(n, n);

    for (int i = 0; i < n; i++) {
        // Compute L
        for (int j = 0; j < n; j++) {
            if (j < i)
                L.set_element(0.0, j, i);
            else {
                double sum = 0.0;
                for (int k = 0; k < i; k++)
                    sum += L.get_element(j, k) * U.get_element(k, i);
                L.set_element(this->get_element(j, i) - sum, j, i);
            }
        }

        // Compute U
        for (int j = 0; j < n; j++) {
            if (j < i)
                U.set_element(0.0, i, j);
            else if (j == i)
                U.set_element(1.0, i, j);
            else {
                double sum = 0.0;
                for (int k = 0; k < i; k++)
                    sum += (L.get_element(i, k) * U.get_element(k, j)) / L.get_element(i, i);
                double val = (this->get_element(i, j) / L.get_element(i, i)) - sum;
                U.set_element(val, i, j);
            }
        }
    }

    return result;
}


double Matrix::det(){
	// computing thedeterminant
	Matrix* p;
	p = new Matrix[2]; 
	p = this->luDecomposition(); // LU decomposition
	
	int n = n_cols;
	double result = 1;

	for (int i=0; i<n; i++){
		result *= p[0].get_element(i, i);
	}
	return result; 
}


Matrix Matrix::cofactor() {
	// Cofactors are used to build the adjugate matrix (aka adjoint), which is necessary to compute the inverse of a matrix using the formula:
    if (n_rows != n_cols) {
        std::cerr << "Cofactor is only for square matrices." << std::endl;
        exit(EXIT_FAILURE);
    }

    int n = n_rows;
    Matrix cofactorMatrix(n, n);

    for (int p = 0; p < n; p++) {
        for (int q = 0; q < n; q++) {
            Matrix minorMatrix(n - 1, n - 1);
            int mi = 0;

            for (int i = 0; i < n; i++) {
                if (i == p) continue;
                int mj = 0;

                for (int j = 0; j < n; j++) {
                    if (j == q) continue;
                    minorMatrix.set_element(this->get_element(i, j), mi, mj);
                    mj++;
                }
                mi++;
            }

            double sign = ((p + q) % 2 == 0) ? 1.0 : -1.0;
            double detMinor = minorMatrix.det();
            cofactorMatrix.set_element(sign * detMinor, p, q);
        }
    }

    return cofactorMatrix;
}

Matrix Matrix::inverse() {
    double d = this->det(); // here the pointer this is calling the det() method and compute it on the matrix instance itself
    if (fabs(d) < 1e-9) {
        std::cerr << "Matrix is singular and cannot be inverted." << std::endl;
        exit(EXIT_FAILURE);
    }

    Matrix cof = this->cofactor();
    Matrix adj = cof.T(); // Adjugate = Transpose of Cofactor

    Matrix inv(n_rows, n_cols);
    for (int i = 0; i < n_rows; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            inv.set_element(adj.get_element(i, j) / d, i, j);
        }
    }

    return inv;
}

// Element operations

double Matrix::mean() {
    double result = 0;
    int rows, cols;
    rows = this -> get_nrows();
    cols = this -> get_ncolumns();

    for(int i=0; i<n_rows;i++){
        for(int j=0; j<n_cols;j++){
            result += this -> get_element(i, j);
        }
    }
    return result/(rows*cols);
}

Matrix Matrix::mean(int axis) {
    int cols, rows;
    // double x = 0;
    rows = this -> get_nrows();
    cols = this -> get_ncolumns();
    if (axis==0){
        Matrix result(1, rows);
        for(int i=0; i<rows; i++){
            double mean_row = 0;
            for(int j=0; j<cols; j++){
                mean_row += this->get_element(i, j);
            }
            mean_row = (double) mean_row/cols;
            result.set_element(mean_row, 0, i);
        }
         return result;
    }
    else if(axis==1) {
        Matrix result(1, cols);
        for(int j=0; j<cols; j++){
            double mean_col = 0;
            for(int i=0; i<rows; i++){
                mean_col += this->get_element(i, j);
            }
            mean_col = (double) mean_col/cols;
            result.set_element(mean_col, 0, j);
        }
        return result;
    }
    else{
        throw std::invalid_argument( "inputs only 0 (mean by row), 1 (mean by column)" );
    }
}
