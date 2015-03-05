#include <crcuda_server.h>
#include <fatBinaryCtl.h>

void crcuda_call(crcuda_message *msg, int sd){

  switch(msg->iden){

  case MALLOC:

    printf("cudaMalloc\n");

    crcudaMalloc(msg, sd);

    break;

  case FREE:

    printf("cudaFree\n");

    crcudaFree(msg, sd);

    break;

  case MEMCPY:
    
    printf("cudaMemcpy\n");
    
    crcudaMemcpy(msg, sd);

    break;

  case CONFIGURECALL:

    printf("cudaConfigureCall\n");

    crcudaConfigureCall(msg, sd);

    break;

  case SETUPARGUMENT:

    printf("cudaSetupArgument\n");

    crcudaSetupArgument(msg, sd);
    
    break;

  case LAUNCH:
    
    printf("cudaLaunch\n");

    crcudaLaunch(msg, sd);

    break;

  case REGISTERFATBINARY:

    printf("__cudaRegisterFatBinary\n");

    __crcudaRegisterFatBinary(msg, sd);

    break;

  case REGISTERFUNCTION:

    printf("__cudaRegisterFunction\n");

    __crcudaRegisterFunction(msg, sd);

    break;

  case UNREGISTERFATBINARY:

    printf("__cudaUnregisterFatBinary\n");

    __crcudaUnregisterFatBinary(msg, sd);
    
    break;

  default:

    printf("UNKOWN FUNCTION CALL...(%d)\n", msg->iden);
    exit(-1);

    break;

  }
}
