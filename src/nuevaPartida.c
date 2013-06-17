#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct users{
	char *codigo;
	int ocupado; /* Ocupado=1, Libre=0 */
	struct users *sig;
}usuario;


typedef struct nuevas_partidas{
	char *codPartida, *jugador;
	struct nuevas_partidas *sig;
} nuevas_partidas;

/*struct partidas{
	char *codigo;
	char *usuario1;
	struct partidas *sig;
	// Mas campos?
}partidas;*/

//struct users *us;
//struct partidas *part;

/* Definimos variables de tamaños de los arrays */
#define TAM_BUFF 300


void nuevaPartidaClient(int socket){
	char buffer[TAM_BUFF];
	Socket_escribir(socket, "C NEW GAME\n");
	buffer = Socket_leer(socket);
		if(strcmp(buffer, "S OK NEW GAME"));
			printf("La partida se ha creado correctamente. Esperando contrincante...\n");
		else 
			printf("Problemas al crear la partida. Intentando de nuevo...");
}

void nuevaPartidaServer(int socket,char user[]){
	char peticion[20];
	
	//Cargar_datos(us);	// TIENE QUE ESTAR EN EL PROGRAMA PRINCIPAL
	//Cargar_datos(part); // TIENE QUE ESTAR EN EL PROGRAMA PRINCIPAL
	
	peticion = Socket_leer(socket);
	if (strstr(peticion,"C NEW GAME")!=NULL){
		if (comprobarOcupado(user)==1){
			crearPartida(user);
			registrarUsuarioNoDisponible(user);
			Socket_escribir(socket,"S OK NEW GAME");
		} else {
			Socket_escribir(socket,"S ERR NEW GAME");
		}
	} else {
		Socket_escribir(socket,"ERROR EN PROTOCOLO");
	}
	
}

void nuevaPartidaClient

/*int comprobarOcupado(char usuario[]) {
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
}*/

/*int comprobarOcupado(char usuario[]){
	int ok=-1;
	struct users *u; //Nuevo puntero a estructura
	u=us; //El nuevo puntero apunta al primer usuario
	do{
		if (strcmp(((*u).codigo),usuario)==0){
			ok=0;
			if (((*u).codigo)=0){
				ok=1;
				((*u).ocupado)=1;
			}	
		}
		u=(*u).sig; //El puntero apunta al siguiente usuario
	}while((u!=NULL)&&(ok==0));
	// Si no se ha encontrado el usuario, ok vale -1
	// Si el usuario estaba ocupado, ok vale 0
	// Si todo ha ido bien, vale 1
	return (ok);
}*/

int comprobarOcupado(char usuario[]){
	// no_disponibles** variable global;
	int ok=-1, i=1;
	if(no_disponibles!=NULL)
		if(strcmp(no_disponibles[0], usuario)==0)
			return 0;
		else{
			while (no_disponibles[i]!=NULL){
				if(strcmp(no_disponibles[i], usuario)==0)
					return 0;
				i++;
			}
			return 1;
		}
	else 
		// Esta opción no tiene sentido ya, es igual que el 0
		return -1;
}

void crearPartida(char usuario[]) {
	//FILE *f;
	struct nuevas_partidas *p, *p_nueva;
	char identPart[9];
	// p_nuevaspartidas variable global;

	crearIdentificadorPartida(identPart);
	//f=fopen("nuevas_partidas.txt","a");
	//fprintf(f,"%s %s\n",usuario,identPart);
	//fclose(f);
	
	/*p=part;
	do{
			p=(*p).sig; //El puntero apunta al siguiente usuario
	}while(p!=NULL); //Hasta situarnos en la partida nula
	struct partidas *p_nueva;
    p_nueva=(partidas*) malloc(sizeof(partidas));
    strcpy(((*p_nueva).codigo),identPart);
	strcpy(((*p_nueva).usuario1),usuario);
	(*p_nueva).sig=NULL;
	((*p).sig)=p_nueva; // Como es un puntero, se añade también a part
	//volcar_datos(part);*/
	
	// Rellenamos la nueva celda de nueva_partida
    p_nueva=(nuevas_partidas*) malloc(sizeof(nuevas_partidas));
    strcpy((p_nueva->codPartida),identPart);
	strcpy((p_nueva->jugador),usuario);

	// Buscamos la primera posición donde podemos colocar la siguiente partida.
	p=p_nuevaspartidas;
	if(p!=NULL){ // Ya estamos en la partida nula
		while(p->sig!=NULL){
			p=p->sig;//El puntero apunta al siguiente usuario hasta situarnos en la partida nula
		}
	}

	p_nueva->sig=NULL;
	((*p)->sig)=p_nueva; // Como es un puntero, se añade también a part
	volcar_nuevas_partidas();
}

/*void registrarUsuarioNoDisponible(char usuario[]) {
	FILE *f;
	
	f=fopen("no_disponibles.txt","a");
	fprintf(f,"%s\n",usuario);
	fclose(f);
}*/

