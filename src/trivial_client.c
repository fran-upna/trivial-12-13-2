#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Registro.h>
#include <Socket.h>
#include <nuevaPartida.h>

int main(int argc, char *argv[]) {
  char opcion;
  char enviaopcion[4] = {0,0,0,0}; 
  char buffer[50];
  char registro;

  /* Comprobar que los parámetros son correctos */
  if (argc!=3){
    printf("ERROR: no ha utilizado la sintaxis correcta\nUso: %s <direccion_ip> <puerto>\n", argv[0]);
    exit(-1);
  }

  //Crear el socket
  int sock=Socket_prepararCliente(argv[1],argv[2]);

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
    
    buffer[0]=Socket_leer(sock); // Recibe la respuesta del registro
    
    if (buffer[0] == 'O'){ // Si recibe 'O' todo ha ido bien
      printf("Registro correcto\n");
      // AQUÍ CONTINUA EL FLUJO DE EJECUCIÓN NORMAL DEL PROGRAMA
      while(nuevaPartida(sock)); // Mientras no se registre una nueva partida de forma efectiva se continua en el bucle.
    }
    else {
      printf("Registro incorrecto\n");
      exit(0);
    }
  }
  else {
    return 0;
  }
  
  
  
  //Funcion que elige una de las categorías anterirormente listadas, sus argumentos son las dos categorias son dos enteros
  //representando las distintas categorías, y el sock es el socket.
  SeleccionCategoria_seleccion(categroria1, categoria2, sock);
  //Funcion que lee por el socket un mensaje que contiene la pregunta con sus respuestas, las muestra aleatoriamente, da la opcion de 
  //elegir una respuesta, y devuelve un int con la posicion de la respuesta correcta.
  int pos_correcta=SeleccionCategoria_Pregunta(sock);
  return 0;
}
