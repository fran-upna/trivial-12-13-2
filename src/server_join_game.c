#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <signal.h>
#include "PartidaType.h"

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
