#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include<Socket.h>
#include<Questions.h>
#include<Question.h>
#include<Connector.h>

void SeleccionCategoria_seleccion(int categoria1, int categoria2, int socket){

	char selec;
	char cat1[2];
	char cat2[2];
	printf("¿Qué categoría deseas seleccionar?(a/b)\n>>");
	scanf("%c",&selec);
	//Seleccionamos la categoria con a o b.
	while(selec!='a'||selec!='b'){
		if(selec=='a'){
			printf("Seleccionada categoría: %d",categoria1);
			sprintf(cat1, "%d", categoria1);
			Socket_escribir(socket, cat1);
		}else if(selec=='b'){
			printf("Seleccionada categoría: %d",categoria2);
			sprintf(cat2, "%d", categoria2);
			Socket_escribir(socket, cat2);
		}else{
			printf("Respuesta incorrecta, vuelve a responder.\n>>");
			scanf("%c",&selec);
		}
	}
	
}


int SeleccionCategoria_Pregunta(int socket){
	
	int correcta;
	//En res 1 se almacena la respuesta correcta.
	char* pregunta;
	char *res1,*res2,*res3,*res4;
	
	pregunta=Socket_leer(socket);
	res1=Socket_leer(socket);
	res2=Socket_leer(socket);
	res3=Socket_leer(socket);
	res4=Socket_leer(socket);
	
	
	//Generamos un numero aleatorio entre 0 y 3 para desordenar las preguntas
	int hora = time(NULL);
	int numero;
	srand(hora);
	numero = rand()%4;
	switch(numero){
	  case 0: printf("¿%s?\n----------------------------------------------------\n",pregunta);
		  printf("\t1-%s.\n\t2-%s.\n\t3-%s.\n\t4-%s.\n",res1,res2,res3,res4);
		  correcta=1;
		  break;
	  case 1: printf("¿%s?\n----------------------------------------------------\n",pregunta);
		  printf("\t1-%s.\n\t2-%s.\n\t3-%s.\n\t4-%s.\n",res4,res3,res2,res1);
		  correcta=4;
		  break;
	  case 2: printf("¿%s?\n----------------------------------------------------\n",pregunta);
		  printf("\t1-%s.\n\t2-%s.\n\t3-%s.\n\t4-%s.\n",res3,res1,res2,res4);
		  correcta=2;
		  break;
	default: printf("¿%s?\n----------------------------------------------------\n",pregunta);
		  printf("\t1-%s.\n\t2-%s.\n\t3-%s.\n\t4-%s.\n",res2,res4,res1,res3);
		  correcta=3;
		  break;
	}

	//Dar valor a correcta segun la posicion que sea, tenemos que saber cual es la correcta de antemano.
	return correcta;

}


void SeleccionCategoria_enviaPreguntas(int sock){
    
    Connector connector;
    
    //Leemos la categoria
    char *cat = Socket_leer(sock);
    int categoria = atoi(cat);
    
    // Indicamos al conector el fichero con las preguntas
    strcpy(connector.questionsFilename, "data/questions.db");

    Questions *questions = Questions_init();
    Questions_load(&connector, questions);
    
    int cuantasEnCategoria = questions->perCategory[categoria];
    srand(time(NULL));
    int cual = rand() % cuantasEnCategoria;

    Question *question = &questions->data[categoria][cual];
    
    char *pregunta = question->question;
    char *respuestaValida = question->valid;
    char *res2 = question->invalid1;
    char *res3 = question->invalid2;
    char *res4 = question->invalid3;
    
    Socket_escribir(sock, pregunta);
    Socket_escribir(sock, respuestaValida);
    Socket_escribir(sock, res2);
    Socket_escribir(sock, res3);
    Socket_escribir(sock, res4);
    
}


