#include <crcuda_client.h>

void crcuda_device_backup(){

  region* r;

  r = crcuda.cp->d0->next;

  while(r->mode >= 0){

    r->backup = malloc(r->size);

    msg->iden = MEMCPY;
    msg->data.memcpy.kind  = cudaMemcpyDeviceToHost;
    msg->data.memcpy.count = r->size;
    msg->data.memcpy.dst   = r->backup;
    msg->data.memcpy.src   = r->base;

    SEND;
    RECV_BUFF(r->backup, r->size);
    RECV;

    msg->iden = FREE;
    msg->data.free.devPtr = r->base;

    SEND;
    RECV;

    r = r->next;
  }
}

void crcuda_device_restore(){

  region *r;

  r = crcuda.cp->d0->next;

  while(r->mode >= 0){

    msg->iden = MEMCPY;
    msg->data.memcpy.kind = cudaMemcpyHostToDevice;
    msg->data.memcpy.count = r->size;
    msg->data.memcpy.dst = r->base;
    msg->data.memcpy.src = r->backup;

    SEND;
    SEND_BUFF(r->backup, r->size);
    RECV;

    free(r->backup);

    r = r->next;

  }
}
