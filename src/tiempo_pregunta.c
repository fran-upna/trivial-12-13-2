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
		char buf[5];
		bzero(buf, 5);
		
		while(seg < 10 && ok == 0) {
			fgets(buf, 5, sock);
			if(strncmp(buf, "P_OK",4) == 0) {
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

// Parte correspondiente al servidor (para añadir a la función del grupo 1)
/*char buf[] = socket_leer(sock);
if (strncmp(buf,"P_FAIL\n",6)==0){
	// Hacer lo mismo que se haría cuando la pregunta es incorrecta
}*/