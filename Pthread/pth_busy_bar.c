/* File:  
 *    pth_busy_bar.c
 *
 * Purpose:
 *    Use busy wait barriers to synchronize threads.
 *
 * Input:
 *    none
 * Output:
 *    Time for BARRIER_COUNT barriers
 *
 * Compile:
 *    gcc -g -Wall -o pth_busy_bar pth_busy_bar.c -lpthread
 * Usage:
 *    ./pth_busy_bar <thread_count>
 *
 * Note:
 *    Compile flag DEBUG will print a message after each barrier    
 *
 * IPP:   Section 4.8.1 (p. 177)
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

#define BARRIER_COUNT 100

int thread_count;
int barrier_thread_counts[BARRIER_COUNT];
//double* A;
double* x;
int sum;
pthread_mutex_t barrier_mutex;

void Usage(char* prog_name);
//void Gen_Matrix(double A[]);
void Gen_Vector(double x[]);
void *Thread_work(void* rank);

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread, i;
   pthread_t* thread_handles; 
   double start, finish;
   
   //y = malloc(500*sizeof(double));


   if (argc != 2)
      Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);
   

   thread_handles = malloc (thread_count*sizeof(pthread_t));
  // A = malloc(500*500*sizeof(double));
   x = malloc(500*sizeof(double));
   //Gen_Matrix(A);
   Gen_Vector(x);
   for (i = 0; i < BARRIER_COUNT; i++)
      barrier_thread_counts[i] = 0;
   pthread_mutex_init(&barrier_mutex, NULL);

   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], NULL,
          Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) {
      pthread_join(thread_handles[thread], NULL);
   }
   GET_TIME(finish); 
   printf("Tiempo general del programa  = %f seconds\n", finish - start);

   pthread_mutex_destroy(&barrier_mutex);
   free(thread_handles);
   return 0;
}  /* main */


/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */


/*-------------------------------------------------------------------
 * Function:    Thread_work
 * Purpose:     Run BARRIER_COUNT barriers
 * In arg:      rank
 * Global var:  thread_count, barrier_thread_counts, barrier_mutex
 * Return val:  Ignored
 */


void Gen_Vector(double x[]){
   int i;
   for(i=0 ;i<512;i++){
      x[i] = random()/((double) RAND_MAX);
   }
}



void *Thread_work(void* rank){

#  ifdef DEBUG
   long my_rank = (long) rank; 
#  endif
   long my_rank = (long) rank; 
   int i;
   double start,finish;
   sum=0;
   
    GET_TIME(start);
   for (i = 0; i < BARRIER_COUNT; i++) {
      pthread_mutex_lock(&barrier_mutex);
      barrier_thread_counts[i]++;

      for(int i=0;i<512;i++){
         sum += x[i]+x[i];
      }      

      pthread_mutex_unlock(&barrier_mutex);
      while (barrier_thread_counts[i] < thread_count);  //busy waiting
#     ifdef DEBUG
      if (my_rank == 0) {
         printf("All threads entered barrier %d\n", i);
         fflush(stdout);
      }
#     endif
   }
   GET_TIME(finish);
   printf("Thread %ld > Elapsed time = %f seconds\n", 
      my_rank, finish - start);

   return NULL;
} /* Thread_work */


