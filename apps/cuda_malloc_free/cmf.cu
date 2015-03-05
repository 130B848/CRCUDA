#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cuda_runtime_api.h>

#define HAS_KERNEL 1
#define SIZE 512

#if HAS_KERNEL
__global__ void mykernel(float* t){
  
  int id = blockDim.x * blockIdx.x + threadIdx.x;

  t[id] = id*10.0f;

}

__global__ void mykernel2(float* t){
  
  int id = blockDim.x * blockIdx.x + threadIdx.x;

  t[id] = t[id]*2;

}
#endif

int main(){

  float* test;
  float* test_h;
  cudaError_t res;

  test_h = (float*)malloc(sizeof(float)*SIZE);

  for(int i = 0 ; i < SIZE ; i ++){
    test_h[i] = i;
  }

  res = cudaMalloc((void**)&test, sizeof(float) * SIZE);

  printf("cudaMalloc => : %d\n", res);

  res = cudaMemcpy(test, test_h, sizeof(float) * SIZE , cudaMemcpyHostToDevice);

  printf("cudaMemcpy => : %d(H to D)\n", res);

#if HAS_KERNEL
  dim3 threads(512, 1, 1);
  dim3 blocks(1, 1, 1);

  mykernel<<<blocks, threads>>>(test);
  mykernel2<<<blocks, threads>>>(test);
#endif

  res = cudaMemcpy(test_h, test, sizeof(float) * SIZE , cudaMemcpyDeviceToHost);

  printf("cudaMemcpy => : %d(D to H)\n", res);

  for(int i = 0 ; i < SIZE ; i ++){
    if(test_h[i] != i*10.0f*2){
      printf("Result check : Failed...\n");
      exit(-1);
      break;
    }
  }

  printf("Result check : OK!!\n");

  res = cudaFree(test);

  printf("cudaFree   => : %d\n", res);

  return 0;
}
