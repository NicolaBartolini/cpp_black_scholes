#include <iostream>
#include "Matrix.hpp"  // Include the Matrix header file

int main() {
    // Create a 2x2 matrix A
    Matrix A(2, 2);
    A.set_element(4.0, 0, 0); // Set A[0][0]
    A.set_element(7.0, 0, 1); // Set A[0][1]
    A.set_element(2.0, 1, 0); // Set A[1][0]
    A.set_element(6.0, 1, 1); // Set A[1][1]

    std::cout << "Matrix A:" << std::endl;
    A.print();  // Print matrix A

    // Compute the inverse of A
    Matrix invA = A.inverse();

    std::cout << "Inverse of Matrix A:" << std::endl;
    invA.print();  // Print the inverse of matrix A

    return 0;
}

// compile: g++ main_matrix_test.cpp Matrix.cpp -o matrix_program
