/*Cliente de la Historia : "Listar partidas disponibles" */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <Socket.h>


/**FUNCIONES**/

//s_disponibles X
//x es el numero de partidas disponibles

void listar_cliente_pdisponibles(int sock)
{
  char *buffer, **resultado;
  int size_buf = 30;
  int npartidas,palabras,i;

  //buffer = (char *)malloc(size_buf*sizeof(char));
  Socket_escribir(sock,"P_DISPONIBLES");
  //escribir(sock,"P_DISPONIBLES\n");
  buffer = Socket_leer(sock);
  //leer_dispo(sock,buffer);
  palabras = listar_cliente_cuentapalabras(buffer);
  resultado = (char **)malloc(palabras*sizeof(char *));
  for(i=0;i<palabras;i++) 
    resultado[i]=(char *)malloc(size_buf*sizeof(char));
  listar_cliente_dividir(resultado,buffer,palabras); 
  npartidas = atoi(resultado[1]);
  char nombrePartidas[npartidas];
  printf("Numero de partidas disponibles = %d\n",npartidas);
  printf("Estas son las %d partidas disponibles: \n",npartidas);
  for(i=0;i<npartidas;i++)
  {    
     nombrePartidas[i] = Socket_leer(sock);
     printf("%d.- Partida con nombre '%s'\n",i+1,nombrePartidas[i])
  }  
//   free();
}



void listar_cliente_dividir(char **resultado,char *cadena,int h)
{
   int i=0,j=0,k=0;
  for(i=0;i<h;i++)
  {
   while(cadena[j]!=' ' && cadena[j]!='\n')
   {
     resultado[i][k]=cadena[j];
     j++;
     k++;
   }
   resultado[i][k]=0;
   j++;
   k=0;
  }
}

int listar_cliente_cuentapalabras(char *cadena)
{
 int cont,contp=0;
 for(cont=0;cont<(strlen(cadena));cont++) if(cadena[cont]==' ') contp++;
 contp++;	//contar la ultima palabra que no ha contado
 return contp;
}
