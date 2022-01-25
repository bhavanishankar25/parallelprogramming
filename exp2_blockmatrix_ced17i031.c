#include <stdio.h>
#include<stdlib.h>
#include <omp.h>

#define NUM_THREAD 14
int main()
{


int n = 500;
    double a[n][n];
    double b[n][n];
    double c[n][n];

    for(int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
        a[i][j]=(double)rand()/RAND_MAX*20000000.0-10000000.0;
        b[i][j]=(double)rand()/RAND_MAX*20000000.0-10000000.0;
        }
    }


	int i, j;
		for(i = 0; i < n; i++)
	{
		for(j=0; j<n; j++)
		{
			c[i][j] = 0.0;
		}
	}



	 omp_set_num_threads(NUM_THREAD);
	 double start, finish;

    start = omp_get_wtime();


#pragma omp parallel

//The "#pragma omp for" advises the compiler to distribute the work load
// of the following loop within the team of threads which you have to create first.
	{


	int i,j,k,kk,jj, bb=5, n=500;
	double sum;




	#pragma omp for


	for(kk=0;kk<n; kk+=bb)
	{
		for(jj=0; jj<n; jj+=bb)
		{
			for(i=0; i<n; i++)
			{
				for(j=jj; j<jj+bb; j++)
				{
					sum = c[i][j];
					for(k=kk; k<kk+bb;k++)
					{
						sum+=a[i][k]*b[k][j];
					}
					c[i][j] = sum;
				}
			}
		}
	}


}


finish = omp_get_wtime();

    printf("%f",finish-start);






}
