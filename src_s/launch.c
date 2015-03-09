#include <crcuda_server.h>
#include <fatBinaryCtl.h>

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

void crcudaGetLastError(crcuda_message* msg, int sd){

  msg->data.getLastError.res
    = crcuda.crcudaGetLastError();

  SEND(msg, sd);
}

void crcudaDeviceReset(crcuda_message* msg, int sd){
  
  msg->data.deviceReset.res
    = crcuda.crcudaDeviceReset();

  SEND(msg, sd);

}

void crcudaGetDeviceProperties(crcuda_message* msg, int sd){
  
  struct cudaDeviceProp prop;
  int device;
  
  device = msg->data.getDeviceProperties.device;

  msg->data.getDeviceProperties.res =
    crcuda.crcudaGetDeviceProperties(&prop, device);

  msg->data.getDeviceProperties.prop = prop;

  SEND(msg, sd);
}

void crcudaSetDeviceFlags(crcuda_message* msg, int sd){

  unsigned int flags;
  
  flags = msg->data.setDeviceFlags.flags;

  msg->data.setDeviceFlags.res = 
    crcuda.crcudaSetDeviceFlags(flags);

  SEND(msg, sd);
}

