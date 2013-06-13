#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <Socket.h>

#define Fichero "cliente.cfg"


void unirse_cliente_partida(int sock,cahr **nombrePartidas){
  char *buffer,**resultado,*username;
  int palabras,npartidas,partidaElegida;
  int size_buf = 50;
  
  printf("¿A que numero de partida desea unirse?: ");
  scanf("%d",&partidaElegida);
  printf("Ha elegido la partida %d\n",partidaElegida);
  printf("Estableciendo conexion con la partida %s ... \n",nombrePartidas[partidaElegida-1]);
  //P_JOIN <partida> <miusuario
  username=(char*)malloc(50*sizeof(char));
  unirse_cliente_ConocerNombre(username);
  char *msg_unirse;
  msg_unirse = (char*)malloc(100*sizeof(char));
  sprintf(msg_unirse,"P_JOIN %s %s",username,nombrePartidas[partidaElegida-1]);  
  Socket_escribir(sock,msg_unirse);
 >
  }
  //--Nos unimos a una de las partidas disponibles
  
}
void unirse_cliente_ConocerNombre(char **nombreUser){
  FILE *f;
  f=fopen(Fichero,"r");
  if (!feof(f))
  {
    fgets(nombreUser,60,f);
  }
  fclose(f);
}
