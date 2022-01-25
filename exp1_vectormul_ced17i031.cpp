#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
time_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

void Mul (int n,double a[] ,double b[], double c[])
{
    unsigned i;

    #pragma omp parallel for shared (a,b,c,n) private(i) schedule(static)
    for (i = 0; i < n; ++i)
    {
        c[i] = a[i] * b[i];
    }
}

int main(int argc, char* argv[])
{


    startTime = clock();
    double a[100000];
    double b[100000];
    double c[100000];

    for(int i = 0; i < 100000; i++)
    {
        a[i] = (long double)(rand()%100000000+10000)/10000;
        b[i] = (long double)(rand()%100000000+10000)/10000;
    }
    Mul(100000,a,b,c);
    int n = 10;
    printf("%lF\n",getCurrentTime());
}
