#include <crcuda_server.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void* buff_send;
void* buff_recv;

void send_message(crcuda_message* msg, int sd){
  int result;
  
  result = send(sd, msg, sizeof(crcuda_message), 0);

  if(result == -1){
    printf("Failed to send msg\n");
  }
}

void send_buff(size_t size, int sd){
  printf("\tSEND_BUFF(%d)\n", size);

  int result;
  int sended = 0;

  while(sended < size){
    result = send(sd, buff_send + sended, size - sended, 0);
    sended += result;
  }

  if(result == -1){
    printf("Failed to send buff\n");
  }
}

void recv_buff(size_t size, int sd){
  printf("\tRECV_BUFF(%d)\n", size);
  
  int result;
  int recved = 0;

  while(recved < size){
    result = recv(sd, buff_recv + recved, size - recved, 0);
    recved += result;
  }

  if(result == -1){
    printf("Failed to recv buff\n");
  }
}
