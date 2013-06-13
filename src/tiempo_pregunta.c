#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <Socket.h>

// Función para contar los 10 segundos de una pregunta.
// Entrada: socket
// Salida: si pasan los 10 segundos, se manda "P_FAIL" al socket
// si no pasan los 10 segundos, no se envía nada
void iniciarContador(FILE* sock) {
	int seg=0;
	pid_contador = fork();
	if(pid_contador == 0) {
		while (seg<10){
			seg++;
			sleep(1);
		}
		socket_escribir(sock, "P_FAIL\n");
		printf("Se ha superado el límite de tiempo.\n");
		kill(pid_contador,SIGINT);
	}
}
	