#include <iostream>
#include <fstream> // Required for file output
#include <cstdlib> // Required for rand() and srand()
#include <ctime> // Required for time()

using namespace std;

int main() {
  const int N = 10; // Size of matrices
  int A[N][N], B[N][N], C[N][N]; // Declare matrices A, B and C

  // Initialize matrices A and B with random values
  srand(time(nullptr)); // Seed the random number generator with the current time
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = rand() % 100; // set the random values to A
      B[i][j] = rand() % 100; // set the random values to B
    }
  }

  // Perform matrix multiplication of each element with another
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      C[i][j] = 0;                          // Initialize C[i][j] to 0
      for (int k = 0; k < N; k++) {
        C[i][j] += A[i][k] * B[k][j]; 
      }
    }
  }

  // Write output to file
  ofstream output_file("output.txt"); // Create an output file stream named "output.txt"
  if (!output_file.is_open()) { // Check if the file was successfully opened
    cerr << "Unable to open the file\n"; // Print an error message to the console if the file could not be opened
    return 1; // Return with an error code
  }
  for (int i = 0; i < N; i++) { // Iterate over each row of C
    for (int j = 0; j < N; j++) { // Iterate over each column of C
      output_file << C[i][j] << " "; // Write the element at row i and column j of C to the file, followed by a space
    }
    output_file << endl;
  }
  output_file.close(); // Close the output file stream
  return 0;
}
