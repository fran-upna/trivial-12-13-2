#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Questions.h>
#include <Connector.h>
#include <Socket.h>

Questions *questions;
Connector connector;
int conexion;

int main(int argc, char *argv[]) {
  
	//Peticion de argumentos de entrada correctos
	if(argc!= 3){
	  printf("Parametros de entrada erróneos. USO: ./trivial_server <puerto> <n_max_conexiones>.\n");
	  exit(-1);
	}
	// Indicamos al conector el fichero con las preguntas
	strcpy(connector.questionsFilename, "data/questions.db");

	// Cargamos todas las preguntas en memoria
	questions = Questions_init();
	Questions_load(&connector, questions);

	// Liberamos memoria
	Questions_free(questions);
	
	//Inicializamos el socket conexion en modo servidor
	conexion=Socket_prepararServidor(argv[1], argv[2]);

	return 0;
}
