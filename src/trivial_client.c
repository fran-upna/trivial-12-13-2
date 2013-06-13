#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Registro.h>
#include <Socket.h>

int main(int argc, char *argv[]) {
  char opcion;
  char enviaopcion[4] = {0,0,0,0};
  char buffer[50];
  //Crear el socket
  printf("Bienvenido a nuestro TRIVIAL\n¿Que deseas hacer?\n 1.-Autentificarte\n 2.-Registrarte\n 3.-Salir\n");
  scanf("%c",&opcion);
  
  sprintf(enviaopcion,"%c", opcion);
  Socket_escribir(sock,enviaopcion);
  
  if (opcion == '1') {
  }
  else if (opcion == '2') { // Ha seleccionado la opcion de registrarse como nuevo usuario del trivial
    char envio[50];
    Registro_altacliente(sock, envio); // Llama a la funcion que le pedirá su nombre y contraseña y le devuelve la informacion en datos
    
    Socket_escribir(sock,envio); // Envia por el socket al servidor su nombre y su clave, en una misma variable, datos.
    
    buffer=Socket_leer(sock); // Recibe la respuesta del registro
    
    if (buffer[0] == 'O'){ // Si recibe 'O' todo ha ido bien
      printf("Registro correcto\n");
      // AQUÍ CONTINUA EL FLUJO DE EJECUCIÓN NORMAL DEL PROGRAMA
    }
    else {
      printf("Registro incorrecto\n");
      exit(0);
    }
  }
  else {
    return 0;
  }
  return 0;
}
