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

void crcudaMemcpyAsync(crcuda_message* msg, int sd){
  
  if(msg->data.memcpyAsync.kind == cudaMemcpyHostToDevice){

    RECV_BUFF(msg->data.memcpyAsync.count, sd);

    msg->data.memcpyAsync.res = 
      crcuda.crcudaMemcpyAsync(msg->data.memcpyAsync.dst,
			       buff_recv,
			       msg->data.memcpyAsync.count,
			       msg->data.memcpyAsync.kind,
			       msg->data.memcpyAsync.stream);

    SEND(msg, sd);
    
  }else{

    printf("\tstream : %p\n", (void*)msg->data.memcpyAsync.stream);
    printf("\tsrc    : %p\n", msg->data.memcpyAsync.src);
    printf("\tkind   : %d\n", msg->data.memcpyAsync.kind);
    printf("\tcount  : %d\n", msg->data.memcpyAsync.count);
    
    msg->data.memcpyAsync.res
      = crcuda.crcudaMemcpyAsync(buff_send,
				 msg->data.memcpyAsync.src,
				 msg->data.memcpyAsync.count,
				 msg->data.memcpyAsync.kind,
				 msg->data.memcpyAsync.stream);

    SEND_BUFF(msg->data.memcpyAsync.count, sd);
    SEND(msg, sd);

  }
}

void crcudaMemset(crcuda_message* msg, int sd){
  
  msg->data.memset.res = 
    crcuda.crcudaMemset(msg->data.memset.devPtr,
			msg->data.memset.value,
			msg->data.memset.count);

  SEND(msg, sd);

}
