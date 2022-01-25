#include <stdio.h>
#include <omp.h>
#include<stdlib.h>

#define NUM_THREAD 24

int main()
{

	int size=519000;
    double a[size],b[size],tsum=0;

    omp_set_num_threads(NUM_THREAD);
    double start, finish;


    for(int i=0; i<size; i++)
    {
        a[i]=(double)rand()/RAND_MAX*20000000.0-10000000.0;
    }


    start = omp_get_wtime();

        int i, id, threads;
        id = omp_get_thread_num();
        threads = omp_get_num_threads();


    #pragma omp parallel
    {
        int sum = 0;
    	for(i=id; i<size; i+=threads)
    	{
            tsum = sum + (a[i]*b[i]);
        }

        #pragma omp critical
        {
            tsum = tsum + sum;
    	}
    }



    finish = omp_get_wtime();

    printf("%f",finish-start);
    return 0;
}
