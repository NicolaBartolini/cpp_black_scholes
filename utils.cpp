#include "utils.hpp"
#include "Matrix.hpp"

double linear_interpolation(double x, double x1, double x2, double y1, double y2){
    double m;
    m = (y2-y1)/(x2-x1);
    return y1  + m*(x-x1);
}

double quantile(Matrix M, double q) {
    if (q < 0.0 || q > 1.0)
        throw std::invalid_argument("q must be in [0,1]");

    Matrix A = M.flatten();
    A.sort();

    int n = A.get_ncolumns();

    if (q == 0.0)
        return A.get_element(0, 0);

    if (q == 1.0)
        return A.get_element(0, n - 1);

    for (int i = 1; i < n; i++) {
        double p = static_cast<double>(i) / n;
        double u = static_cast<double>(i - 1) / n;

        if (q <= p) {
            double x = A.get_element(0, i - 1);
            double y = A.get_element(0, i);
            return linear_interpolation(q, u, p, x, y);
        }
    }

    // safety fallback
    return A.get_element(0, n - 1);
}


// double quantile(Matrix M, double q) {
//     int n_rows, n_cols;
//     Matrix A = M.flatten();
    
//     n_rows = M.get_nrows();
//     n_cols = M.get_ncolumns();
    
//     A.sort();

//     double p, u;
//     double x, y, z;

//     if(q==0){
//         return A.get_element(0,0);
//     }

//     else if (q==1){
//         return A.get_element(0, n_rows*n_cols-1);
//     }
//     else{
//         for(int i=1; i<n_rows*n_cols; i++){
//             p = (double) i/(n_rows*n_cols);
//             u = (double) (i-1)/(n_rows*n_cols);
//             if (p>q){
//                 x = A.get_element(0,i-1);
//                 y = A.get_element(0,i);
//                 z = linear_interpolation(q, u, p, x, y);
//                 return z;
//             } 
//         }
//     }
// }

// void bubbleSort(int arr[], int n) {
//     for (int i = 0; i < n - 1; i++) {
//         for (int j = 0; j < n - i - 1; j++) {
          
//             // Swap if the element found is
//           	// greater than the next element
//             if (arr[j] > arr[j + 1]) 
//                 swap(arr[j],arr[j+1]);
//         }
//     }
// }