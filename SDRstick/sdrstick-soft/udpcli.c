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
  int sockfd;
  struct sockaddr_in their_addr;  /*  Almacenara la direccion IP y numero de puerto del servidor */
  struct hostent *he;
  int numbytes;
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
  their_addr.sin_family = AF_INET;  /* host byte order */
  their_addr.sin_port = htons(MYPORT);  /* network byte order */
  their_addr.sin_addr = *((struct in_addr *)he->h_addr);
  bzero(&(their_addr.sin_zero), 8);
  /* enviamos el mensaje, esta linea contiene una barra invertida al final, indicando que sigue abajo*/
  if ((numbytes=sendto(sockfd, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&their_addr, \
	sizeof(struct sockaddr))) == -1) {
    perror("sendto");
    exit(1);
  }
  printf("enviados %d bytes hacia %s\n",numbytes,inet_ntoa(their_addr.sin_addr));
  close(sockfd);
  return 0;
}
