#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <Socket.h>

/* AVISO: La parte comentada corresponde a la parte de código que debe implementarse en el main del cliente*/

/*pid_t pid_contador;

int main(void){
	
	int res;
	
	printf("****Probaremos el conteo de 10 segundos****\n");
	printf("Tienes 10 segundos para escribir un número y pulsar ENTER\n");
	iniciarContador((FILE*)1);
	// Aquí se leería la respuesta
	if (kill(pid_contador, 0) == 0) {
		kill(pid_contador,SIGINT);
		printf("Bien hecho, te has salvado\n");
	}.
	
	return 0;
}
*/

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
	
// Parte correspondiente al servidor (para añadir a la función del grupo 1)
/*char buf[] = socket_leer(sock);
if (strncmp(buf,"P_FAIL\n",6)==0){
// Hacer lo mismo que se haría cuando la pregunta es incorrecta
}*/