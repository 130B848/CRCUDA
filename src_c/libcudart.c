#include <crcuda_client.h>
#include <fatBinaryCtl.h>
#include <fatbinary.h>

CRCUDA crcuda;

int initialized = 0;

void unsupported_function_calls(){
  printf("\tUNSUPPORTED FUNCTION CALLS\n");
  exit(-1);
}

__attribute__((constructor)) void init_crcuda(){

  if(initialized)return;

  connect_to_server();

  crcuda.cp = (context*)malloc(sizeof(context));

  crcuda.cp->d0 = (region*)malloc(sizeof(region));
  crcuda.cp->d1 = (region*)malloc(sizeof(region));
  crcuda.cp->d0->mode = crcuda.cp->d1->mode = -1;
  crcuda.cp->d0->next = crcuda.cp->d1;
  crcuda.cp->d1->prev = crcuda.cp->d0;
  crcuda.cp->d1->next = NULL;
  crcuda.cp->d0->prev = NULL;

  crcuda.cp->s0 = (crcuda_stream*)malloc(sizeof(crcuda_stream));
  crcuda.cp->s1 = (crcuda_stream*)malloc(sizeof(crcuda_stream));
  crcuda.cp->s0->mode = crcuda.cp->s1->mode = -1;
  crcuda.cp->s0->next = crcuda.cp->s1;
  crcuda.cp->s1->prev = crcuda.cp->s0;
  crcuda.cp->s1->next = NULL;
  crcuda.cp->s0->prev = NULL;

  crcuda.cp->e0 = (crcuda_event*)malloc(sizeof(crcuda_event));
  crcuda.cp->e1 = (crcuda_event*)malloc(sizeof(crcuda_event));
  crcuda.cp->e0->mode = crcuda.cp->e1->mode = -1;
  crcuda.cp->e0->next = crcuda.cp->e1;
  crcuda.cp->e1->prev = crcuda.cp->e0;
  crcuda.cp->e1->next = NULL;
  crcuda.cp->e0->prev = NULL;

  crcuda.cp->a0 = (apilog*)malloc(sizeof(apilog));
  crcuda.cp->a1 = (apilog*)malloc(sizeof(apilog));
  crcuda.cp->a0->next = crcuda.cp->a1;
  crcuda.cp->a1->prev = crcuda.cp->a0;
  crcuda.cp->a1->next = NULL;
  crcuda.cp->a0->prev = NULL;

  initialized = 1;

  return;

}

cudaError_t __cudaRegisterDeviceFunction(){

  TRACE("__cudaRegisterDeviceFunction");

  ENTER;

  UNSUPPORTED;

}

void __cudaMutexOperation(int lock){

  TRACE("__cudaMutexOperation");

  ENTER;

  UNSUPPORTED;
}



void __cudaTextureFetch(const void* tex,void* index,int integer,void* val){

  TRACE("__cudaTextureFetch");

  ENTER;

  UNSUPPORTED;

}

int __cudaSynchronizeThreads(void** one,void* two){

  TRACE("__cudaSynchronizeThreads");

  ENTER;

  UNSUPPORTED;

}

void __cudaRegisterShared(void** fatCubinHandle,void **devicePtr){

  TRACE("__cudaRegisterShared");

  ENTER;

  UNSUPPORTED;

}

void __cudaRegisterSharedVar(void** fatCubinHandle,void **devicePtr,size_t size,size_t alignment,int storage){

  TRACE("__cudaRegisterSharedVar");

  ENTER;

  UNSUPPORTED;

}

void** __cudaRegisterFatBinary(void* fatCubin){

  TRACE("__cudaRegisterFatBinary");

  ENTER;

  if(!initialized){init_crcuda();}

  __fatBinC_Wrapper_t*    wrapper;
  struct fatBinaryHeader* header;
  
  wrapper = (__fatBinC_Wrapper_t*)fatCubin;
  header  = (struct fatBinaryHeader*)wrapper->data;

  msg->iden = REGISTERFATBINARY;
  msg->data.registerFatBinary.header  = *header;
  msg->data.registerFatBinary.wrapper = *wrapper;

  SEND;
  SEND_BUFF((void*)wrapper->data, header->headerSize + header->fatSize);
  RECV;

  return msg->data.registerFatBinary.fatCubinHandle;

}

