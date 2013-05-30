/*Cliente de la Historia : "Listar partidas disponibles" */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

struct Usuario
{
    char *Alias;
    char *id;
    int resultado;
};

#define Fichero "Cliente.cfg"
#define B 60
#define M 60
#define TM 50

void escribir(int ,char *);
void leer_dispo(int ,char *);
void leer(int );
void dividir(char **,char *,int );
int cuentapalabras(char *);


/**PROGRAMA PRINCIPAL**/
int main(int argc,char *argv[])
{
  /*
  int size_buf = 30;
  int npartidas;
  char *buffer;
  */
  //--
  char *buffer,*mensaje,**resultado;
  int sock,puerto,dir_ip,conexion;
    int npartidas;
  struct Usuario User;
  int leidos,opcion,i,palabras,opc;
  char opc2;
  int size_buf/*tamaño del buffer*/,tmsg/*tamaño de mensaje*/;
  FILE *f;
  struct in_addr addr;
  struct sockaddr_in DatoServidor;
  if(argc != 3)
  {
    printf("Error! Uso: %s <direccion_ip> <puerto>\n",argv[0]);
    return;
  }
  /* Abrimos el socket */
  sock=socket(PF_INET,SOCK_STREAM,0);
  if (sock==-1) 
  {
    printf("Error no puedo abrir el socket\n");
    exit(-1);
  }  
  /* Rellenamos la estructura con los datos del servidor */
  DatoServidor.sin_family=AF_INET;
  puerto=atoi(argv[2]);
  DatoServidor.sin_port=htons(puerto);
  if (inet_aton(argv[1], &dir_ip) == 0) 
  {
    perror("inet_aton");
    exit(EXIT_FAILURE);
  }  
  DatoServidor.sin_addr.s_addr=(dir_ip);
    /*Conexion con el servidor*/
  conexion=connect(sock,(struct sockaddr *)&DatoServidor,sizeof(DatoServidor));
  if (conexion==-1) 
  {
    printf("Error no puedo establecer la conexion con el servidor\n");
    exit(-1);
  }
  printf("Conexion establecida correctamente.\n");
  
  
  
  
  
  //-- previamente implemntada la conexion con el server
  //--
  //--Mandamos mensaje para concer las partidas 
  buffer = (char *)malloc(size_buf*sizeof(char));
  escribir(sock,"P_DISPONIBLES\n");
  leer_dispo(sock,buffer);
  palabras=cuentapalabras(buffer);
  resultado=(char **)malloc(palabras*sizeof(char *));
  for(i=0;i<palabras;i++) 
    resultado[i]=(char *)malloc(20*sizeof(char));
  dividir(resultado,buffer,palabras); 
  npartidas = atoi(resultado[1]);
  printf("Numero de partidas disponibles = %d\n",npartidas);
  for(i=0;i<npartidas;i++)
      leer(sock);
  
  
}
/**FIN PROGRAMA PRINCIPAL**/
/**************************/
/**FUNCIONES**/

void escribir(int sock,char *mensaje)
{
  FILE *f;
  f = fdopen(sock,"w+");
  setbuf(f,NULL);
  printf("Enviando %s",mensaje);
  fputs(mensaje,f);
//      fclose(f);
}

void leer_dispo(int sock,char *buffer)
{
  FILE *f;
  f = fdopen(sock ,"r+" );
  setbuf(f,NULL);
  fgets(buffer,20,f);//Leer
  printf("Mensaje del SERVER: %s",buffer);
}
void leer(int sock)
{
  FILE *f;
  int tamano_buf = 60;
  char *msg;
  msg =(char *)malloc(40*sizeof(char));
  f = fdopen( sock ,"w+" );
  setbuf(f,NULL);
  if(!f)
  {
   printf("Error FDOPEN\n"); 
  }
  fgets(msg,tamano_buf,f);//Leer
  printf("Mensaje del SERVER <- <- %s",msg);
//   fclose(f);
}
//s_disponibles X
//x es el numero de partidas disponibles

void dividir(char **resultado,char *cadena,int h)
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

int cuentapalabras(char *cadena)
{
 int cont,contp=0;
 for(cont=0;cont<(strlen(cadena));cont++) if(cadena[cont]==' ') contp++;
 contp++;	//contar la ultima palabra que no ha contado
 return contp;
}
