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
  unsigned int frec;
  unsigned int cmd[4] = {0x00000007,0,0,0};
  unsigned int cmd_len = sizeof(cmd);
  if (argc != 3) {
    fprintf(stderr,"usage: sdrstick-set-frec hostname frec[Hz]\n");
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
  printf("argv[2]: \"%s\"\n",argv[2]);
  sscanf(argv[2],"%d", &frec);
  printf("La frecuencia deseada es: %d\n",frec);
  cmd[1] = frec;
  rc = send(sockfd, cmd, cmd_len, 0);
  bzero(cmd,sizeof(cmd));
  rc = recv(sockfd, cmd, sizeof(cmd), 0);
  printf("Recibí %d characteres.\n",rc);
  printf("Rx:%d:%d:%d:%d\n", cmd[0], cmd[1], cmd[2], cmd[3]);   
  close(sockfd);
  return 0;
}
