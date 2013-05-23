#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// Librería para usar el socket
#include <Socket.h>

void categoria(int x, char cat[]) {
	switch(x) {
		case 1: strcpy(cat, "GEOGRAPHY");
				break;
		case 2: strcpy(cat, "ENTERTAINMENT");
				break;
		case 3: strcpy(cat, "HISTORY");
				break;
		case 4: strcpy(cat, "LITERATURE");
				break;
		case 5: strcpy(cat, "SCIENCE_NATURE");
				break;
		case 6: strcpy(cat, "SPORTS");
				break;
		default: printf("La tirada no es válida.\n");
	}
}

void tirarDado(FILE *sock) {
	int d, x, y;
	char cat1[20], cat2[20];
	
	// Establezco la semilla para aleatoriedad
	srand(time(NULL));
	d = rand() % 6 + 1;
	// printf("DEBUG | El dado ha salido %d\n",d);
	
	// Calculamos categorías aleatorias
	srand(time(NULL));
	x = rand() % 6 + 1;
	y = rand() % 6 + 1;
	
	// Nos aseguramos de que las categorías son distintas
	while(x == y) {
		y = rand() % 6 + 1;
	}
	
	// Envíamos categoría
	categoria(x, cat1);
	categoria(y, cat2);
	
	// Buffer para almacenar lo que se envía por el socket
	char buf_info[strlen(cat1)+strlen(cat2)+sizeof(int)];

	// Enviamos al socket las categorías
	sprintf(buf_info,"%s %s %d\n", cat1, cat2, d);
	socket_escribir(sock, buf_info);
	printf("Se han enviado al jugador las categorías %s y %s.\n",cat1, cat2);
	
}

// Entrada: dos arrays que almacenan cada una de las dos categorías.
// Modifica: mete en los arrays pasados como argumento el valor de las categorías.
void recibirCategoria(char cat1[], char cat2[]){
	
	// Buffer para leer lo que venga del socket
	char buf_leido[50];
	
	// Declaramos variable para almacenar el resultado del dado
	int res_dado;
	
	// Leemos del socket las categorías y el resultado del dado
	buf_leido = socket_leer(sock);
	
	// Separamos el resultado en dos buffers y un entero
	sscanf(buf_leido,"%s %s %d",cat1,cat2,&res_dado);
	
	// Mostramos el resultado del dado
	printf("Has sacado un %d en la tirada.\n",res_dado);
	
	// Mostramos las categorías
	printf("Las categorías a elegir son: \n"); 
	printf("     a) %s \n",cat1);
	printf("     b) %s \n",cat2);
	
}