void registrarUsuarioNoDisponible(char usuario[]) {
	/*int ok=0;
	struct users *u; //Nuevo puntero a estructura
	u=us; //El nuevo puntero apunta al primer usuario
	do{
		if (strcmp(((*u).codigo),usuario)==0){
			((*u).ocupado)=1;
			ok=1;
		}
		u=(*u).sig; //El puntero apunta al siguiente usuario
	}while((u!=NULL)&&(ok==0));
	//volcar_datos(us);
	// Si no se ha encontrado el usuario, ok vale 0
	// Si se ha encontrado, vale 1*/
	// no_disponibles** variable global;

	int i=1;
	if(no_disponibles!=NULL){
		while (no_disponibles[i]!=NULL)
			i++;
		no_disponibles[i] = (char*) malloc(sizeof(usuario)); // ESTO SE PUEDE??
		strcpy(no_disponibles[i],usuario);
		no_dispoibles[i+1] = NULL;
	}
	else {
		no_disponibles[0] = (char*) malloc(sizeof(usuario)); // ESTO SE PUEDE??
		strcpy(no_disponibles[0],usuario);
		no_dispoibles[1] = NULL;
	}
}

void crearIdentificadorPartida(char identPartida[]){
	int n=8;
	char linea[30];
	char ident[9];
	int valido=1;//Inicializamos a no valido
	FILE *f;
	int ascii,i;
	struct nuevas_partidas *np;	// p_nuevaspartidas variable global
	struct partidas *p;  // p_partidas variable global
	
	while (valido==1){
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
		p=part;
		do{
			if (strcmp(((*p).codigo),ident)==0){
				valido=0;
			}
			p=(*p).sig; //El puntero apunta al siguiente usuario
		}while(p!=NULL);

		p=p_partidas;
		if (p==NULL)
			valido=0;
		else 
			if(strcmp(ident, p->codPartida)==0)
				valido=0;
			else
				while(p->sig!=NULL){
					p=p->sig;
					if(strcmp(ident, p->codPartida)==0){
						valido=0;
						break;
					}
				}

		np=p_nuevaspartidas;
		if (np==NULL)
			valido=0;
		else 
			if(strcmp(ident, np->codPartida)==0)
				valido=0;
			else
				while(np->sig!=NULL){
					np=np->sig;
					if(strcmp(ident, np->codPartida)==0){
						valido=0;
						break;
					}
				}

		/*f=fopen("nuevas_partidas.txt","r");
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
		fclose(f);*/
		
	}
	strcpy(ident,identPartida);
	return;
}

void cargar_nuevas_partidas(){
	// Se define como variable global: p_nuevaspartidas
	FILE* f;
	nuevas_partidas* np, npp;
	char buff[100];

	f=fopen("nuevas_partidas.txt","r");
	if(f!=NULL){
		while(!feof(f)){
			if(p_nuevaspartidas==NULL){
				fgets(buff, 100, f);
				p_nuevaspartidas=(nuevas_partidas*) malloc(sizeof(nuevas_partidas));
				p_nuevaspartidas->codPartida = obtenerCodPartida(buff);
				p_nuevaspartidas->jugador = obtenerJugador(buff);
				p_nuevaspartidas->sig=NULL;
			}
			else{
				if(p_nuevaspartidas->sig==NULL){
					np = (nuevas_partidas*) malloc(sizeof(nuevas_partidas));
					p_nuevaspartidas->sig = np;
					np->codPartida = obtenerCodPartida(buff);
					np->jugador = obtenerJugador(buff);
					np->sig = NULL;
				}
				else{
					fgets(buff, 100, f);
					npp=p_nuevaspartidas->sig;
					while(npp->sig!=NULL)
						npp = npp->sig;
					np = (nuevas_partidas*) malloc(sizeof(nuevas_partidas));
					np->codPartida = obtenerCodPartida(buff);
					np->jugador = obtenerJugador(buff);
					np->sig = NULL;
					npp->sig=np;
				}
			}
		}
	}
	fclose(f);
}

void volcar_nuevas_partidas(){
	// Se define como variable global: p_nuevaspartidas
	FILE* f;
	nuevas_partidas* np;
	char buff[100];

	f=fopen("nuevas_partidas.txt","w+");
	if(f!=NULL){
		if(p_nuevaspartidas==NULL){
			fclose(f);
			return;
		}
		else{
			np = p_nuevaspartidas;
			while(np->sig!=NULL){
				fprintf(f,"%s %s\n", np->jugador, np->codPartida);
				np = np->sig;
			}
			fprintf(f,"%s %s\n", np->jugador, np->codPartida);
		}
	}
	else{
		printf("ERROR en el volcado de los datos al fichero de nuevas partidas.");
	}
	fclose(f);
}

char* obtenerCodPartida(char* buff){
	char[9] ident;
	int i=0, j=0;

	while(buff[i]!=' ')
		i++;
	i++;
	while(buff[i]!='\0'&&j<9){
		ident[j]=buff[i];
		i++;
		j++;
	}

	return ident;
}

char* obtenerNombre(char* buff){
	char[30] nom;
	int i=0, j=0;

	while(buff[i]!=' '){
		nom[j]=buff[i];
		i++;
		j++;
	}
}