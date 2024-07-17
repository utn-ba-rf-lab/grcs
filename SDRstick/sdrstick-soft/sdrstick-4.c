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

int main(int argc, char *argv[]) {
  int sockfd, rc;
  struct sockaddr_in their_addr;  /*  Almacenara la direccion IP y numero de puerto del servidor */
  struct hostent *he;
  int numbytes;
  unsigned int cmd[4] = {0x00000004,8008,0,0};
  unsigned int cmd_len = sizeof(cmd);
  char buff[100];
  if (argc != 2) {
    fprintf(stderr,"usage: sdrstick-stop hostname\n");
    exit(1);
  }
  /* convertimos el hostname a su direccion IP */
  if ((he=gethostbyname(argv[1])) == NULL) {
    herror("gethostbyname");
    exit(1);
  }
  /* Creamos el socket */
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    exit(1);
  }
  memset((char *)&their_addr,0,sizeof(their_addr));
  their_addr.sin_family = AF_INET;  /* host byte order */
  their_addr.sin_port = htons(MYPORT);  /* network byte order */
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  bzero(&(their_addr.sin_zero), 8);
  /* connect */
  rc = connect(sockfd, (struct sockaddr *) &their_addr, sizeof(their_addr));
  printf("connect returns %d\n",rc);  
  rc = send(sockfd, cmd, cmd_len, 0);
  bzero(buff,sizeof(buff));
  rc = recv(sockfd, buff, sizeof(buff), 0);
  printf("Recibí %d characteres.\n",rc);
  printf("Rx:%d:%d:%d:%d\n", (unsigned int) buff[0], (unsigned int) buff[3], (unsigned int) buff[7], (unsigned int) buff[11]);   
  close(sockfd);
  return 0;
}
