#include <crcuda_client.h>
#include <iden.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int sockfd;

void connect_to_server(){

#if 0
  char* pid_char;
  int   pid_server;

  pid_char = getenv("CRCUDA_SERVER");

  if(pid_char == NULL){
    printf("\texport CRCUDA_SERVER=PID\n");
    exit(-1);
  }

  pid_server = atoi(pid_char);
  
  printf("pid_server : %d\n",pid_server);
#endif
  
  int result;
  struct sockaddr_un address;
  
  sockfd = socket(AF_UNIX,SOCK_STREAM,0);
  
  address.sun_family = AF_UNIX;
  
  strcpy(address.sun_path,"/tmp/crcuda_server");
  
  result = connect(sockfd,(struct sockaddr*)&address,sizeof(address));
  
  if(result == -1){
    perror("oops: client (failed to connect to the crcuda_server)\n");
    exit(-1);
  }

  msg = (crcuda_message*)malloc(sizeof(crcuda_message));
  
}
