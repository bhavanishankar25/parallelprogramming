#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
time_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}


int main()
{
	  int i;
    startTime = clock();
    double a[100000];
    double b[100000];
    double c[100000];

    for(int i = 0; i < 100000; i++)
    {
        a[i] = (long double)(rand()%100000000+10000)/10000;
        b[i] = (long double)(rand()%100000000+10000)/10000;
    }
        for (i = 0; i < 100000; i++)
    {
        c[i] = a[i] * b[i];
    }
    printf("%lF\n",getCurrentTime());
}
