#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QuestionType.h>
#include <Socket.h>

void categorias(int x, char cat[]) {
	switch(x) {
		case GEOGRAPHY: strcpy(cat, "GEOGRAPHY");
				break;
		case ENTERTAINMENT: strcpy(cat, "ENTERTAINMENT");
				break;
		case HISTORY: strcpy(cat, "HISTORY");
				break;
		case LITERATURE: strcpy(cat, "LITERATURE");
				break;
		case SCIENCE_NATURE: strcpy(cat, "SCIENCE_NATURE");
				break;
		case SPORTS: strcpy(cat, "SPORTS");
				break;
		default: printf("No existe categoría.\n");
	}
}

// Función devolverCategorias para colocar en el lado del Servidor y devolver las categorias de juego del trivial
// Entrada: un entero que indica el socket al que se le deben devolver las categorías.
// Requisitos: haber recibido el mensaje C CATEGORY LIST desde el cliente.
// Salida: ninguna
void devolverCategorias(int socket){
	//if (strstr(entrada,"C CATEGORY LIST")!=NULL) Se tiene que comprobar fuera y llamar a la función si es necesario.
		Socket_escribir(socket,"LIST GEOGRAPHY ENTERTAINMENT HISTORY LITERATURE SCIENCE_NATURE SPORTS");
}

// Función pedirCategorias para colocar en el lado del Cliente y que muestra por pantalla las categorías devueltas por el servidor.
// Entrada: un entero que indica el socket del servidor con el que se va a comunicar.
// Requisitos: no encontrarse en medio de ninguna otra comunicación con el servidor.
// Salida: ninguna.
void pedirCategorias(int socket){
	char* buff;
	char* cad;

	Socket_escribir(socket, "C CATEGORY LIST");
	buff = Socket_leer(socket);

	puts("Las categorías de las que dispone el juego son las siguientes:");
	cad = strtok(buff, " \n");    // Primer token -> LIST
	if((cad = strtok( NULL, " \n"))==NULL) // Primera llamada para comprobar si no hay categorias.
		puts("No hay mas usuarios. Solamente usted se encuentra conectado");
	else 
		printf("\t%s\n", cad);
   	while((cad = strtok( NULL, " \n")) != NULL)  // Posteriores llamadas
     		printf( "\t%s\n", cad );
}