%%cu
#include<bits/stdc++.h>
#include <stdio.h> 
#include <iostream>

static const int arraySize = 100000000;
static const int blockSize = 500;
__global__ void sumarray(double *a, double *out) {
    int idx = threadIdx.x;
    double sum = 0;
    for (int i = idx; i < arraySize; i += blockSize)
        sum += a[i];
    __shared__ double r[blockSize];
    r[idx] = sum;
    __syncthreads();
    for (int size = blockSize/2; size>0; size/=2) { //uniform
        if (idx<size)
            r[idx] += r[idx+size];
        __syncthreads();
    }
    if (idx == 0)
        *out = r[0];
}


int main(){
    

    double *h_a;
    double *h_result;

    double *d_a;
    double *d_result;

    

    size_t bytes = arraySize*sizeof(double);

    h_a = (double*)malloc(bytes);
    h_result = (double*)malloc(bytes);

    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_result, bytes);

    int i;
    for( i = 0; i < arraySize; i++ ) {
        h_a[i] = i*(double) rand() + 0.00001534784187571354923459*(double) rand();
    }

    cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);

    int blockSize =500;
    int gridSize =1;

    sumarray<<< gridSize, blockSize >>>(d_a,d_result);

    cudaMemcpy( h_result, d_result, bytes, cudaMemcpyDeviceToHost );

    printf("%lf",h_result[0]);

    cudaFree(d_a);
    cudaFree(d_result);
 
    free(h_a);
    free(h_result);


    return 0;
}

