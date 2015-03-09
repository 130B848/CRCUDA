#include <iden.h>

typedef struct _cr_kernels{
  struct _cr_kernels *prev, *next;
  void* kernel;
} cr_kernels;

typedef struct _crcuda{

  cr_kernels *ck0, *ck1;

  cudaError_t (*crcudaDeviceReset)(void);
  cudaError_t (*crcudaDeviceSynchronize)(void);
  cudaError_t (*crcudaDeviceSetLimit)(enum cudaLimit limit,  size_t value);
  cudaError_t (*crcudaDeviceGetLimit)(size_t *pValue,  enum cudaLimit limit);
  cudaError_t (*crcudaDeviceGetCacheConfig)(enum cudaFuncCache *pCacheConfig);
  cudaError_t (*crcudaDeviceSetCacheConfig)(enum cudaFuncCache cacheConfig);
  cudaError_t (*crcudaDeviceGetSharedMemConfig)(enum cudaSharedMemConfig *pConfig);
  cudaError_t (*crcudaDeviceSetSharedMemConfig)(enum cudaSharedMemConfig config);
  cudaError_t (*crcudaDeviceGetByPCIBusId)(int *device,  char *pciBusId);
  cudaError_t (*crcudaDeviceGetPCIBusId)(char *pciBusId,  int len,  int device);
  cudaError_t (*crcudaIpcGetEventHandle)(cudaIpcEventHandle_t *handle,  cudaEvent_t event);
  cudaError_t (*crcudaIpcOpenEventHandle)(cudaEvent_t *event,  cudaIpcEventHandle_t handle);
  cudaError_t (*crcudaIpcGetMemHandle)(cudaIpcMemHandle_t *handle,  void *devPtr);
  cudaError_t (*crcudaIpcOpenMemHandle)(void **devPtr,  cudaIpcMemHandle_t handle,  unsigned int flags);
  cudaError_t (*crcudaIpcCloseMemHandle)(void *devPtr);
  cudaError_t (*crcudaThreadExit)(void);
  cudaError_t (*crcudaThreadSynchronize)(void);
  cudaError_t (*crcudaThreadSetLimit)(enum cudaLimit limit,  size_t value);
  cudaError_t (*crcudaThreadGetLimit)(size_t *pValue,  enum cudaLimit limit);
  cudaError_t (*crcudaThreadGetCacheConfig)(enum cudaFuncCache *pCacheConfig);
  cudaError_t (*crcudaThreadSetCacheConfig)(enum cudaFuncCache cacheConfig);
  cudaError_t (*crcudaGetLastError)(void);
  cudaError_t (*crcudaPeekAtLastError)(void);
  const char* (*crcudaGetErrorString)(cudaError_t error);
  cudaError_t (*crcudaGetDeviceCount)(int *count);
  cudaError_t (*crcudaGetDeviceProperties)(struct cudaDeviceProp *prop,  int device);
  cudaError_t (*crcudaDeviceGetAttribute)(int *value,  enum cudaDeviceAttr attr,  int device);
  cudaError_t (*crcudaChooseDevice)(int *device,  const struct cudaDeviceProp *prop);
  cudaError_t (*crcudaSetDevice)(int device);
  cudaError_t (*crcudaGetDevice)(int *device);
  cudaError_t (*crcudaSetValidDevices)(int *device_arr,  int len);
  cudaError_t (*crcudaSetDeviceFlags)( unsigned int flags );
  cudaError_t (*crcudaStreamCreate)(cudaStream_t *pStream);
  cudaError_t (*crcudaStreamCreateWithFlags)(cudaStream_t *pStream,  unsigned int flags);
  cudaError_t (*crcudaStreamDestroy)(cudaStream_t stream);
  cudaError_t (*crcudaStreamWaitEvent)(cudaStream_t stream,  cudaEvent_t event,  unsigned int flags);
  cudaError_t (*crcudaStreamAddCallback)(cudaStream_t stream, cudaStreamCallback_t callback,  void *userData,  unsigned int flags);
  cudaError_t (*crcudaStreamSynchronize)(cudaStream_t stream);
  cudaError_t (*crcudaStreamQuery)(cudaStream_t stream);
  cudaError_t (*crcudaEventCreate)(cudaEvent_t *event);
  cudaError_t (*crcudaEventCreateWithFlags)(cudaEvent_t *event,  unsigned int flags);
  cudaError_t (*crcudaEventRecord)(cudaEvent_t event,  cudaStream_t stream );
  cudaError_t (*crcudaEventQuery)(cudaEvent_t event);
  cudaError_t (*crcudaEventSynchronize)(cudaEvent_t event);
  cudaError_t (*crcudaEventDestroy)(cudaEvent_t event);
  cudaError_t (*crcudaEventElapsedTime)(float *ms,  cudaEvent_t start,  cudaEvent_t end);
  cudaError_t (*crcudaConfigureCall)(dim3 gridDim,  dim3 blockDim,  size_t sharedMem ,  cudaStream_t stream );
  cudaError_t (*crcudaSetupArgument)(const void *arg,  size_t size,  size_t offset);
  cudaError_t (*crcudaFuncSetCacheConfig)(const void *func,  enum cudaFuncCache cacheConfig);
  cudaError_t (*crcudaFuncSetSharedMemConfig)(const void *func,  enum cudaSharedMemConfig config);
  cudaError_t (*crcudaLaunch)(const void *func);
  cudaError_t (*crcudaFuncGetAttributes)(struct cudaFuncAttributes *attr,  const void *func);
  cudaError_t (*crcudaSetDoubleForDevice)(double *d);
  cudaError_t (*crcudaSetDoubleForHost)(double *d);
  cudaError_t (*crcudaMalloc)(void **devPtr,  size_t size);
  cudaError_t (*crcudaMallocHost)(void **ptr,  size_t size);
  cudaError_t (*crcudaMallocPitch)(void **devPtr,  size_t *pitch,  size_t width,  size_t height);
  cudaError_t (*crcudaMallocArray)(cudaArray_t *array,  const struct cudaChannelFormatDesc *desc,  size_t width,  size_t height ,  unsigned int flags );
  cudaError_t (*crcudaFree)(void *devPtr);
  cudaError_t (*crcudaFreeHost)(void *ptr);
  cudaError_t (*crcudaFreeArray)(cudaArray_t array);
  cudaError_t (*crcudaFreeMipmappedArray)(cudaMipmappedArray_t mipmappedArray);
  cudaError_t (*crcudaHostAlloc)(void **pHost,  size_t size,  unsigned int flags);
  cudaError_t (*crcudaHostRegister)(void *ptr,  size_t size,  unsigned int flags);
  cudaError_t (*crcudaHostUnregister)(void *ptr);
  cudaError_t (*crcudaHostGetDevicePointer)(void **pDevice,  void *pHost,  unsigned int flags);
  cudaError_t (*crcudaHostGetFlags)(unsigned int *pFlags,  void *pHost);
  cudaError_t (*crcudaMalloc3D)(struct cudaPitchedPtr* pitchedDevPtr,  struct cudaExtent extent);
  cudaError_t (*crcudaMalloc3DArray)(cudaArray_t *array,  const struct cudaChannelFormatDesc* desc,  struct cudaExtent extent,  unsigned int flags );
  cudaError_t (*crcudaMallocMipmappedArray)(cudaMipmappedArray_t *mipmappedArray,  const struct cudaChannelFormatDesc* desc,  struct cudaExtent extent,  unsigned int numLevels,  unsigned int flags );
  cudaError_t (*crcudaGetMipmappedArrayLevel)(cudaArray_t *levelArray,  cudaMipmappedArray_const_t mipmappedArray,  unsigned int level);
  cudaError_t (*crcudaMemcpy3D)(const struct cudaMemcpy3DParms *p);
  cudaError_t (*crcudaMemcpy3DPeer)(const struct cudaMemcpy3DPeerParms *p);
  cudaError_t (*crcudaMemcpy3DAsync)(const struct cudaMemcpy3DParms *p,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpy3DPeerAsync)(const struct cudaMemcpy3DPeerParms *p,  cudaStream_t stream );
  cudaError_t (*crcudaMemGetInfo)(size_t *free,  size_t *total);
  cudaError_t (*crcudaArrayGetInfo)(struct cudaChannelFormatDesc *desc,  struct cudaExtent *extent,  unsigned int *flags,  cudaArray_t array);
  cudaError_t (*crcudaMemcpy)(void *dst,  const void *src,  size_t count,  enum cudaMemcpyKind kind);
  cudaError_t (*crcudaMemcpyPeer)(void *dst,  int dstDevice,  const void *src,  int srcDevice,  size_t count);
  cudaError_t (*crcudaMemcpyToArray)(cudaArray_t dst,  size_t wOffset,  size_t hOffset,  const void *src,  size_t count,  enum cudaMemcpyKind kind);
  cudaError_t (*crcudaMemcpyFromArray)(void *dst,  cudaArray_const_t src,  size_t wOffset,  size_t hOffset,  size_t count,  enum cudaMemcpyKind kind);
  cudaError_t (*crcudaMemcpyArrayToArray)(cudaArray_t dst,  size_t wOffsetDst,  size_t hOffsetDst,  cudaArray_const_t src,  size_t wOffsetSrc,  size_t hOffsetSrc,  size_t count,  enum cudaMemcpyKind kind );
  cudaError_t (*crcudaMemcpy2D)(void *dst,  size_t dpitch,  const void *src,  size_t spitch,  size_t width,  size_t height,  enum cudaMemcpyKind kind);
  cudaError_t (*crcudaMemcpy2DToArray)(cudaArray_t dst,  size_t wOffset,  size_t hOffset,  const void *src,  size_t spitch,  size_t width,  size_t height,  enum cudaMemcpyKind kind);
  cudaError_t (*crcudaMemcpy2DFromArray)(void *dst,  size_t dpitch,  cudaArray_const_t src,  size_t wOffset,  size_t hOffset,  size_t width,  size_t height,  enum cudaMemcpyKind kind);
  cudaError_t (*crcudaMemcpy2DArrayToArray)(cudaArray_t dst,  size_t wOffsetDst,  size_t hOffsetDst,  cudaArray_const_t src,  size_t wOffsetSrc,  size_t hOffsetSrc,  size_t width,  size_t height,  enum cudaMemcpyKind kind );
  cudaError_t (*crcudaMemcpyToSymbol)(const void *symbol,  const void *src,  size_t count,  size_t offset ,  enum cudaMemcpyKind kind );
  cudaError_t (*crcudaMemcpyFromSymbol)(void *dst,  const void *symbol,  size_t count,  size_t offset ,  enum cudaMemcpyKind kind );
  cudaError_t (*crcudaMemcpyAsync)(void *dst,  const void *src,  size_t count,  enum cudaMemcpyKind kind,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpyPeerAsync)(void *dst,  int dstDevice,  const void *src,  int srcDevice,  size_t count,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpyToArrayAsync)(cudaArray_t dst,  size_t wOffset,  size_t hOffset,  const void *src,  size_t count,  enum cudaMemcpyKind kind,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpyFromArrayAsync)(void *dst,  cudaArray_const_t src,  size_t wOffset,  size_t hOffset,  size_t count,  enum cudaMemcpyKind kind,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpy2DAsync)(void *dst,  size_t dpitch,  const void *src,  size_t spitch,  size_t width,  size_t height,  enum cudaMemcpyKind kind,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpy2DToArrayAsync)(cudaArray_t dst,  size_t wOffset,  size_t hOffset,  const void *src,  size_t spitch,  size_t width,  size_t height,  enum cudaMemcpyKind kind,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpy2DFromArrayAsync)(void *dst,  size_t dpitch,  cudaArray_const_t src,  size_t wOffset,  size_t hOffset,  size_t width,  size_t height,  enum cudaMemcpyKind kind,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpyToSymbolAsync)(const void *symbol,  const void *src,  size_t count,  size_t offset,  enum cudaMemcpyKind kind,  cudaStream_t stream );
  cudaError_t (*crcudaMemcpyFromSymbolAsync)(void *dst,  const void *symbol,  size_t count,  size_t offset,  enum cudaMemcpyKind kind,  cudaStream_t stream );
  cudaError_t (*crcudaMemset)(void *devPtr,  int value,  size_t count);
  cudaError_t (*crcudaMemset2D)(void *devPtr,  size_t pitch,  int value,  size_t width,  size_t height);
  cudaError_t (*crcudaMemset3D)(struct cudaPitchedPtr pitchedDevPtr,  int value,  struct cudaExtent extent);
  cudaError_t (*crcudaMemsetAsync)(void *devPtr,  int value,  size_t count,  cudaStream_t stream );
  cudaError_t (*crcudaMemset2DAsync)(void *devPtr,  size_t pitch,  int value,  size_t width,  size_t height,  cudaStream_t stream );
  cudaError_t (*crcudaMemset3DAsync)(struct cudaPitchedPtr pitchedDevPtr,  int value,  struct cudaExtent extent,  cudaStream_t stream );
  cudaError_t (*crcudaGetSymbolAddress)(void **devPtr,  const void *symbol);
  cudaError_t (*crcudaGetSymbolSize)(size_t *size,  const void *symbol);
  cudaError_t (*crcudaPointerGetAttributes)(struct cudaPointerAttributes *attributes,  const void *ptr);
  cudaError_t (*crcudaDeviceCanAccessPeer)(int *canAccessPeer,  int device,  int peerDevice);
  cudaError_t (*crcudaDeviceEnablePeerAccess)(int peerDevice,  unsigned int flags);
  cudaError_t (*crcudaDeviceDisablePeerAccess)(int peerDevice);
  cudaError_t (*crcudaGraphicsUnregisterResource)(cudaGraphicsResource_t resource);
  cudaError_t (*crcudaGraphicsResourceSetMapFlags)(cudaGraphicsResource_t resource,  unsigned int flags);
  cudaError_t (*crcudaGraphicsMapResources)(int count,  cudaGraphicsResource_t *resources,  cudaStream_t stream );
  cudaError_t (*crcudaGraphicsUnmapResources)(int count,  cudaGraphicsResource_t *resources,  cudaStream_t stream );
  cudaError_t (*crcudaGraphicsResourceGetMappedPointer)(void **devPtr,  size_t *size,  cudaGraphicsResource_t resource);
  cudaError_t (*crcudaGraphicsSubResourceGetMappedArray)(cudaArray_t *array,  cudaGraphicsResource_t resource,  unsigned int arrayIndex,  unsigned int mipLevel);
  cudaError_t (*crcudaGraphicsResourceGetMappedMipmappedArray)(cudaMipmappedArray_t *mipmappedArray,  cudaGraphicsResource_t resource);
  cudaError_t (*crcudaGetChannelDesc)(struct cudaChannelFormatDesc *desc,  cudaArray_const_t array);
  struct cudaChannelFormatDesc (*crcudaCreateChannelDesc)(int x,  int y,  int z,  int w,  enum cudaChannelFormatKind f);
  cudaError_t (*crcudaBindTexture)(size_t *offset,  const struct textureReference *texref,  const void *devPtr,  const struct cudaChannelFormatDesc *desc,  size_t size );
  cudaError_t (*crcudaBindTexture2D)(size_t *offset,  const struct textureReference *texref,  const void *devPtr,  const struct cudaChannelFormatDesc *desc,  size_t width,  size_t height,  size_t pitch);
  cudaError_t (*crcudaBindTextureToArray)(const struct textureReference *texref,  cudaArray_const_t array,  const struct cudaChannelFormatDesc *desc);
  cudaError_t (*crcudaBindTextureToMipmappedArray)(const struct textureReference *texref,  cudaMipmappedArray_const_t mipmappedArray,  const struct cudaChannelFormatDesc *desc);
  cudaError_t (*crcudaUnbindTexture)(const struct textureReference *texref);
  cudaError_t (*crcudaGetTextureAlignmentOffset)(size_t *offset,  const struct textureReference *texref);
  cudaError_t (*crcudaGetTextureReference)(const struct textureReference **texref,  const void *symbol);
  cudaError_t (*crcudaBindSurfaceToArray)(const struct surfaceReference *surfref,  cudaArray_const_t array,  const struct cudaChannelFormatDesc *desc);
  cudaError_t (*crcudaGetSurfaceReference)(const struct surfaceReference **surfref,  const void *symbol);
  cudaError_t (*crcudaCreateTextureObject)(cudaTextureObject_t *pTexObject,  const struct cudaResourceDesc *pResDesc,  const struct cudaTextureDesc *pTexDesc,  const struct cudaResourceViewDesc *pResViewDesc);
  cudaError_t (*crcudaDestroyTextureObject)(cudaTextureObject_t texObject);
  cudaError_t (*crcudaGetTextureObjectResourceDesc)(struct cudaResourceDesc *pResDesc,  cudaTextureObject_t texObject);
  cudaError_t (*crcudaGetTextureObjectTextureDesc)(struct cudaTextureDesc *pTexDesc,  cudaTextureObject_t texObject);
  cudaError_t (*crcudaGetTextureObjectResourceViewDesc)(struct cudaResourceViewDesc *pResViewDesc,  cudaTextureObject_t texObject);
  cudaError_t (*crcudaCreateSurfaceObject)(cudaSurfaceObject_t *pSurfObject,  const struct cudaResourceDesc *pResDesc);
  cudaError_t (*crcudaDestroySurfaceObject)(cudaSurfaceObject_t surfObject);
  cudaError_t (*crcudaGetSurfaceObjectResourceDesc)(struct cudaResourceDesc *pResDesc,  cudaSurfaceObject_t surfObject);
  cudaError_t (*crcudaDriverGetVersion)(int *driverVersion);
  cudaError_t (*crcudaRuntimeGetVersion)(int *runtimeVersion);
  cudaError_t (*crcudaGetExportTable)(const void **ppExportTable,  const cudaUUID_t *pExportTableId);
  void** (*__crcudaRegisterFatBinary)(void* fatCubin);
  void (*__crcudaUnregisterFatBinary)(void **fatCubinHandle);
  void (*__crcudaRegisterVar)(void **fatCubinHandle,char *hostVar,char *deviceAddress,const char *deviceName,int ext,int size,int constant,int global);
  void (*__crcudaRegisterTexture)(void **fatCubinHandle,const struct textureReference *hostVar,const void **deviceAddress,const char *deviceName,int dim,int norm,int ext);
  void (*__crcudaRegisterSurface)(void **fatCubinHandle,const struct surfaceReference  *hostVar,const void **deviceAddress,const char *deviceName,int dim,int ext);
  void (*__crcudaRegisterFunction)(void **fatCubinHandle,const char *hostFun,char *deviceFun,const char *deviceName,int thread_limit,uint3 *tid,uint3 *bid,dim3 *bDim,dim3 *gDim,int *wSize);
  void (*__crcudaRegisterShared)(void **fatCubinHandle, void **devicePtr);
  void (*__crcudaRegisterSharedVar)(void **fatCubinHandle,void **devicePtr,size_t size,size_t alignment,int storage);
  int (*__crcudaSynchronizeThreads)(void** one,void* two);
  void (*__crcudaTextureFetch)(const void* tex,void* index,int integer,void* val);
  void (*__crcudaMutexOperation)(int lock);
  cudaError_t (*__crcudaRegisterDeviceFunction)();

} CRCUDA;

