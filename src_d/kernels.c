#include <crcuda_server.h>
#include <fatBinaryCtl.h>
#include <string.h>

void init_kernels(){
  crcuda.ck0 = (cr_kernels*)malloc(sizeof(cr_kernels));
  crcuda.ck1 = (cr_kernels*)malloc(sizeof(cr_kernels));
  crcuda.ck0->next = crcuda.ck1;
  crcuda.ck1->prev = crcuda.ck0;
  crcuda.ck1->next = NULL;
  crcuda.ck0->prev = NULL;
}

void add_kernel(void* addr){
  cr_kernels* ck;

  ck = (cr_kernels*)malloc(sizeof(cr_kernels));
  //  ck->kernel = malloc(size);
  //  memcpy(ck->kernel, addr, size);
  ck->kernel = addr;
  ck->prev = crcuda.ck1->prev;
  ck->next = crcuda.ck1;
  ck->prev->next = ck;
  ck->next->prev = ck;

  //  printf("Added kernel : %s\n", ck->kernel);
}

void* get_kernel(void* func){
  cr_kernels* ck;
  int found = 0;

  ck = crcuda.ck0->next;
  while(ck->next != NULL){
    if(strcmp(func, ck->kernel) == 0){
      found = 1;
      break;
    }
    ck = ck->next;
  }

  if(found){
    return ck->kernel;
  }
  return NULL;
}
