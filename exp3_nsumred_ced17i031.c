#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREAD 24

int main()
{

	int size=1039000;
    double a[size], sum=0;
    int i, id, threads;

    omp_set_num_threads(NUM_THREAD);
    double start, finish;


    for(int i=0; i<size; i++)
    {
        a[i]=(double)rand()/RAND_MAX*20000000.0-10000000.0;
    }


    start = omp_get_wtime();


    #pragma omp parallel for reduction(+:sum)

    	for(i=0; i<size; i++)
    		{
    			sum = sum + a[i];
    		}




    finish = omp_get_wtime();

    printf("%f",finish-start);
    return 0;
}
