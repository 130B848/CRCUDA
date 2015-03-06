#include <cuda_runtime_api.h>
#include <stdio.h>

int main(){

  cudaStream_t s;
  cudaError_t res;

  res = cudaStreamCreate(&s);
  
  printf("res : %d\n", res);

  res = cudaStreamDestroy(s);

  printf("res : %d\n", res);

  return 0;
}
