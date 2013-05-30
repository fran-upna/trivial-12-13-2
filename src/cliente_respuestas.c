#include <stdlib.h>
#include <stdio.h>
#include <Socket.h>

void responder(int socket){
  char resp;
  do{
    printf("¿Cuál es tu respuesta?\n");
    resp = scanf("%c", &resp); //Guardamos la respuesta del usuario
    if ((resp != '1') && (resp != '2') && (resp != '3') && (resp != '4')) //Comprobamos que la respuesta es válida
      printf("La respuesta no es válida, debe ser: 1, 2, 3, 4");
  } while ((resp != '1') && (resp != '2') && (resp != '3') && (resp != '4')); //Si la respuesta no es válida pedimos una nueva respuesta

  Socket_escribir(socket, "%s", resp); //Enviamos la respuesta al servidor
  
  printf("%s", Socket_leer(socket)); //Mostramos si la respuesta es correcta o no
}