#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <signal.h>
#include <Socket.h>

void Send_Games(int sock,char *nombre);
int Count_Games(char *nombre);

void Send_Games(int sock,char *nombre)	
{
    int i,cantidad=Count_Games(nombre);
    FILE *f;
    char *auxiliar;
    f=fopen(nombre,"r");
    auxiliar=(char *)malloc(20*sizeof(char));
    sprintf(auxiliar,"S_DISPONIBLES %d\n",cantidad);
    Socket_escribir(auxiliar);
    for(i=0;i<cantidad;i++)
    {
	  fgets(auxiliar,20,f);
	  if(!feof(f)) Socket_escribir(auxiliar);
    }
    fclose(f);  
}

int Count_Games(char *nombre)
{
   int partidas=0;
   FILE *f;  
   char *auxiliar;
   f=fopen(nombre,"r");
   auxiliar=(char *)malloc(20*sizeof(char));
   while(!feof(f))
    {
	  fgets(auxiliar,30,f);
	  partidas++;
    }
    partidas--;
   return partidas;
}