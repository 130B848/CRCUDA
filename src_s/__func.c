#include <crcuda_server.h>
#include <fatBinaryCtl.h>

__fatBinC_Wrapper_t wrapper;

//char *hostFun;

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
  char *hostFun, *deviceFun, *deviceName;
  //  char *deviceFun, *deviceName;
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

void __crcudaRegisterVar(crcuda_message* msg, int sd){
  
  void **fatCubinHandle;
  char *hostVar, *deviceAddress, *deviceName;
  int ext, size, constant, global;
  int hostVar_size, deviceAddress_size, deviceName_size;

  fatCubinHandle     = msg->data.registerVar.fatCubinHandle;
  ext                = msg->data.registerVar.ext;
  size               = msg->data.registerVar.size;
  constant           = msg->data.registerVar.constant;
  global             = msg->data.registerVar.global;
  hostVar_size       = msg->data.registerVar.hostVar_size;
  deviceAddress_size = msg->data.registerVar.deviceAddress_size;
  deviceName_size    = msg->data.registerVar.deviceName_size;

  hostVar = (char*)malloc(msg->data.registerVar.hostVar_size);
  RECV_BUFF(hostVar_size, sd);
  memcpy(hostVar, buff_recv, hostVar_size);

  deviceAddress = (char*)malloc(msg->data.registerVar.deviceAddress_size);
  RECV_BUFF(deviceAddress_size, sd);
  memcpy(deviceAddress, buff_recv, deviceAddress_size);

  deviceName = (char*)malloc(msg->data.registerVar.deviceName_size);
  RECV_BUFF(deviceName_size, sd);
  memcpy(deviceName, buff_recv, deviceName_size);

  crcuda.__crcudaRegisterVar(fatCubinHandle,
			     hostVar,
			     deviceAddress,
			     (const char*)deviceName,
			     ext,
			     size,
			     constant,
			     global);

  SEND(msg, sd);

}

void __crcudaUnregisterFatBinary(crcuda_message* msg, int sd){

  crcuda.__crcudaUnregisterFatBinary(msg->data.unregisterFatBinary.fatCubinHandle);

  SEND(msg, sd);

}
