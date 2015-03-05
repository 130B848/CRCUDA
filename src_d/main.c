#include <crcuda_server.h>
#include <fatBinaryCtl.h>

#define TRUE  1
#define FALSE 0

CRCUDA crcuda;
int end_server = FALSE;

int main(){

  printf("START CRCUDA DAEMON...\n");
  
  load_cuda_lib();

  printf("FINISH LOADING CUDA LIB...\n");
  printf("SETUP SOCKET...\n");

  /*
    printf("********************************\n");
    printf("** PID %-5d                  **\n", getpid());
    printf("** export CRCUDA_SERVER=%-5d **\n", getpid());
    printf("********************************\n");
  */

  int len,rc,on = 1;
  int listen_sd,max_sd,new_sd;
  int desc_ready;
  int close_conn;

  struct sockaddr_un addr;
  struct timeval timeout;
  fd_set master_set,working_set;

  listen_sd = socket(AF_UNIX,SOCK_STREAM,0);

  if(listen_sd < 0){
    perror("socket() failed\n");
    exit(-1);
  }

  rc = setsockopt(listen_sd, SOL_SOCKET, SO_REUSEADDR, (char*)&on,sizeof(on));

  if(rc < 0){
    perror("setsockopt() failed\n");
    exit(-1);
  }

  unlink("/tmp/crcuda_server");

  memset(&addr,0,sizeof(addr));

  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path,"/tmp/crcuda_server");

  rc = bind(listen_sd,(struct sockaddr*)&addr,sizeof(addr));

  if(rc < 0){
    perror("bind() failed");
    close(listen_sd);
    exit(-1);
  }

  rc = listen(listen_sd,SOMAXCONN);

  if(rc < 0){
    perror("listen() failed");
    close(listen_sd);
    exit(-1);
  }

  FD_ZERO(&master_set);
  max_sd = listen_sd;
  FD_SET(listen_sd,&master_set);

  timeout.tv_sec = 3*60;
  timeout.tv_usec = 0;

  init_kernels();

  int i;
  crcuda_message* msg;

  msg = (crcuda_message*)malloc(sizeof(crcuda_message));

  buff_send = malloc(1024*1024);
  buff_recv = malloc(1024*1024);

  do{

    memcpy(&working_set,&master_set,sizeof(master_set));

    rc = select(max_sd+1, &working_set, NULL, NULL, NULL);

    if(rc < 0){
      perror("select() failed\n");
      break;
    }

    if(rc == 0){
      printf("select() time out. End program.\n");
      break;
    }

    desc_ready = rc;

    for(i = 0 ; i < max_sd+1 && desc_ready > 0 ; ++i){

      if(FD_ISSET(i,&working_set)){

	desc_ready = -1;

	if(i == listen_sd){

	  printf("ACCEPT <= %d\n", listen_sd);

	  new_sd = accept(listen_sd,NULL,NULL);

	  if(new_sd < 0){
	    printf("accept() failed");
	    end_server = TRUE;
	  }

	  FD_SET(new_sd,&master_set);

	  if(new_sd > max_sd){
	    max_sd = new_sd;
	  }

	}else{

	  rc = recv(i, msg, sizeof(crcuda_message), 0);
	  
	  if(rc <= 0){

	    FD_CLR(i,&master_set);
	    end_server = TRUE;

	    printf("PROC FIN ...\n");

	  }else{

	    crcuda_call(msg, i);

	  }
	}
      }
    }
  }while(end_server == FALSE);
}
