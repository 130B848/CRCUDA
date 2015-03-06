#ifndef IDEN_H
#define IDEN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/un.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#include <driver_types.h>
#include <cuda_runtime_api.h>
#include <vector_types.h>
#include <signal.h>
#include <__cudaFatFormat.h>
#include <fatBinaryCtl.h>
#include <fatbinary.h>

typedef struct{
  cudaError_t res;
  void* devPtr;
  size_t size;
} Malloc;

typedef struct{
  cudaError_t res;
  void* devPtr;
} Free;

typedef struct{
  cudaError_t res;
  void* dst;
  void* src;
  size_t count;
  enum cudaMemcpyKind kind;
} Memcpy;

typedef struct{
  cudaError_t res;
  cudaStream_t stream;
} StreamCreate;

typedef struct{
  cudaError_t res;
  cudaStream_t stream;
} StreamDestroy;

typedef struct{
  void** fatCubinHandle;
  __fatBinC_Wrapper_t wrapper;
  struct fatBinaryHeader header;
} RegisterFatBinary;

typedef struct{
  void** fatCubinHandle;
} UnregisterFatBinary;

typedef struct{
  void** fatCubinHandle;
  //const char* hostFun;
  int hostFun_size;
  //char* deviceFun;
  int deviceFun_size;
  //const char* deviceName;
  int deviceName_size;

  int thread_limit;
  /*
  void* tid;
  void* bid;
  void* bDim;
  void* gDim;
  int*  wSize;
  */
} RegisterFunction;

typedef struct{
  void** fatCubinHandle;
  //char *hostVar;
  int hostVar_size;
  //char *deviceAddress;
  int deviceAddress_size;
  //char *deviceName;
  int deviceName_size;
  int ext;
  int size;
  int constant;
  int global;
} RegisterVar;

typedef struct{
  cudaError_t res;
  dim3 gridDim;
  dim3 blockDim;
  size_t sharedMem;
  //* STREAM *//
} ConfigureCall;

typedef struct{
  cudaError_t res;
  size_t size;
  size_t offset;
} SetupArgument;

typedef struct{
  cudaError_t res;
  int size;
} Launch;

typedef struct{
  cudaError_t res;
} GetLastError;

typedef struct{
  cudaError_t res;
} DeviceReset;

typedef struct{
  cudaError_t res;
  struct cudaDeviceProp prop;
  int device;
} GetDeviceProperties;

typedef struct{
  cudaError_t res;
  unsigned int flags;
} SetDeviceFlags;

typedef struct{
  void* ptr;
  size_t size;
  unsigned int flags;
} HostRegister;

typedef struct{
  void* ptr;
} HostUnregister;

typedef struct{
  void *devPtr;
  size_t pitch;
  size_t width;
  size_t height;
} MallocPitch;

typedef struct{
  struct cudaPitchedPtr pitchedDevPtr;
  struct cudaExtent extent;
} Malloc3D;

enum{
  MALLOC,
  MALLOCPITCH,
  MALLOC3D,
  FREE,
  MEMCPY,

  REGISTERFATBINARY,
  UNREGISTERFATBINARY,
  REGISTERFUNCTION,
  REGISTERVAR,
  HOSTREGISTER,
  HOSTUNREGISTER,

  CONFIGURECALL,
  SETUPARGUMENT,
  LAUNCH,
  GETLASTERROR,
  DEVICERESET,
  GETDEVICEPROPERTIES,
  SETDEVICEFLAGS,

  STREAMCREATE,
  STREAMDESTROY,
};

typedef struct _crcuda_message {

  unsigned int iden;

  union{
    //__func.c
    RegisterFatBinary registerFatBinary;
    RegisterFunction registerFunction;
    RegisterVar registerVar;
    UnregisterFatBinary unregisterFatBinary;
    //device.c
    Malloc malloc;
    Free free;
    Memcpy memcpy;
    //launch.c
    ConfigureCall configureCall;
    SetupArgument setupArgument;
    Launch launch;
    GetLastError getLastError;
    DeviceReset deviceReset;
    GetDeviceProperties getDeviceProperties;
    SetDeviceFlags setDeviceFlags;
    //stream.c
    StreamCreate streamCreate;
    StreamDestroy streamDestroy;
  } data;

} crcuda_message;

#endif
