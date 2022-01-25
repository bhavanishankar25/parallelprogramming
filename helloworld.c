#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {

int omp_rank,omp_threads;
#pragma omp parallel private(omp_rank)
 {

 /* Obtain thread number */
 omp_rank = omp_get_thread_num();
 omp_threads=omp_get_num_threads();
 printf("Hello World from thread = %d\n" "of threads=%d",omp_rank,omp_threads );


 }

}
