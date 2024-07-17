#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define MYPORT 8000    /* el puerto donde se enviaran los datos */

typedef char* optval_t;

int main() {
  int sockfd, rc;
  struct sockaddr_in their_addr;  /*  Almacenara la direccion IP y numero de puerto del servidor */
  struct sockaddr_in *d_their_addr;
  unsigned int their_addr_len = sizeof(struct sockaddr_in);
  unsigned char cmd[16] = "SDRSTICK";
  unsigned int cmd_len = sizeof(cmd);
  unsigned char puerto[] = "eth0";
  socklen_t puerto_t = sizeof(puerto);
  int opt_val = 1;
  d_their_addr = &their_addr;
  /* Creamos el socket */
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }
  printf("socket OK\n");
  memset((char *)&their_addr,0,sizeof(their_addr));
  their_addr.sin_family = AF_INET;  /* host byte order */
  their_addr.sin_port = htons(MYPORT);  /* network byte order */
  their_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
  bzero(&(their_addr.sin_zero), 8);
  if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,(optval_t)&opt_val, sizeof(int)) == -1) {
    printf("can't set socket option SO_BROADCAST\n");
  }
  setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, &puerto, puerto_t);
  //send SDRSTICK discovery packet
  if((rc = sendto(sockfd,cmd,9,0,(struct sockaddr *)d_their_addr,their_addr_len))==-1) {
    perror("sendto");
    printf("Error sending discovery packet\n");
  }
  
  bzero(cmd,cmd_len);
  rc = recv(sockfd, cmd, sizeof(cmd), 0);
  printf("Recibí %d characteres.\n",rc);
  printf("Rx:%s\n", cmd);   
  close(sockfd);
  return 0;
}
