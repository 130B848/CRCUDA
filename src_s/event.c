#include <crcuda_server.h>
#include <fatBinaryCtl.h>

void crcudaEventCreateWithFlags(crcuda_message* msg, int sd){
  
  cudaEvent_t event;
  cudaError_t res;

  res = crcuda.crcudaEventCreateWithFlags(&event, 
					  msg->data.eventCreateWithFlags.flags);

  msg->data.eventCreateWithFlags.res = res;
  msg->data.eventCreateWithFlags.event = event;

  SEND(msg, sd);

}

void crcudaEventRecord(crcuda_message* msg, int sd){
  
  cudaError_t res;

  res = crcuda.crcudaEventRecord(msg->data.eventRecord.event,
				 msg->data.eventRecord.stream);

  msg->data.eventRecord.res = res;

  SEND(msg, sd);

}

void crcudaEventSynchronize(crcuda_message* msg, int sd){

  cudaError_t res;

  res = crcuda.crcudaEventSynchronize(msg->data.eventSynchronize.event);

  msg->data.eventSynchronize.res = res;

  SEND(msg, sd);

}

void crcudaEventElapsedTime(crcuda_message* msg, int sd){
  
  cudaError_t res;

  res = crcuda.crcudaEventElapsedTime(&msg->data.eventElapsedTime.ms,
				      msg->data.eventElapsedTime.start,
				      msg->data.eventElapsedTime.end);

  printf("\tms : %f\n", msg->data.eventElapsedTime.ms);

  msg->data.eventElapsedTime.res = res;

  SEND(msg, sd);
  
}

void crcudaEventDestroy(crcuda_message* msg, int sd){

  cudaError_t res;

  res = crcuda.crcudaEventDestroy(msg->data.eventDestroy.event);

  msg->data.eventDestroy.res = res;

  SEND(msg, sd);

}
