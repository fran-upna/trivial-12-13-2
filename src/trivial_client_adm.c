#include <stdio.h>
#include <string.h>

#include <ListaPreguntas.h>

#define PW "1234"


int main(int argc, char *argv[]) {
	
	int res1, res2, res3, cat; // Variables para el control de la selección de usuario
	
	char pass[15]; // Almacén para la contraseña
	
	printf("Conexión a la administración. Introduce la contraseña: ");
	scanf("%s",pass);
	
	while (strcmp(pass,PW)!=0){
		
		printf("Contraseña incorrecta.\n");
		printf("Introduce la contraseña: ");
		scanf("%s",pass);
	
	}
	
	// Menú que lista todas las opciones de administrador de forma jerárquica
	do{
		printf("\n	1. Gestión de preguntas y categorías\n");
		printf("	2. Opciones de moderación\n");
		printf("	3. Apagar el servidor\n");
		printf("	0. Salir\n"),
		printf("Indica el número correspondiente a la opción deseada: ");
		scanf("%d",&res1);
		switch (res1){
			case 1: do{
						printf("\n	1. Añadir una pregunta\n");
						printf("	2. Listar categorías disponibles\n");
						printf("	3. Listar preguntas de una categoría\n");
						printf("	4. Eliminar una pregunta\n");
						printf("	0. Salir de la gestión de preguntas y categorías\n");
						scanf("%d",&res2);
					
						switch (res2){
							case 1: // Llamar a función para añadir pregunta
									printf("Añadiendo pregunta...\n");
									break;
							case 2: // Llamar a función para listar categorías
									printf("Listando categorías disponibles...\n");
									break;
							case 3: // Llamar a función para listar preguntas de cada categoría
									printf("\nIntroduce el número de la categoría a listar:\n\n");
									printf("	1. Entretenimiento\n");
									printf("	2. Geografía\n");
									printf("	3. Historia\n");
									printf("	4. Literatura\n");
									printf("	5. Ciencia\n");
									printf("	6. Deportes\n");
									printf("\n	Categoría: ");
									scanf("%d", &cat);
									lista_preguntas(cat);
									break;
							case 4: // Llamar a función para eliminar pregunta
									printf("Eliminando pregunta...\n");
									break;
							default: printf("Introduce un número de acuerdo a las opciones listadas\n");
						}
					}while (res2!=0);
					
					break;
			case 2: do{
						printf("\n	1. Listar preguntas sin moderar\n");
						printf("	2. Aceptar pregunta en moderación\n");
						printf("	3. Denegar pregunta en moderación\n");
						printf("	0. Salir de la moderación\n");
						scanf("%d",&res3);
					
						switch (res3){
							case 1: // Llamar a función para listar preguntas sin moderar
									printf("Listando preguntas sin moderar...\n");
									break;
							case 2: printf("Selecciona el ID de pregunta a aceptar\n");
									// Llamar a función que acepte pregunta
									break;
							case 3: printf("Selecciona el ID de pregunta a denegar\n");
									// Llamar a función que deniegue pregunta
									break;
							default: printf("Introduce un número de acuerdo a las opciones listadas\n");
						}
					}while (res3!=0);
					
					break;
				
			case 3: // Llamar a función que apague el servidor
					printf("Apagando el servidor...\n");
					break;
				
			default: if (res1!=0) {
						printf("Introduce un número de acuerdo a las opciones listadas.\n");
					}
		}
		
	}while (res1!=0);
	
	return 0;
}
