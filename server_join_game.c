#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <signal.h>
//#include "PartidaType.h"

typedef struct partidas
{
  char *Jugador1,*Jugador2,*Turno,*CodPartida;
  int Pjugador1,Pjugador2;
  struct partidas *sig;
}partidas;

typedef struct nuevas_partidas
{
    char *codPartida,*jugador;
    struct nuevas_partidas *sig;
}nuevas_partidas;



/*		PROBLEMAS GORDOS		*/
/*preguntar la estructura de un fichero de una partida*/
/*	     saber como está compuesto 		*/

char * leer(int c_sock);
void escribir(int c_sock,char *mensaje);
void buscar_contrincante(char **jugador2, char *partida);
void dividir(char ***resul,char *cadena);
void crear_partida(char *, char *, char *);

int main(int argc,char *argv[]) 
{
  int sock,puerto,conexion;
  char *buffer;
  struct in_addr addr;
  struct sockaddr_in servidor;
  struct sockaddr_in cliente;
  buffer=(char *)malloc(60*sizeof(char));
  if(argc != 2)
  {
    printf("Error! Uso: %s <puerto>\n",argv[0]);
    return;
  }
  /* Abrimos el socket */
  sock=socket(PF_INET,SOCK_STREAM,0);
  if (sock==-1) 
  {  

    printf("Error no puedo abrir el socket\n");
    exit(-1);
  } 
  /* Rellenamos la estructura para pedir p  fputs(player1,f); //duda;uerto */
  servidor.sin_family=AF_INET;
  puerto=atoi(argv[1]);
  servidor.sin_port=htons(puerto);
  servidor.sin_addr.s_addr=INADDR_ANY;
  conexion = bind(sock,(struct sockaddr *)&servidor,sizeof(servidor));
  if (conexion ==-1) 
  {
    printf("Error!! no puedo coger el puerto!!!\n");
    exit(-1);
  }
  //else
  printf("Puerto selecionado correctamente. \n");
  listen(sock,5);  
  printf("Escuchando por el puerto %d\n",puerto); 
  int dirlen=sizeof(cliente);
  sock=accept(sock,(struct sockaddr *)&cliente,&dirlen);
  buffer=leer(sock);
  if(strstr(buffer,"P_JOIN\n")!=NULL)
  {
    char **tokens;
    dividir(&tokens,buffer);
    crear_partida(tokens[0],tokens[2],tokens[1]);
  }
}

  //hacer cargar partidas al principio
  
  
//P_DISPONIBLES
char * leer(int c_sock)
{
  int leidos;
  char *buffer;
  FILE *f;
  buffer=(char *)malloc(40*sizeof(char));
  f = fdopen(c_sock ,"w+" );
  setbuf(f,NULL);
  fflush(stdin);
  fgets(buffer,40,f);//Leer
  return buffer;
}

/*Escribir*/
void escribir(int c_sock,char *mensaje)
{
     FILE *f;
     f = fdopen(c_sock ,"w+" );
     setbuf(f,NULL);
     fputs(mensaje,f);
}

void dividir(char ***resul,char *cadena)
{
  int i=0,j=0,k=0;
  char **resultado;
  resultado=(char **)malloc(3*sizeof(char *));
  for(i=0;i<3;i++) resultado[i]=(char *)malloc(30*sizeof(char));
  for(i=0;i<3;i++)
  {
   while(cadena[j]!=' ' && cadena[j]!='\n')
   {
	if(cadena[j]!=' ' && cadena[j]!='\n')
	{
     resultado[i][k]=cadena[j];
     k++;
	}
	j++;
   }
   resultado[i][k]=0;
   j++;
   k=0;
  }
  buscar_contrincante(&resultado[0],resultado[1]);
  i=0;
  while(sockets[i]!=sock)
  {
    i++;
  }
  strcpy(resultado[2],usuarios[i]);
  //resultado sale kon jugador1, nombrepartida, jugador2
  *resul=resultado; 
}

void buscar_contrincante(char **jugador1, char *partida)
{
   struct nuevas_partidas *p,*pant;
   p=p_nuevaspartidas;
   while (strcmp(p->codPartida,partida)!=0)
   {
     pant=p;
     p=p->sig;
   }
    pant->sig=p->sig;
    *jugador1=p->jugador;
    free(p);
    volcar_nuevas_partidas();
}

void crear_partida(char *player1, char *player2, char *game)
{
  struct partidas *P;
  P=(struct partidas *) malloc(sizeof(struct partidas));
  P->CodPartida=game;
  P->Jugador1=player1;
  P->Jugador2=player2;
  P->Turno=player1;
  P->Pjugador1=0;
  P->Pjugador2=0;
  P->sig=ppartidas;
  ppartidas=P; 
}

void crear_lista_partidas()
{
  FILE *f;
  partidas *paux, *p;
  paux=(struct partidas *)malloc(sizeof(struct partidas));
  f=fopen("partidas_en_juego.txt","r");
  if(!feof(f)) fread(&paux,sizeof(struct partidas),1,f);
  ppartidas=paux;
  p=ppartidas;
  while(!feof(f))
  {
    fread(&paux,sizeof(paux),1,f);
    if(!feof(f)) p->sig=paux;
  }
  p->sig=NULL;
}