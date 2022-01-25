#include<stdlib.h>
#include<stdio.h>
#include<omp.h>
#include<time.h>
#include <unistd.h>

#define NUM_THREAD 24

int main()
{
    int m=200,n=200,p=200;
    double a[m*n],b[n*p],c[m*p];

    for(int i=0,j=0;i<m*n,j<n*p;i++,j++)
    {
        a[i] = (double)rand()/RAND_MAX*2000.0000-1000.0000;
        b[j] = (double)rand()/RAND_MAX*2000.0000-1000.0000;
    }

    //omp_set_num_threads(NUM_THREAD);
    double time_spent = 0.0;

    clock_t begin = clock();
    #pragma omp parallel for shared(a,b,c)
          for(int j=0;j<p;j++)
        {
            for(int i=0;i<m;i++)
            {
                c[j*m + i]=0.0;
                for(int k=0;k<n;k++)
                {
                    c[j*m + i] += a[k*m + i]*b[j*n + k];
                }
            }
        }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%f\n",time_spent);
    return 0;
}
