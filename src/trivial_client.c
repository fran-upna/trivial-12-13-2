#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Registro.h>

int main(int argc, char *argv[]) {
  char opcion;
  char *datos;	
  char l;
  //Crear el socket
  printf("Bienvenido a nuestro TRIVIAL\n¿Que deseas hacer?\n 1.-Autentificarte\n 2.-Registrarte\n 3.-Salir\n);
  scanf("%c",opcion);
  Socket_escribir(sock,opcion);
  if (opcion=='1') {
  }
  else if (opcion=='2'){ // Ha seleccionado la opcion de registrarse como nuevo usuario del trivial
    char envio[50];
    Registro_altacliente(sock, envio); // Llama a la funcion que le pedirá su nombre y contraseña y le devuelve la informacion en datos
    
    Socket_escribir(sock,envio); // Envia por el socket al servidor su nombre y su clave, en una misma variable, datos.
    
    l=Socket_leer(sock); // Recibe la respuesta del registro
    
    if (l=='O'){ // Si recibe 'O' todo ha ido bien y si recibe 'E' ha fallado.
      printf("Registro correcto\n");
    }
    else {
      printf("Registro incorrecto\n");
      exit 0;
    }
  }
  else if (opcion=='3'){
    return 0;
  }
}
