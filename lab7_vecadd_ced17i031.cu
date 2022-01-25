%%cu
#include<bits/stdc++.h>
#include <cstdio> 
#include <iostream> 

__global__ void vecAdd( double *a,   double *b,  double *c, int n)
{
    int id = blockIdx.x*blockDim.x+threadIdx.x;
    int bs = blockDim.x;
    for (int k = id; k < n; k += bs) {
        c[k] = a[k] + b[k];
    }
    
}
 
int main( int argc, char* argv[] )
{
    int n = 100000000;
 
    
    double *h_a;
    double *h_b;
    double *h_c;
 
    double *d_a;
    double *d_b;
    double *d_c;
 
    size_t bytes = n*sizeof(double);
 
    h_a = (double*)malloc(bytes);
    h_b = (double*)malloc(bytes);
    h_c = (double*)malloc(bytes);
 
    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);
 
    int i;
    for( i = 0; i < n; i++ ) {
        h_a[i] = i*(double) rand() + 0.00001534784187571354923459*(double) rand();
        h_b[i] = i*(double) rand() + 0.00001534784187571354923459*(double) rand();
    }
 
    cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, bytes, cudaMemcpyHostToDevice);
 
    int blockSize =500;
    int gridSize =1;

 
    vecAdd<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);
 
    cudaMemcpy( h_c, d_c, bytes, cudaMemcpyDeviceToHost );
    //for(i=0; i<n; i++)
    //printf("%f\n, ", h_c[i]);
 
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
 
    free(h_a);
    free(h_b);
    free(h_c);
 
    return 0;
}