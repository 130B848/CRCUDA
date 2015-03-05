#include <crcuda_client.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

crcuda_message* msg;

void send_message(){

  printf("\tSEND\n");
  
  int result;

  result = send(sockfd, msg, sizeof(crcuda_message), 0);

  if(result == -1){
    printf("Failed to send msg.\n");
  }
}

void recv_message(){

  printf("\tRECV\n");

  int result;

  result = recv(sockfd, msg, sizeof(crcuda_message), 0);

  if(result == -1){
    printf("Failed to send msg.\n");
  }
}

void send_buff(void* ptr, size_t size){

  printf("\tSEND_BUFF\n");

  int result;
  int sended = 0;

  while(sended < size){
    result = send(sockfd, ptr + sended, size - sended, 0);
    sended += result;
  }

  if(result == -1){
    printf("Failed to send buffer\n");
  }
}

void recv_buff(void* ptr, size_t size){

  printf("\tRECV_BUFF\n");

  int result;
  int recved = 0;

  while(recved < size){
    result = recv(sockfd, ptr + recved, size - recved, 0);
    recved += result;
  }

  if(result == -1){
    printf("Failed to recv buffer\n");
  }
}
