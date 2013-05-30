#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Questions.h>
#include <Connector.h>
#include <Socket.h>

Questions *questions;
Connector connector;
int conexion;

int* sockets;
char** usuarios;
int MAX_USUARIOS 20;


int main(int argc, char *argv[]) {
  char usuarios[40];
  char socketsusu[40];
  char *datos;
  int numerousuarios;
  char registro;
  char nombre[20];

  
	//Peticion de argumentos de entrada correctos
	if(argc!= 3){
	  printf("Parametros de entrada erróneos. USO: ./trivial_server <puerto> <n_max_conexiones>.\n");
	  exit(-1);
	}

	//Inicializamos el socket conexion en modo servidor
	conexion=Socket_prepararServidor(argv[1], argv[2]);


  sockets = (int*) malloc (N_MAX_USUARIOS*sizeof(int));
  for (i=0;i<MAX_USUARIOS;i+)
    sockets[i]=-1;
  
  usuarios = (char**) malloc (N_MAX_USUARIOS*sizeof(char*));
  for (i=0;i<MAX_USUARIOS;i+)
    usuarios[i]=-1;

/*  
	// Indicamos al conector el fichero con las preguntas
	strcpy(connector.questionsFilename, "data/questions.db");

	// Cargamos todas las preguntas en memoria
	questions = Questions_init();
	Questions_load(&connector, questions);

	// Liberamos memoria
	Questions_free(questions);
*/
	

	
	// REGISTRO DE USUARIO
	datos=Socket_leer(socket);
	sockets[numerousuarios]=socket;
	a=0;
	scanf("%c",&c);
	while (c!=' '){
	  nombre[a]=c;
	  scanf("%c",&c);
	  a++;
	}
	strcpy(usuarios[numerousuarios],nombre);
	registro=Registro_altausuario(int socket, char *datos);
	if (strcmp(registro,"1")==0)	  	Socket_escribir(socket,"O");
	else 					Socket_escribir(socket,"E");

	
	return 0;
}
