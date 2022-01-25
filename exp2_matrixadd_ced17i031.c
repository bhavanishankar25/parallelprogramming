#include <stdio.h>
#include<stdlib.h>
#include <omp.h>

#define NUM_THREAD 24

int main()
{
	int size = 445;
	double a[size][size];
	double b[size][size];
    double c[size][size];

    for(int i=0; i<size; i++)
    {
    	for (int j=0; j<size; j++)
    	{
        a[i][j]=(double)rand()/RAND_MAX*20000000.0-10000000.0;
        b[i][j]=(double)rand()/RAND_MAX*20000000.0-10000000.0;
    	}
    }

    omp_set_num_threads(NUM_THREAD);
    double start, finish;

    start = omp_get_wtime();

    #pragma omp parallel
    {
        int i, id, threads, j;
        id = omp_get_thread_num();
        threads = omp_get_num_threads();

        for(i=id; i<size; i=i+threads)
        {
            for(j=0; j<size; j++)
            {
                c[i][j] = a[i][j] + b[i][j]; //
            }
        }
    }
    finish = omp_get_wtime();
    printf("%f",finish-start);
}
