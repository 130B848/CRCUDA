#include <crcuda_server.h>
#include <fatBinaryCtl.h>

__fatBinC_Wrapper_t wrapper;

char *hostFun;

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

void crcudaConfigureCall(crcuda_message* msg, int sd){

#if 0
  printf("\tgridDim.x  : %d\n", msg->data.configureCall.gridDim.x);
  printf("\tgridDim.y  : %d\n", msg->data.configureCall.gridDim.y);
  printf("\tgridDim.z  : %d\n", msg->data.configureCall.gridDim.z);
  printf("\tblockDim.x : %d\n", msg->data.configureCall.blockDim.x);
  printf("\tblockDim.y : %d\n", msg->data.configureCall.blockDim.y);
  printf("\tblockDim.z : %d\n", msg->data.configureCall.blockDim.z);
  printf("\tsharedMem  : %d\n", msg->data.configureCall.sharedMem);
#endif
  
  msg->data.configureCall.res =
    crcuda.crcudaConfigureCall(msg->data.configureCall.gridDim,
			       msg->data.configureCall.blockDim,
			       msg->data.configureCall.sharedMem,
			       NULL); //* STREAM *//

  SEND(msg, sd);

}

void crcudaSetupArgument(crcuda_message* msg, int sd){

  size_t size, offset;
  void* arg;

  size   = msg->data.setupArgument.size;
  offset = msg->data.setupArgument.offset;

  printf("\tsize   : %d\n", size);
  printf("\toffset : %d\n", offset);

  arg = malloc(size+offset);

  RECV_BUFF(size+offset, sd);
  memcpy(arg, buff_recv, size+offset);

  msg->data.setupArgument.res
    = crcuda.crcudaSetupArgument(arg, size, offset);

  SEND(msg, sd);

}

void crcudaLaunch(crcuda_message* msg, int sd){

  int   size;
  void* func;

  size = msg->data.launch.size;

  RECV_BUFF(size, sd);
  
  func = malloc(size);
  memcpy(func, buff_recv, size);

  //  printf("get_kernel(func) : %s\n", get_kernel(func));

  msg->data.launch.res
    //    = crcuda.crcudaLaunch((const void*)func);
    //    = crcuda.crcudaLaunch((const void*)hostFun);
    = crcuda.crcudaLaunch(get_kernel(func));
  
  //  printf("\tfunc : %s\n", (char*)func);
  //  printf("\tres  : %d\n", msg->data.launch.res);
  
  SEND(msg, sd);
}

void __crcudaRegisterFatBinary(crcuda_message* msg, int sd){

  struct fatBinaryHeader header;
  void* fatBin;
  int recv_size;
  
  header  = msg->data.registerFatBinary.header;
  wrapper = msg->data.registerFatBinary.wrapper;

  recv_size = header.headerSize + header.fatSize;

  RECV_BUFF(recv_size, sd);

  fatBin = (void*)malloc(recv_size);

  memcpy(fatBin, buff_recv, recv_size);
  
  wrapper.data = (const unsigned long long*)fatBin;

  msg->data.registerFatBinary.fatCubinHandle
    = crcuda.__crcudaRegisterFatBinary(&wrapper);

  printf("sended\n");

  SEND(msg, sd);

}

void __crcudaRegisterFunction(crcuda_message* msg, int sd){

  void **fatCubinHandle;
  //  char *hostFun, *deviceFun, *deviceName;
  char *deviceFun, *deviceName;
  int hostFun_size, deviceFun_size, deviceName_size;
  int thread_limit;
  uint3 *tid, *bid;
  dim3 *bDim, *gDim;
  int *wSize;

  fatCubinHandle  = msg->data.registerFunction.fatCubinHandle;
  thread_limit    = msg->data.registerFunction.thread_limit;
  hostFun_size    = msg->data.registerFunction.hostFun_size;
  deviceFun_size  = msg->data.registerFunction.deviceFun_size;
  deviceName_size = msg->data.registerFunction.deviceName_size;

  hostFun = (char*)malloc(hostFun_size);
  RECV_BUFF(hostFun_size, sd);
  memcpy(hostFun, buff_recv, hostFun_size);

  deviceFun = (char*)malloc(deviceFun_size);
  RECV_BUFF(deviceFun_size, sd);
  memcpy(deviceFun, buff_recv, deviceFun_size);

  deviceName = (char*)malloc(deviceName_size);
  RECV_BUFF(deviceName_size, sd);
  memcpy(deviceName, buff_recv, deviceName_size);

#if 0
  printf("\thostFun    : %s\n", hostFun);
  printf("\tdeviceFun  : %s\n", deviceFun);
  printf("\tdeviceName : %s\n", deviceName);
#endif

  crcuda.__crcudaRegisterFunction(fatCubinHandle,
				  (const char*)hostFun,
				  deviceFun,
				  (const char*)deviceName,
				  thread_limit,
				  tid,
				  bid,
				  bDim,
				  gDim,
				  wSize);

  add_kernel(hostFun);

  SEND(msg, sd);
}

void __crcudaUnregisterFatBinary(crcuda_message* msg, int sd){

  crcuda.__crcudaUnregisterFatBinary(msg->data.unregisterFatBinary.fatCubinHandle);

  SEND(msg, sd);

}
