#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>



///////////////////////////////
//Implementacion de funciones//
///////////////////////////////
//Aceptar conexion en servidor
int Socket_esperaConexiones(int sock){
     
    struct sockaddr_in cliente;
    unsigned int dirlen,cone=0;
	  
    dirlen=sizeof(cliente);
    cone = accept (sock, (struct sockaddr *)&cliente,&dirlen); 
    
    if (sock == -1){ 
	printf ("Erro aceptando conexionr\n"); 
	exit(-2);
    }
    printf("Conexion establecida desde la IP %x con el puerto %d.\n----------------------------------------------\n",ntohl(cliente.sin_addr.s_addr),ntohs(cliente.sin_port));
  
    return cone;
}
////Preparar conexión servidor.
int Socket_prepararServidor(char p[],char m[]){
    
    int sock,puerto,max;
    struct sockaddr_in servidor;
  
    puerto=atoi(p);
	max=atoi(m);
    //Se crea el socket
    sock=socket(PF_INET,SOCK_STREAM,0);
    //DATOS DE SERVIDOR A CONECTARSE EL SOCKET//
    //////////////////////////////////////////////////
    servidor.sin_family=AF_INET;
    servidor.sin_port=htons(puerto);
    servidor.sin_addr.s_addr= htonl(INADDR_ANY);
    /////////////////////////////////////////////////
    
    //AVISANDO AL SO DE QUE CREAMOS UN SERVIDOR
    if (bind (sock, (struct sockaddr *)&servidor, sizeof (servidor)) == -1) { 
	    printf ("Error:El puerto esta ocupado\n\n"); 
	    exit(-2);
    }
    //AVISANDO AL SO DE QUE EMPIEZE A ESCUCHAR
    printf("Escuchando conexiones en el puerto: %d\n",puerto);
    if (listen (sock, max) == -1) { 
	    printf ("Error creando servidor\n"); 
	    exit(-2);
    }

    return Socket_esperaConexiones(sock);
}

void Socket_escribit(int sock,char msj[]){
    write(sock,msj,strlen(msj));
    return;
}


