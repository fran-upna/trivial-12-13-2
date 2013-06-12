#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Socket.h>
#include <Registro.h>
#include <Socket.h>

int sock;

int main(int argc, char *argv[]) {
  char opcion[2] = {0,0};
  char *datos;	
  char l;
  char buffer[50];

  if(argc !=2){
    printf("Error. Uso: %s <ip_servidor> <puerto_servidor>\n",argv[0]);
    exit(-1);
  }
  sock = Socket_prepararCliente(argv[1],argv[2]);

  //Crear el socket
  printf("Bienvenido a nuestro TRIVIAL\n¿Que deseas hacer?\n 1.-Autentificarte\n 2.-Registrarte\n 3.-Salir\n");
  scanf("%c", &opcion[0]);

  Socket_escribir(sock,opcion);
  if (strcmp(opcion, "1") == 0) {
  }
  else if (strcmp(opcion, "2") == 0){ // Ha seleccionado la opcion de registrarse como nuevo usuario del trivial
    char envio[50];
    Registro_altacliente(sock, envio); // Llama a la funcion que le pedirá su nombre y contraseña y le devuelve la informacion en datos
    
    Socket_escribir(sock,envio); // Envia por el socket al servidor su nombre y su clave, en una misma variable, datos.
    
    buffer=Socket_leer(sock); // Recibe la respuesta del registro
    
    if (strcmp(buffer, "O") == 0){ // Si recibe 'O' todo ha ido bien y si recibe 'E' ha fallado.
      printf("Registro correcto\n");
    }
    else {
      printf("Registro incorrecto\n");
      exit(0);
    }
  }
  else if (strcmp(opcion, "3") == 0){
    return 0;
  }

  return 0;
}
