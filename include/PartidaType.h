#ifndef PARTIDATYPE_H
#define PARTIDATYPE_H

// Estructura para almacenar las nuevas partidas disponibles sin el segundo usuario
typedef struct nuevas_partidas{
	char *codPartida, *jugador;
} nuevas_partidas;


// Estructura para almacenar las partidas en juego.
typedef struct partidas{
	char *Jugador1, *Jugador2, *Turno, *CodPartida;
	int Pjugador1, Pjugador2;
} partidas; 

#endif