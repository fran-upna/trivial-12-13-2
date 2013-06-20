#include <stdlib.h>
#include <stdio.h>
#include <Socket.h>
#include <PartidaType.h>

// Función del servidor
void comprobar_respuesta(partidas p, int correcta){
  if (atoi(Socket_leer(socket)) == correcta){ //Comprobamos si la respuesta es correcta
    Socket_escribir(socket, "Respuesta correcta");
    if (strcmp(p.turno == p.jugador1) == 0)
	p.pjugador1++; //Sumamos un punto a la puntuación del usuario 1
    else
        p.pjugador2++; //Sumamos un punto a la puntuación del usuario 2
  } else{
    Socket_escribir(socket, "Respuesta incorrecta");
    if (strcmp(p.turno, p.jugador1) == 0)
	p.turno = p.jugador2; //Pasamos turno al jugador 2
    else
        p.turno = p.jugador1; //Pasamos turno al jugador 1
  }
}

// Función del cliente
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