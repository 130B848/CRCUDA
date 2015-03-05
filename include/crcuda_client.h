#include <iden.h>

#define ENTER
#define LEAVE
#define UNSUPPORTED unsupported_function_calls();
#define TRACE(func) printf("%s\n",func);//printf("[TRACE]\t%-25s\n",func);

//connect.c
extern int sockfd;
extern void connect_to_server();

//message.c
extern crcuda_message *msg;
extern void send_message();
extern void recv_message();
extern void send_buff(void*, size_t);
extern void recv_buff(void*, size_t);
#define SEND send_message();
#define RECV recv_message();
#define SEND_BUFF(ptr, size) send_buff(ptr, size);
#define RECV_BUFF(ptr, size) recv_buff(ptr, size);

typedef struct _stream{
  struct _stream *prev,*next;
  cudaStream_t s;
  unsigned int flags;
  int mode;
} crcuda_stream;

typedef struct _event{
  struct _event *prev,*next;
  cudaEvent_t e;
  unsigned int flags;
  int mode;
  float charge;
} crcuda_event;

typedef struct _array{
  struct _array *prev,*next;
  cudaArray_t ar;
  char* backup;
  size_t width;
  size_t height;
  size_t backup_size;
  unsigned int flags;
  struct cudaExtent extent;
  struct cudaChannelFormatDesc desc;
  int mode;
  /*
    mode
    0 : cudaMallocArray
    1 : cudaMalloc3DArray
  */
} crcuda_array;

typedef struct _textureObject{
  struct _textureObject *prev,*next;
  cudaTextureObject_t tx;
  struct cudaResourceDesc rdesc;
  struct cudaTextureDesc tdesc;
  struct cudaResourceViewDesc vdesc;
} crcuda_texture;

typedef struct _textureReferece{
  struct _textureReferece *prev,*next;
  /*-1 : invalid
     0 : not binded
     1 : binded
   */
  struct textureReference *texref;
  int mode;
  size_t *offset;
  void *devPtr;
  struct cudaChannelFormatDesc desc;
  size_t size;
} crcuda_textureReference;

typedef struct _region{
  struct _region *prev,*next;
  size_t size;
  void *devPtr;
  void *base;
  char* backup;
  int mode;
  int flag;
} region;

typedef struct _symbol{

  struct _symbol *prev,*next;

#if 0
  char* sym;
  char* backup;
  size_t size;
  void *devPtr;
#endif

  char* backup;
  char* hostVar;
  char* deviceAddress;
  char* deviceName;
  int ext;
  int size;
  int constant;
  int global;

} symbol;

typedef struct _apilog{
  struct _apilog *prev,*next;
  unsigned int type;
  union{
    Malloc malloc;
    MallocPitch mallocPitch;
    Malloc3D malloc3D;
    Free free;
    RegisterFatBinary registerFatBinary;
    RegisterFunction registerFunction;
    RegisterVar registerVar;
    HostRegister hostRegister;
    HostUnregister hostUnregister;
  } data;
} apilog;

typedef struct _context{
  crcuda_stream *s0,*s1;
  crcuda_event *e0,*e1;
  crcuda_array *ar0,*ar1;
  crcuda_texture *tx0,*tx1;
  crcuda_textureReference *txr0,*txr1;
  region *d0,*d1;
  apilog *a0,*a1;
  symbol *sm0,*sm1;
} context;

typedef struct _crcuda{
  context* cp;
} CRCUDA;

extern CRCUDA crcuda;
