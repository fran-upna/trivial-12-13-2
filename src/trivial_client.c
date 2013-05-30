#include <stdio.h>
#include <Socket.h>

int main(int argc, char *argv[]) {
  int sock;
  if(argc !=2){
    printf("Error. Uso: %s <ip_servidor> <puerto_servidor>\n");
    exit(-1);
  }
  sock = Socket_prepararCliente(argv[1],argv[2]);

	return 0;
}
