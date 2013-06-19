#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Questions.h>
#include <Connector.h>

#include <Registro.h>
#include <nuevaPartida.h>
#include <Socket.h>

Questions *questions;
Connector connector;

int* sockets;
char** usuarios;
int MAX_USUARIOS = 20;

nuevasPartidas *p_nuevaspartidas;
char p_nodisponibles[200][20]; // Por razones de facilidad de programación sólo se podrán tener 199 usuarios en este estado.


int main(int argc, char *argv[]) {
  char *datos;
  int numerousuarios;
  char registro;
  char nombre[20];
  int i = 0;

  sockets = (int*) malloc (MAX_USUARIOS*sizeof(int));
  for (i=0;i<MAX_USUARIOS;i++)
    sockets[i]=-1;
  
  usuarios = (char**) malloc (MAX_USUARIOS*sizeof(char*));
  for (i=0;i<MAX_USUARIOS;i++) {
    usuarios[i]=(char *)malloc(50*sizeof(char));
    usuarios[i][0]=0;
  }
  
	// Indicamos al conector el fichero con las preguntas
	strcpy(connector.questionsFilename, "data/questions.db");

	// Cargamos todas las preguntas en memoria
	questions = Questions_init();
	Questions_load(&connector, questions);

	// TODO!!! Crear el socket, la siguiente línea tiene que ser sustituida
	int sock = 0;

  datos=Socket_leer(sock);
  if(datos[0]=='1'){
    
  }
  else if (datos[0] == '2'){
	// REGISTRO DE USUARIO
	datos=Socket_leer(sock); //Recibe en datos el "usuario clave"
	
	int numerousuarios=0;
	while(sockets[numerousuarios] != -1) { // Buscamos espacio para guardar el usuario
	  numerousuarios++;
	} //El usuario actual y su socket estan en la posicion numerousuarios
	
	sockets[numerousuarios]=sock; // Guardamos el socket del usuario en el array de sockets
	
	int p=0;
	while(datos[p] != ' ') {
	  nombre[p]=datos[p];
	  p++;
	}
	nombre[p]=0;	//Guardamos en nombre el nombre del usuario
	
	strcpy(usuarios[numerousuarios],nombre); // Guardamos el nombre del usuario en el array de usuarios
	
	registro=Registro_altausuario(sock, datos); // Llamo a registro alta usuario con el socket y "usuario clave"
	if (registro == 1) {
	  Socket_escribir(sock,"O"); // Comprobamos si ha ido todo
	}
	else {
	  Socket_escribir(sock,"E"); // correctamente en el alta.
	}
  }

  // Debemos crear el select o el formato de procesos adecuado para hacer que el servidor sea concurrente.

  // Comienzo del protocolo creando una nueva partida.
  // Para encontrar el nombre del usuario se busca sobre la estructura creada de sockets y busca su nombre que se encuentra en la misma posición
  nuevaPartidaServer(sock, /*nombre del usuario*/)
  
  
  
  
  //Funcion que lee a traves del socket la categoria enviada y elegida por el cliente, y le envia al cliente una pregunta aleatoria a traves del 
  //socket con la pregunta, sus respuestas y la respuesta 	que es correcta.
  SeleccionCategoria_enviaPreguntas(sock);

  	// Al terminar la ejecución del programa...
  	// Liberamos memoria
	Questions_free(questions);
	
  return 0;
}
