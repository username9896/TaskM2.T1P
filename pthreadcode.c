#include <iostream>
#include <fstream>
#include <cstdlib>
#include <pthread.h>

using namespace std;

#define N 1000              // Size of matrices
#define NUM_THREADS 4       // Number of threads to use

int A[N][N], B[N][N], C[N][N];  // Matrices A, B, and C
int block_size;                 // Size of each block for block partitioning

struct thread_data {            // Struct for thread data
   int thread_id;              // Thread ID
   int row_start;              // Starting row for the thread
   int row_end;                // Ending row for the thread
};

void *matrix_multiply(void *threadarg) {
   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;

   // Perform matrix multiplication for assigned block of rows
   for (int i = my_data->row_start; i < my_data->row_end; i++) {
      for (int j = 0; j < N; j++) {
         for (int k = 0; k < N; k++) {
            C[i][j] += A[i][k] * B[k][j];
         }
      }
   }

   pthread_exit(NULL);
}

int main() {
   clock_t start_time = clock();
   block_size = N / NUM_THREADS;
   pthread_t threads[NUM_THREADS];
   struct thread_data td[NUM_THREADS];     // Create array of thread data structs

   // Initialize matrices A and B with random values
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         A[i][j] = rand() % 10;
         B[i][j] = rand() % 10;
      }
   }

   // Create output file stream
   ofstream output_file("output.txt");

   // Create threads and assign tasks to them
   int rc, row_start, row_end;
   for (int t = 0; t < NUM_THREADS; t++) {
      row_start = t * block_size;
      row_end = (t + 1) * block_size;
      td[t] = {t, row_start, row_end};    // Initialize thread data struct for this thread
      rc = pthread_create(&threads[t], NULL, matrix_multiply, (void *)&td[t]);   // Create thread
      if (rc) {
         cout << "Error: unable to create thread, " << rc << endl;
         exit(-1);
      }
   }
   
   clock_t end_time = clock();
  double execution_time = (static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC) * 1000000000;
  std::cout << "Execution time is - " << execution_time << " nanoseconds\n" <<std::endl;

   // Wait for all threads to complete
   for (int t = 0; t < NUM_THREADS; t++) {
      rc = pthread_join(threads[t], NULL);
      if (rc) {
         cout << "unable to connect with the thread, " << rc << endl;
         exit(-1);
      }
   }

   // Write output to file
   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         output_file << C[i][j] << " ";
      }
      output_file << endl;
   }

   // Close output file stream
   output_file.close();

   return 0;
}
