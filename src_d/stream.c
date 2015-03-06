#include <crcuda_server.h>
#include <fatBinaryCtl.h>

void crcudaStreamCreate(crcuda_message* msg, int sd){
  
  cudaStream_t stream;
  cudaError_t  res;

  res = crcuda.crcudaStreamCreate(&stream);

  msg->data.streamCreate.res = res;
  msg->data.streamCreate.stream = stream;

  SEND(msg, sd);
}

void crcudaStreamDestroy(crcuda_message* msg, int sd){
  
  cudaError_t  res;

  res = crcuda.crcudaStreamDestroy(msg->data.streamDestroy.stream);

  msg->data.streamDestroy.res = res;

  SEND(msg, sd);

}
