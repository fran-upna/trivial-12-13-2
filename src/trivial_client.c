#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Socket.h>

int sock;

int main(int argc, char *argv[]) {
  if(argc !=2){
    printf("Error. Uso: %s <ip_servidor> <puerto_servidor>\n",argv[0]);
    exit(-1);
  }
  sock = Socket_prepararCliente(argv[1],argv[2]);

	return 0;
}
