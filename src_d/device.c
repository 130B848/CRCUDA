#include <crcuda_server.h>
#include <fatBinaryCtl.h>

void crcudaMalloc(crcuda_message* msg, int sd){

  void* ptr;

  msg->data.malloc.res    = crcuda.crcudaMalloc((void**)&ptr, msg->data.malloc.size);
  msg->data.malloc.devPtr = ptr;

  printf("\tres    : %d\n", msg->data.malloc.res);
  printf("\tsize   : %d\n", msg->data.malloc.size);
  printf("\tdevPtr : %p\n", ptr);

  SEND(msg, sd);
}

void crcudaFree(crcuda_message* msg, int sd){

  msg->data.free.res
    = crcuda.crcudaFree(msg->data.free.devPtr);

  SEND(msg, sd);
}

void crcudaMemcpy(crcuda_message* msg, int sd){
  
  if(msg->data.memcpy.kind == cudaMemcpyHostToDevice){

    RECV_BUFF(msg->data.memcpy.count, sd);

    msg->data.memcpy.res = 
      crcuda.crcudaMemcpy(msg->data.memcpy.dst,
			  buff_recv,
			  msg->data.memcpy.count, 
			  msg->data.memcpy.kind);

    SEND(msg, sd);

  }else{
    
    msg->data.memcpy.res
      = crcuda.crcudaMemcpy(buff_send,
			    msg->data.memcpy.src,
			    msg->data.memcpy.count,
			    msg->data.memcpy.kind);
    
    SEND_BUFF(msg->data.memcpy.count, sd);
    SEND(msg, sd);
    
  }
}
