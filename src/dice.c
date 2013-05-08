#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void envio_cat(char category1[], char category2[], int result);
int tirarDado(FILE *sock, char cat1[], char cat2[]);
void categoria(int x, char cat[]);
//void categoria2(int x, char cat2[]);

int main (int argc, char* argv[]) {

	char cat1[20], cat2[20];

	int x = tirarDado((FILE*)1,cat1,cat2);
	
	envio_cat(cat1,cat2,x);
	
}


// Función para enviar las dos categorías y el resultado del dado al cliente
// Entrada: dos punteros a string con dos categorías y el resultado del dado
// Salida: envía por el socket las categorías y el resultado del dado
void envio_cat(char category1[], char category2[], int result){
	char buf_info[50];
	sprintf(buf_info,"%s %s %d\n", category1, category2, result);
	//fprintf(fsock,"%s",buf_info);
	printf("Se han enviado al jugador las categorías %s y %s.\n",category1, category2);
	//bzero(buf_info);
	
	// Uso el socket para enviar toda la información
}

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

int tirarDado(FILE *sock, char cat1[], char cat2[]) {
	int d, x, y;
	
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
	
	return d;
}