void __cudaUnregisterFatBinary(void** fatCubinHandle){

  TRACE("__cudaUnregisterFatBinary");

  ENTER;

  msg->iden = UNREGISTERFATBINARY;
  msg->data.unregisterFatBinary.fatCubinHandle = fatCubinHandle;

  SEND;
  RECV;
  
  LEAVE;

}

void __cudaRegisterVar(void** fatCubinHandle,char *hostVar,char *deviceAddress,const char *deviceName,int ext,int size,int constant,int global){

  TRACE("__cudaRegisterVar");

  ENTER;

  UNSUPPORTED;

  //  mocu_register_var(size);
  //  mocu_add_symbol(hostVar,deviceAddress,(char*)deviceName,ext,size,constant,global);

}

void __cudaRegisterTexture(void **fatCubinHandle,const struct textureReference *hostVar,const void **deviceAddress,const char *deviceName,int dim,int norm,int ext){

  TRACE("__cudaRegisterTexture");

  ENTER;

  UNSUPPORTED;

}

void __cudaRegisterSurface(void **fatCubinHandle,const struct surfaceReference *hostVar,const void **deviceAddress,const char *deviceName,int dim,int ext){

  TRACE("__cudaRegisterSurface");

  ENTER;

  UNSUPPORTED;

}

void __cudaRegisterFunction(void **fatCubinHandle,const char *hostFun,char *deviceFun,const char *deviceName,int thread_limit,uint3 *tid,uint3 *bid,dim3 *bDim,dim3 *gDim,int *wSize){

  TRACE("__cudaRegisterFunction");

  ENTER;

#if 0 
  printf("\thostFun      : %s\n", hostFun);
  printf("\tdeviceFun    : %s\n", deviceFun);
  printf("\tdeviceName   : %s\n", deviceName);
  printf("\tthread_limit : %d\n", thread_limit);
  printf("\ttid->x       : %d\n", tid->x);
  printf("\ttid->y       : %d\n", tid->y);
  printf("\ttid->z       : %d\n", tid->z);
  printf("\tbid->x       : %d\n", bid->x);
  printf("\tbid->y       : %d\n", bid->y);
  printf("\tbid->z       : %d\n", bid->z);
  printf("\tbDim->x      : %d\n", bDim->x);
  printf("\tbDim->y      : %d\n", bDim->y);
  printf("\tbDim->z      : %d\n", bDim->z);
  printf("\tgDim->x      : %d\n", gDim->x);
  printf("\tgDim->y      : %d\n", gDim->y);
  printf("\tgDim->z      : %d\n", gDim->z);
  printf("\twSize        : %d\n", *wSize);
#endif

  msg->iden = REGISTERFUNCTION;
  msg->data.registerFunction.fatCubinHandle = fatCubinHandle;
  msg->data.registerFunction.thread_limit   = thread_limit;

  int size;
  int hostFun_size, deviceFun_size, deviceName_size;

  size = 0;

  while(hostFun[size++] != '\0');

  hostFun_size = size;
  msg->data.registerFunction.hostFun_size = hostFun_size;
  size = 0;

  while(deviceFun[size++] != '\0');

  deviceFun_size = size;
  msg->data.registerFunction.deviceFun_size = deviceFun_size;
  size = 0;

  while(deviceName[size++] != '\0');

  deviceName_size = size;
  msg->data.registerFunction.deviceName_size = deviceName_size;

  SEND;
  SEND_BUFF((void*)hostFun, hostFun_size);
  SEND_BUFF((void*)deviceFun, deviceFun_size);
  SEND_BUFF((void*)deviceName, deviceName_size);
  RECV;

}

cudaError_t cudaDeviceReset(void){

  TRACE("cudaDeviceReset");

  ENTER;

  UNSUPPORTED;

  LEAVE;
  
}


