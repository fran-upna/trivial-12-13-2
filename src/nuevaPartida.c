// PROBLEMAS
// Faltan los /n en el protocolo
// De donde narices sacamos los socket (cliente vale, servidor?, se pretende crear hijos?)
// Info usuario.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Definimos variables de tamaños de los arrays */
#define TAM_BUFF 300


void nuevaPartidaClient(){
	char buffer[TAM_BUFF];
	socket_escribir(/*socket,*/"C NEW GAME\n");
	buffer = socket_leer(/*socket*/);
	printf("La partida se ha creado correctamente. Esperando contrincante...\n");
}

// PENDIENTE VER CÓMO ESTÁ GUARDADA LA INFORMACIÓN DE USUARIO
void nuevaPartidaServer(int socket){
	char peticion[20];
	char user[30];
	// Buscar user segun socket
	
	peticion = socket_leer(/*socket*/);
	if (strstr(peticion,"C NEW GAME\n")!=NULL){
		if (comprobarOcupado(user)==0){
			crearPartida(user);
			registrarUsuarioNoDisponible(user);
			socket_escribir(/*socket,*/"S OK NEW GAME\n");
		} else {
			socket_escribir(/*socket,*/"S ERR NEW GAME\n");
		}
	} else {
		socket_escribir(/*socket,*/"ERROR EN PROTOCOLO");
	}
	
}

int comprobarOcupado(char usuario[]) {
	FILE *f;
	char linea[30];
	int valido=0;//Inicializamos a valido
	
	f=fopen("no_disponibles.txt","r");
	while (!feof(f)){
		fscanf(f,"%s",linea);
		if (strstr (linea,usuario)!=NULL){
			valido=1; //Esta en el fichero de no disponibles
			break;
		}
	}
	fclose(f);
	return valido;
}

void crearPartida(char usuario[]) {
	FILE *f;
	char identPart[9];

	crearIdentificadorPartida(identPart);
	f=fopen("nuevas_partidas.txt","a");
	fprintf(f,"%s %s\n",usuario,identPart);
	fclose(f);
	printf("Se ha creado una nueva partida para el jugador %s\n",usuario);

}

void registrarUsuarioNoDisponible(char usuario[]) {
	FILE *f;
	
	f=fopen("no_disponibles.txt","a");
	fprintf(f,"%s\n",usuario);
	fclose(f);
}

void crearIdentificadorPartida(char identPartida[]){
	int n=8;
	char linea[30];
	char ident[9];
	int valido=1;//Inicializamos a no valido
	FILE *f;
	int ascii,i;
	
	while (valido=1){
		valido=0; // valido hasta que se demuestre lo contrario
		//Crear un identificador
		for (i=0; i<n;i++) {
			do {
				ascii=rand()% 75 + 48;
			} while (((ascii>57)&&(ascii<65))||((ascii>90)&&(ascii<97)));
			ident[i]=(char)ascii;
		}
		ident[n]='\0';
		//Comprobar que no exista
		f=fopen("nuevas_partidas.txt","r");
		if (f == NULL) { // Si no existe el fichero no hay que comprobar
			strcpy(ident,identPartida);
			return;
		}
		while (!feof(f)){
			fscanf(f,"%s",linea);
			if (strstr (linea,ident)!=NULL){
				valido=1; //Repetido
				break;
			}
		}
		fclose(f);
	}
	strcpy(ident,identPartida);
	return;
}
