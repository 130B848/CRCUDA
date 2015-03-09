#include <crcuda_client.h>

void crcuda_event_update(){

  cudaError_t res;
  crcuda_event* ep;
  float f;

  msg->iden = EVENTCREATEWITHFLAGS;
  msg->data.eventCreateWithFlags.flags = cudaEventDefault;

  SEND;
  RECV;

  crcuda.cp->e1->e = msg->data.eventCreateWithFlags.event;

  msg->iden = EVENTRECORD;
  msg->data.eventRecord.event = crcuda.cp->e1->e;
  msg->data.eventRecord.stream = NULL;

  SEND;
  RECV;

  msg->iden = EVENTSYNCHRONIZE;
  msg->data.eventSynchronize.event = crcuda.cp->e1->e;

  SEND;
  RECV;

  ep = crcuda.cp->e0->next;

  while(ep->mode >= 0){

    switch(ep->mode){

    case 0:break;

    case 1:

      msg->iden = EVENTELAPSEDTIME;
      msg->data.eventElapsedTime.start = ep->e;
      msg->data.eventElapsedTime.end   = crcuda.cp->e1->e;

      SEND;
      RECV;

      ep->charge = msg->data.eventElapsedTime.ms;
      ep->mode   = 2;

      break;
    case 2:

      msg->iden = EVENTELAPSEDTIME;
      msg->data.eventElapsedTime.start = crcuda.cp->e0->e;
      msg->data.eventElapsedTime.end   = crcuda.cp->e1->e;

      SEND;
      RECV;

      ep->charge += msg->data.eventElapsedTime.ms;

      break;
    }
    ep = ep->next;
  }
}

void crcuda_event_restore(){
 
  crcuda_event* ep;

  msg->iden = EVENTCREATEWITHFLAGS;
  msg->data.eventCreateWithFlags.event = crcuda.cp->e0->e;
  msg->data.eventCreateWithFlags.flags = cudaEventDefault;
  
  SEND;
  RECV;

  msg->iden = EVENTCREATEWITHFLAGS;
  msg->data.eventCreateWithFlags.event = crcuda.cp->e1->e;
  msg->data.eventCreateWithFlags.flags = cudaEventDefault;
  
  SEND;
  RECV;

  ep = crcuda.cp->e0->next;

  while(ep->mode >= 0){
    
    msg->iden = EVENTCREATEWITHFLAGS;
    msg->data.eventCreateWithFlags.flags = ep->flags;
    msg->data.eventCreateWithFlags.event = ep->e;

    SEND;
    RECV;

    ep = ep->next;

  }

  msg->iden = EVENTRECORD;
  msg->data.eventRecord.event  = crcuda.cp->e0->e;
  msg->data.eventRecord.stream = NULL;

  SEND;
  RECV;

}