cudaError_t cudaDeviceSynchronize(void){

  TRACE("cudaDeviceSynchronize");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceSetLimit(enum cudaLimit limit,  size_t value){

  TRACE("cudaDeviceSetLimit");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceGetLimit(size_t *pValue,  enum cudaLimit limit){

  TRACE("cudaDeviceGetLimit");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceGetCacheConfig(enum cudaFuncCache *pCacheConfig){

  TRACE("cudaDeviceGetCacheConfig");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceSetCacheConfig(enum cudaFuncCache cacheConfig){

  TRACE("cudaDeviceSetCacheConfig");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceGetSharedMemConfig(enum cudaSharedMemConfig *pConfig){

  TRACE("cudaDeviceGetSharedMemConfig");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceSetSharedMemConfig(enum cudaSharedMemConfig config){

  TRACE("cudaDeviceSetSharedMemConfig");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceGetByPCIBusId(int *device,  char *pciBusId){

  TRACE("cudaDeviceGetByPCIBusId");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceGetPCIBusId(char *pciBusId,  int len,  int device){

  TRACE("cudaDeviceGetPCIBusId");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaIpcGetEventHandle(cudaIpcEventHandle_t *handle,  cudaEvent_t event){

  TRACE("cudaIpcGetEventHandle");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaIpcOpenEventHandle(cudaEvent_t *event,  cudaIpcEventHandle_t handle){

  TRACE("cudaIpcOpenEventHandle");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaIpcGetMemHandle(cudaIpcMemHandle_t *handle,  void *devPtr){

  TRACE("cudaIpcGetMemHandle");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaIpcOpenMemHandle(void **devPtr,  cudaIpcMemHandle_t handle,  unsigned int flags){

  TRACE("cudaIpcOpenMemHandle");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaIpcCloseMemHandle(void *devPtr){

  TRACE("cudaIpcCloseMemHandle");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaThreadExit(void){

  TRACE("cudaThreadExit");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaThreadSynchronize(void){

  TRACE("cudaThreadSynchronize");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaThreadSetLimit(enum cudaLimit limit,  size_t value){

  TRACE("cudaThreadSetLimit");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaThreadGetLimit(size_t *pValue,  enum cudaLimit limit){

  TRACE("cudaThreadGetLimit");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaThreadGetCacheConfig(enum cudaFuncCache *pCacheConfig){

  TRACE("cudaThreadGetCacheConfig");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaThreadSetCacheConfig(enum cudaFuncCache cacheConfig){

  TRACE("cudaThreadSetCacheConfig");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetLastError(void){

  TRACE("cudaGetLastError");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaPeekAtLastError(void){

  TRACE("cudaPeekAtLastError");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


const char* cudaGetErrorString(cudaError_t error){

  TRACE("cudaGetErrorString");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetDeviceCount(int *count){

  TRACE("cudaGetDeviceCount");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetDeviceProperties(struct cudaDeviceProp *prop,  int device){

  TRACE("cudaGetDeviceProperties");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceGetAttribute(int *value,  enum cudaDeviceAttr attr,  int device){

  TRACE("cudaDeviceGetAttribute");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaChooseDevice(int *device,  const struct cudaDeviceProp *prop){

  TRACE("cudaChooseDevice");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaSetDevice(int device){

  TRACE("cudaSetDevice");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetDevice(int *device){

  TRACE("cudaGetDevice");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaSetValidDevices(int *device_arr,  int len){

  TRACE("cudaSetValidDevices");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaSetDeviceFlags( unsigned int flags ){

  TRACE("cudaSetDeviceFlags");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaStreamCreate(cudaStream_t *pStream){

  TRACE("cudaStreamCreate");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaStreamCreateWithFlags(cudaStream_t *pStream,  unsigned int flags){

  TRACE("cudaStreamCreateWithFlags");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaStreamDestroy(cudaStream_t iStream){

  TRACE("cudaStreamDestroy");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaStreamWaitEvent(cudaStream_t stream,  cudaEvent_t event,  unsigned int flags){

  TRACE("cudaStreamWaitEvent");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaStreamAddCallback(cudaStream_t stream, cudaStreamCallback_t callback,  void *userData,  unsigned int flags){

  TRACE("cudaStreamAddCallback");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}

cudaError_t cudaStreamSynchronize(cudaStream_t stream){

  TRACE("cudaStreamSynchronize");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaStreamQuery(cudaStream_t stream){

  TRACE("cudaStreamQuery");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}

cudaError_t cudaEventCreateWithFlags(cudaEvent_t *iEvent,  unsigned int flags){

  TRACE("cudaEventCreateWithFlags");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaEventCreate(cudaEvent_t *iEvent){

  TRACE("cudaEventCreate");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}

cudaError_t cudaEventRecord(cudaEvent_t iEvent,  cudaStream_t iStream ){

  TRACE("cudaEventRecord");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaEventQuery(cudaEvent_t event){

  TRACE("cudaEventQuery");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaEventSynchronize(cudaEvent_t event){

  TRACE("cudaEventSynchronize");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaEventDestroy(cudaEvent_t event){

  TRACE("cudaEventDestroy");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaEventElapsedTime(float *ms,  cudaEvent_t start,  cudaEvent_t end){

  TRACE("cudaEventElapsedTime");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaConfigureCall(dim3 gridDim,  dim3 blockDim,  size_t sharedMem ,  cudaStream_t stream ){

  TRACE("cudaConfigureCall");

  ENTER;

  msg->iden = CONFIGURECALL;
  msg->data.configureCall.gridDim = gridDim;
  msg->data.configureCall.blockDim = blockDim;
  msg->data.configureCall.sharedMem = sharedMem;
  //* STREAM *//

  printf("\tgridDim.x  : %d\n", gridDim.x);
  printf("\tgridDim.y  : %d\n", gridDim.y);
  printf("\tgridDim.z  : %d\n", gridDim.z);
  printf("\tblockDim.x : %d\n", blockDim.x);
  printf("\tblockDim.y : %d\n", blockDim.y);
  printf("\tblockDim.z : %d\n", blockDim.z);
  printf("\tsharedMem  : %d\n", sharedMem);

  SEND;
  RECV;

  LEAVE;

  printf("\tres : %d\n", msg->data.configureCall.res);

  return msg->data.configureCall.res;
}


cudaError_t cudaSetupArgument(const void *arg,  size_t size,  size_t offset){

  TRACE("cudaSetupArgument");

  ENTER;

  printf("\tsize   : %d\n", size);
  printf("\toffset : %d\n", offset);

  msg->iden = SETUPARGUMENT;
  msg->data.setupArgument.size = size;
  msg->data.setupArgument.offset = offset;

  SEND;
  SEND_BUFF((void*)arg, size+offset);
  RECV;

  LEAVE;

  printf("\tres    : %d\n", msg->data.setupArgument.res);

  return msg->data.setupArgument.res;

}


cudaError_t cudaFuncSetCacheConfig(const void *func,  enum cudaFuncCache cacheConfig){

  TRACE("cudaFuncSetCacheConfig");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaFuncSetSharedMemConfig(const void *func,  enum cudaSharedMemConfig config){

  TRACE("cudaFuncSetSharedMemConfig");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}

cudaError_t cudaLaunch(const void *func){

  TRACE("cudaLaunch");

  ENTER;

  printf("\tfunc : %p\n", func);
  printf("\tfunc : %s(char ?)\n", (char*)func);

  int size = 0;

  while( ((char*)func)[size++] != '\0');

  msg->iden = LAUNCH;
  msg->data.launch.size = size;

  SEND;
  SEND_BUFF((void*)func, size);
  RECV;

  LEAVE;

  return msg->data.launch.res;

}


cudaError_t cudaFuncGetAttributes(struct cudaFuncAttributes *attr,  const void *func){

  TRACE("cudaFuncGetAttributes");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaSetDoubleForDevice(double *d){

  TRACE("cudaSetDoubleForDevice");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaSetDoubleForHost(double *d){

  TRACE("cudaSetDoubleForHost");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}

cudaError_t cudaMalloc(void **devPtr,  size_t size){
  
  TRACE("cudaMalloc");

  ENTER;

  cudaError_t res;
  apilog* a;
  region* r;

  msg->iden = MALLOC;
  msg->data.malloc.size = size;
  
  SEND;
  RECV;

  res     = msg->data.malloc.res;
  *devPtr = msg->data.malloc.devPtr;

  a = (apilog*)malloc(sizeof(apilog));
  a->type = MALLOC;
  a->data.malloc.size = size;
  a->data.malloc.devPtr = *devPtr;
  a->prev = crcuda.cp->a1->prev;
  a->next = crcuda.cp->a1;
  a->prev->next = a;
  a->next->prev = a;
  
  r = (region*)malloc(sizeof(region));
  r->size = size;
  r->base = *devPtr;
  r->mode = 0;
  r->flag = 0;
  r->prev = crcuda.cp->d1->prev;
  r->next = crcuda.cp->d1;
  r->prev->next = r;
  r->next->prev = r;
  
  LEAVE;
  
  return res;

}


cudaError_t cudaMallocHost(void **ptr,  size_t size){

  TRACE("cudaMallocHost");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMallocPitch(void **devPtr,  size_t *pitch,  size_t width,  size_t height){

  TRACE("cudaMallocPitch");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMallocArray(cudaArray_t *array,  const struct cudaChannelFormatDesc *desc,  size_t width,  size_t height ,  unsigned int flags ){

  TRACE("cudaMallocArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaFree(void *devPtr){

  TRACE("cudaFree");

  ENTER;

  cudaError_t res;
  apilog *a;
  region *r;

  msg->iden = FREE;
  msg->data.free.devPtr = devPtr;

  SEND;
  RECV;

  res = msg->data.free.res;
  
  a = (apilog*)malloc(sizeof(apilog));
  a->type = FREE;
  a->data.free.devPtr = devPtr;
  a->prev = crcuda.cp->a1->prev;
  a->next = crcuda.cp->a1;
  a->prev->next = a;
  a->next->prev = a;
  
  r = crcuda.cp->d0->next;
  
  while(r->mode >= 0){
    if(r->base == devPtr){
      r->next->prev = r->prev;
      r->prev->next = r->next;
      free(r);
      break;
    }
    r = r->next;
  }
  
  LEAVE;
  
  return res;

}


cudaError_t cudaFreeHost(void *ptr){

  TRACE("cudaFreeHost");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaFreeArray(cudaArray_t array){

  TRACE("cudaFreeArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaFreeMipmappedArray(cudaMipmappedArray_t mipmappedArray){

  TRACE("cudaFreeMipmappedArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaHostAlloc(void **pHost,  size_t size,  unsigned int flags){

  TRACE("cudaHostAlloc");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaHostRegister(void *ptr,  size_t size,  unsigned int flags){

  TRACE("cudaHostRegister");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaHostUnregister(void *ptr){

  TRACE("cudaHostUnregister");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaHostGetDevicePointer(void **pDevice,  void *pHost,  unsigned int flags){

  TRACE("cudaHostGetDevicePointer");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaHostGetFlags(unsigned int *pFlags,  void *pHost){

  TRACE("cudaHostGetFlags");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMalloc3D(struct cudaPitchedPtr* pitchedDevPtr,  struct cudaExtent extent){

  TRACE("cudaMalloc3D");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMalloc3DArray(cudaArray_t *array,  const struct cudaChannelFormatDesc* desc,  struct cudaExtent extent,  unsigned int flags ){

  TRACE("cudaMalloc3DArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMallocMipmappedArray(cudaMipmappedArray_t *mipmappedArray,  const struct cudaChannelFormatDesc* desc,  struct cudaExtent extent,  unsigned int numLevels,  unsigned int flags ){

  TRACE("cudaMallocMipmappedArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetMipmappedArrayLevel(cudaArray_t *levelArray,  cudaMipmappedArray_const_t mipmappedArray,  unsigned int level){

  TRACE("cudaGetMipmappedArrayLevel");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy3D(const struct cudaMemcpy3DParms *p){

  TRACE("cudaMemcpy3D");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy3DPeer(const struct cudaMemcpy3DPeerParms *p){

  TRACE("cudaMemcpy3DPeer");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy3DAsync(const struct cudaMemcpy3DParms *p,  cudaStream_t stream ){

  TRACE("cudaMemcpy3DAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy3DPeerAsync(const struct cudaMemcpy3DPeerParms *p,  cudaStream_t stream ){

  TRACE("cudaMemcpy3DPeerAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemGetInfo(size_t *free,  size_t *total){

  TRACE("cudaMemGetInfo");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaArrayGetInfo(struct cudaChannelFormatDesc *desc,  struct cudaExtent *extent,  unsigned int *flags,  cudaArray_t array){

  TRACE("cudaArrayGetInfo");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy(void *dst,  const void *src,  size_t count,  enum cudaMemcpyKind kind){

  TRACE("cudaMemcpy");

  ENTER;
  
  msg->iden = MEMCPY;
  msg->data.memcpy.kind  = kind;
  msg->data.memcpy.count = count;
  msg->data.memcpy.dst = dst;
  msg->data.memcpy.src = (void*)src;

  if(kind == cudaMemcpyHostToDevice){

    SEND;
    SEND_BUFF((void*)src, count);
    RECV;
    
  }else{

    SEND;
    RECV_BUFF(dst, count);
    RECV;
    
  }

  LEAVE;

  return msg->data.memcpy.res;

}


cudaError_t cudaMemcpyPeer(void *dst,  int dstDevice,  const void *src,  int srcDevice,  size_t count){

  TRACE("cudaMemcpyPeer");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyToArray(cudaArray_t dst,  size_t wOffset,  size_t hOffset,  const void *src,  size_t count,  enum cudaMemcpyKind kind){

  TRACE("cudaMemcpyToArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyFromArray(void *dst,  cudaArray_const_t src,  size_t wOffset,  size_t hOffset,  size_t count,  enum cudaMemcpyKind kind){

  TRACE("cudaMemcpyFromArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyArrayToArray(cudaArray_t dst,  size_t wOffsetDst,  size_t hOffsetDst,  cudaArray_const_t src,  size_t wOffsetSrc,  size_t hOffsetSrc,  size_t count,  enum cudaMemcpyKind kind ){

  TRACE("cudaMemcpyArrayToArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy2D(void *dst,  size_t dpitch,  const void *src,  size_t spitch,  size_t width,  size_t height,  enum cudaMemcpyKind kind){

  TRACE("cudaMemcpy2D");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy2DToArray(cudaArray_t dst,  size_t wOffset,  size_t hOffset,  const void *src,  size_t spitch,  size_t width,  size_t height,  enum cudaMemcpyKind kind){

  TRACE("cudaMemcpy2DToArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}

cudaError_t cudaMemcpy2DFromArray(void *dst,  size_t dpitch,  cudaArray_const_t src,  size_t wOffset,  size_t hOffset,  size_t width,  size_t height,  enum cudaMemcpyKind kind){

  TRACE("cudaMemcpy2DFromArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy2DArrayToArray(cudaArray_t dst,  size_t wOffsetDst,  size_t hOffsetDst,  cudaArray_const_t src,  size_t wOffsetSrc,  size_t hOffsetSrc,  size_t width,  size_t height,  enum cudaMemcpyKind kind ){

  TRACE("cudaMemcpy2DArrayToArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyToSymbol(const void *symbol,  const void *src,  size_t count,  size_t offset ,  enum cudaMemcpyKind kind ){

  TRACE("cudaMemcpyToSymbol");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyFromSymbol(void *dst,  const void *symbol,  size_t count,  size_t offset ,  enum cudaMemcpyKind kind ){

  TRACE("cudaMemcpyFromSymbol");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyAsync(void *dst,  const void *src,  size_t count,  enum cudaMemcpyKind kind,  cudaStream_t iStream ){

  TRACE("cudaMemcpyAsync");

  ENTER;

  UNSUPPORTED;
    
  LEAVE;

}


cudaError_t cudaMemcpyPeerAsync(void *dst,  int dstDevice,  const void *src,  int srcDevice,  size_t count,  cudaStream_t stream ){

  TRACE("cudaMemcpyPeerAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyToArrayAsync(cudaArray_t dst,  size_t wOffset,  size_t hOffset,  const void *src,  size_t count,  enum cudaMemcpyKind kind,  cudaStream_t stream ){

  TRACE("cudaMemcpyToArrayAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyFromArrayAsync(void *dst,  cudaArray_const_t src,  size_t wOffset,  size_t hOffset,  size_t count,  enum cudaMemcpyKind kind,  cudaStream_t stream ){

  TRACE("cudaMemcpyFromArrayAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy2DAsync(void *dst,  size_t dpitch,  const void *src,  size_t spitch,  size_t width,  size_t height,  enum cudaMemcpyKind kind,  cudaStream_t stream ){

  TRACE("cudaMemcpy2DAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy2DToArrayAsync(cudaArray_t dst,  size_t wOffset,  size_t hOffset,  const void *src,  size_t spitch,  size_t width,  size_t height,  enum cudaMemcpyKind kind,  cudaStream_t stream ){

  TRACE("cudaMemcpy2DToArrayAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpy2DFromArrayAsync(void *dst,  size_t dpitch,  cudaArray_const_t src,  size_t wOffset,  size_t hOffset,  size_t width,  size_t height,  enum cudaMemcpyKind kind,  cudaStream_t stream ){

  TRACE("cudaMemcpy2DFromArrayAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyToSymbolAsync(const void *symbol,  const void *src,  size_t count,  size_t offset,  enum cudaMemcpyKind kind,  cudaStream_t stream ){

  TRACE("cudaMemcpyToSymbolAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemcpyFromSymbolAsync(void *dst,  const void *symbol,  size_t count,  size_t offset,  enum cudaMemcpyKind kind,  cudaStream_t stream ){

  TRACE("cudaMemcpyFromSymbolAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemset(void *devPtr,  int value,  size_t count){

  TRACE("cudaMemset");

  ENTER;

  UNSUPPORTED;
  
  LEAVE;

}


cudaError_t cudaMemset2D(void *devPtr,  size_t pitch,  int value,  size_t width,  size_t height){

  TRACE("cudaMemset2D");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemset3D(struct cudaPitchedPtr pitchedDevPtr,  int value,  struct cudaExtent extent){

  TRACE("cudaMemset3D");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemsetAsync(void *devPtr,  int value,  size_t count,  cudaStream_t stream ){

  TRACE("cudaMemsetAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemset2DAsync(void *devPtr,  size_t pitch,  int value,  size_t width,  size_t height,  cudaStream_t stream ){

  TRACE("cudaMemset2DAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaMemset3DAsync(struct cudaPitchedPtr pitchedDevPtr,  int value,  struct cudaExtent extent,  cudaStream_t stream ){

  TRACE("cudaMemset3DAsync");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetSymbolAddress(void **devPtr,  const void *symbol){

  TRACE("cudaGetSymbolAddress");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetSymbolSize(size_t *size,  const void *symbol){

  TRACE("cudaGetSymbolSize");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaPointerGetAttributes(struct cudaPointerAttributes *attributes,  const void *ptr){

  TRACE("cudaPointerGetAttributes");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceCanAccessPeer(int *canAccessPeer,  int device,  int peerDevice){

  TRACE("cudaDeviceCanAccessPeer");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceEnablePeerAccess(int peerDevice,  unsigned int flags){

  TRACE("cudaDeviceEnablePeerAccess");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDeviceDisablePeerAccess(int peerDevice){

  TRACE("cudaDeviceDisablePeerAccess");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGraphicsUnregisterResource(cudaGraphicsResource_t resource){

  TRACE("cudaGraphicsUnregisterResource");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGraphicsResourceSetMapFlags(cudaGraphicsResource_t resource,  unsigned int flags){

  TRACE("cudaGraphicsResourceSetMapFlags");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGraphicsMapResources(int count,  cudaGraphicsResource_t *resources,  cudaStream_t stream ){

  TRACE("cudaGraphicsMapResources");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGraphicsUnmapResources(int count,  cudaGraphicsResource_t *resources,  cudaStream_t stream ){

  TRACE("cudaGraphicsUnmapResources");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGraphicsResourceGetMappedPointer(void **devPtr,  size_t *size,  cudaGraphicsResource_t resource){

  TRACE("cudaGraphicsResourceGetMappedPointer");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGraphicsSubResourceGetMappedArray(cudaArray_t *array,  cudaGraphicsResource_t resource,  unsigned int arrayIndex,  unsigned int mipLevel){

  TRACE("cudaGraphicsSubResourceGetMappedArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGraphicsResourceGetMappedMipmappedArray(cudaMipmappedArray_t *mipmappedArray,  cudaGraphicsResource_t resource){

  TRACE("cudaGraphicsResourceGetMappedMipmappedArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetChannelDesc(struct cudaChannelFormatDesc *desc,  cudaArray_const_t array){

  TRACE("cudaGetChannelDesc");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


struct cudaChannelFormatDesc cudaCreateChannelDesc(int x,  int y,  int z,  int w,  enum cudaChannelFormatKind f){

  TRACE("cudaCreateChannelDesc");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaBindTexture(size_t *offset,  const struct textureReference *texref,  const void *devPtr,  const struct cudaChannelFormatDesc *desc,  size_t size ){

  TRACE("cudaBindTexture");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaBindTexture2D(size_t *offset,  const struct textureReference *texref,  const void *devPtr,  const struct cudaChannelFormatDesc *desc,  size_t width,  size_t height,  size_t pitch){

  TRACE("cudaBindTexture2D");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaBindTextureToArray(const struct textureReference *texref,  cudaArray_const_t array,  const struct cudaChannelFormatDesc *desc){

  TRACE("cudaBindTextureToArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaBindTextureToMipmappedArray(const struct textureReference *texref,  cudaMipmappedArray_const_t mipmappedArray,  const struct cudaChannelFormatDesc *desc){

  TRACE("cudaBindTextureToMipmappedArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaUnbindTexture(const struct textureReference *texref){

  TRACE("cudaUnbindTexture");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetTextureAlignmentOffset(size_t *offset,  const struct textureReference *texref){

  TRACE("cudaGetTextureAlignmentOffset");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetTextureReference(const struct textureReference **texref,  const void *symbol){

  TRACE("cudaGetTextureReference");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaBindSurfaceToArray(const struct surfaceReference *surfref,  cudaArray_const_t array,  const struct cudaChannelFormatDesc *desc){

  TRACE("cudaBindSurfaceToArray");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetSurfaceReference(const struct surfaceReference **surfref,  const void *symbol){

  TRACE("cudaGetSurfaceReference");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaCreateTextureObject(cudaTextureObject_t *pTexObject,  const struct cudaResourceDesc *pResDesc,  const struct cudaTextureDesc *pTexDesc,  const struct cudaResourceViewDesc *pResViewDesc){

  TRACE("cudaCreateTextureObject");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDestroyTextureObject(cudaTextureObject_t texObject){

  TRACE("cudaDestroyTextureObject");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetTextureObjectResourceDesc(struct cudaResourceDesc *pResDesc,  cudaTextureObject_t texObject){

  TRACE("cudaGetTextureObjectResourceDesc");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetTextureObjectTextureDesc(struct cudaTextureDesc *pTexDesc,  cudaTextureObject_t texObject){

  TRACE("cudaGetTextureObjectTextureDesc");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetTextureObjectResourceViewDesc(struct cudaResourceViewDesc *pResViewDesc,  cudaTextureObject_t texObject){

  TRACE("cudaGetTextureObjectResourceViewDesc");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaCreateSurfaceObject(cudaSurfaceObject_t *pSurfObject,  const struct cudaResourceDesc *pResDesc){

  TRACE("cudaCreateSurfaceObject");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDestroySurfaceObject(cudaSurfaceObject_t surfObject){

  TRACE("cudaDestroySurfaceObject");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetSurfaceObjectResourceDesc(struct cudaResourceDesc *pResDesc,  cudaSurfaceObject_t surfObject){

  TRACE("cudaGetSurfaceObjectResourceDesc");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaDriverGetVersion(int *driverVersion){

  TRACE("cudaDriverGetVersion");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaRuntimeGetVersion(int *runtimeVersion){

  TRACE("cudaRuntimeGetVersion");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}


cudaError_t cudaGetExportTable(const void **ppExportTable,  const cudaUUID_t *pExportTableId){

  TRACE("cudaGetExportTable");

  ENTER;

  UNSUPPORTED;

  LEAVE;

}
