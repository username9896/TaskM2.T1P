#include <iostream>
#include <fstream>
#include <cstdlib>
#include <omp.h>

using namespace std;

#define N 1000              // Size of matrices

int A[N][N], B[N][N], C[N][N];  // Matrices A, B, and C

int main() {
   // Initialize matrices A and B with random values
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         A[i][j] = rand() % 10;
         B[i][j] = rand() % 10;
      }
   }

   // Create output file stream
   ofstream output_file("output.txt");

   // Perform matrix multiplication in parallel using OpenMP
   #pragma omp parallel for collapse(2)   // collapse is used to collapse the outer two loops for better performance
   for (int i = 0; i < N; i++) {     // i loop parallelized
      for (int j = 0; j < N; j++) {  // j loop parallelized
         for (int k = 0; k < N; k++) {
            C[i][j] += A[i][k] * B[k][j];  // matrix multiplication
         }
      }
   }

   // Write output to file
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         output_file << C[i][j] << " ";  // write C to file
      }
      output_file << endl;
   }

   // Close output file stream
   output_file.close();

   return 0;
}
