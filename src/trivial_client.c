#include <string.h>
#include <stdio.h>
#include "Socket.h"
#include <Registro.h>

int main(int argc, char *argv[]) {
  int sock;
  char opcion;
  char *datos;	

  if(argc !=2){
    printf("Error. Uso: %s <ip_servidor> <puerto_servidor>\n");
    exit(-1);
  }
  sock = Socket_prepararCliente(argv[1],argv[2]);

  printf("Bienvenido a nuestro TRIVIAL\n¿Que deseas hacer?\n 1.-Autentificarte\n 2.-Registrarte\n 3.-Salir\n");
  scanf("%c",opcion);
  if (opcion=='1') {
  }
  else if (opcion=='2'){
    datos=Registro_altacliente(sock);
    Socket_escribir(sock,datos);
    datos=Socket_leer(sock);
    if (datos[0]=='O'){
      printf("Registro correcto\n");
    }
    else {
      printf("Registro incorrecto\n");
    }
  }
  else if (opcion=='3'){
    return 0;
  }

  return 0;
}
