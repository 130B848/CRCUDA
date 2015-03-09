#include <crcuda_client.h>

void crcuda_stream_restore(){

  crcuda_stream* sp;
  cudaError_t res;

  sp = crcuda.cp->s0->next;

  while(sp->mode >= 0){

    msg->iden = STREAMCREATE;

    SEND;
    RECV;

    sp->s = msg->data.streamCreate.stream;

    sp = sp->next;

  }
}
