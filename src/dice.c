#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

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
	printf("El dado ha salido %d\n",d);
	
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
	
	char buf_info[strlen(cat1)+strlen(cat2)+sizeof(int)];

	// Enviamos al socket las categorías
	sprintf(buf_info,"%s %s %d\n", cat1, cat2, d);
	//fprintf(fsock,"%s",buf_info);
	printf("Se han enviado al jugador las categorías %s y %s.\n",cat1, cat2);
	
	// Uso el socket para enviar toda la información
}