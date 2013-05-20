#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <Socket.h>

// Función para contar los 10 segundos de una pregunta.
// Entrada: socket
// Salida: si pasan los 10 segundos, se manda "P_FAIL" al socket
// 		   si no pasan los 10 segundos, no se envía nada
void iniciarContador(FILE* sock) {
	pid_t pid_contador = fork();
	if(pid_contador == 0) {
		int seg = 0, ok = 0;
		char buf[30];
		bzero(buf, 30);
		
		while(seg < 10 && ok == 0) {
			fgets(buf, 30, sock);
			if(strcmp(buf, "P_OK") == 0) {
				ok = 1;
			}
			sleep(1);
			seg++;
		}

		if(ok == 0) {
			// Informamos de que han pasado los 10 segundos
			printf("Pregunta fallida: han pasado los 10 segundos.");
			socket_escribir(sock, "P_FAIL\n");
		}
	}
}