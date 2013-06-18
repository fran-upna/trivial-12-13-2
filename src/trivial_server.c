#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Questions.h>
#include <Connector.h>

#include <Registro.h>
#include <nuevaPartida.h>

Questions *questions;
Connector connector;

int* sockets;
char** usuarios;
int MAX_USUARIOS = 20;


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

	// Liberamos memoria
	Questions_free(questions);

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
	
  return 0;
}