#define CUDA_LIB_PATH  "/usr/local/cuda-5.5/lib64/libcudart.so"  
#define TRACE(func) printf("[TRACE -runtime-] %-25s\n",func)

extern CRCUDA crcuda;

#define BUFF_SIZE 1024;
extern void* buff_send;
extern void* buff_recv;
extern void* fatBin;
extern int recvBuff;
extern size_t recv_buff_size;

//kernels.c
extern void init_kernels();
extern void add_kernel();
extern void* get_kernel(void*);

//load.c
extern void load_cuda_lib();
extern int dlclose_cuda();

//assinn.c
extern void crcuda_call(crcuda_message*, int);

//message.c
extern void send_message(crcuda_message*, int);
extern void send_buff(size_t, int);
extern void recv_buff(size_t, int);

#define SEND(msg, sd) send_message(msg, sd);
#define SEND_BUFF(size, sd) send_buff(size, sd);
#define RECV_BUFF(size, sd) recv_buff(size, sd);

/*
extern void __crcudaRegisterFatBinary(crcuda_message*, int);
extern void __crcudaRegisterFunction(crcuda_message*, int);
extern void __crcudaUnregisterFatBinary(crcuda_message*, int);
extern void crcudaMalloc(crcuda_message*, int);
extern void crcudaFree(crcuda_message*, int);
extern void crcudaMemcpy(crcuda_message*, int);
extern void crcudaConfigureCall(crcuda_message*, int);
extern void crcudaSetupArgument(crcuda_message*, int);
extern void crcudaLaunch(crcuda_message*, int);
extern void crcudaStreamCreate(crcuda_message*, int);
extern void crcudaStreamDestroy(crcuda_message*, int);
*/

#define ENTER  
#define LEAVE  
