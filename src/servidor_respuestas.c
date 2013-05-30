#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <.h>

void comprobar_respuesta(struct partidas p, int correcta){
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