#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include <categorias.h>
//#include <Questions.h> Eliminado porque lo proporciona ListaPreguntas.h
#include <Connector.h>
#include <ListaPreguntas.h>

#define TAM_BUFF 50

int numclientes;
int N_DESCRIPTORES;
int* descriptores;

Questions *questions;
Connector connector;

void aceptar_nuevo_cliente(int sock);
int comprobar (char cadena[]);
void *apagado(void *arg);

int main (int argc, char * argv[]) {
    int sock, cat;
    struct sockaddr_in servidor;
    char buf[20000];
    int i;
    FILE *f;
    int opcion;
    pthread_t hiloApagado;
    
    // Inicializar el estado del servidor 
    numclientes=0;
	
    if (argc<3){
		printf("Error! La especificación es: servidor <puerto> <número_máximo_de_conexiones>\n");
		exit(-1);
    }
    else if (argc==3) {
		sscanf(argv[2],"%d",&N_DESCRIPTORES); 
    }
    
    // Estructura para guardar todos los sockects de clientes.
    descriptores = (int*) malloc(N_DESCRIPTORES*sizeof(int));
    for (i=0;i<N_DESCRIPTORES;i++) descriptores[i]=-1;	
    
    // Preparación del servidor para conectarlo a la red.
    servidor.sin_family=AF_INET;
    servidor.sin_port=htons(atoi(argv[1]));
    servidor.sin_addr.s_addr=INADDR_ANY;
    sock=socket(PF_INET,SOCK_STREAM,0);
    int err=bind(sock,(struct sockaddr *)&servidor,sizeof(servidor));
    if (err==-1) {
        printf("Error: no puedo coger el puerto\n");
        exit(-1);
    }
    
    // Indicamos al conector el fichero con las preguntas
	strcpy(connector.questionsFilename, "data/questions.db");

	// Cargamos todas las preguntas en memoria
	questions = Questions_init();
	Questions_load(&connector, questions);

    listen (sock, N_DESCRIPTORES);
	printf("Iniciado el servidor de administración de nuestro TRIVIAL.\n");
	printf("Puede escribir 'salir' para apagar el servidor.\n");
    printf("Escuchando conexiones en el puerto %d\n", ntohs(servidor.sin_port));
	
	// Creamos un hilo para leer el apagado del ordenador.
    pthread_create(&hiloApagado, NULL, apagado, NULL);

    while(1) {
        fd_set paraleer;
        int fd_maximo=0;

        // Preparar el conjunto con los sockets que nos interesan 
        FD_ZERO(&paraleer);
        FD_SET(sock,&paraleer); // El original 
	
        fd_maximo=sock; // Para ir calculando el maximo 
        for (i=0;i<N_DESCRIPTORES;i++)
            if (descriptores[i]!=-1) {
                FD_SET(descriptores[i],&paraleer);   // Añadimos cada descriptor abierto 
                fd_maximo= fd_maximo>descriptores[i]?fd_maximo:descriptores[i]; // Y actualizamos el maximo 
            }
        fd_maximo++; // sumamos uno porque select solo mira de 0 a fd_maximo-1 

		if (select(fd_maximo,&paraleer,NULL,NULL,NULL)>0) {
            // Hay algo que leer en alguno 
            if (FD_ISSET(sock,&paraleer))  {
                // Conexion para aceptar 
                aceptar_nuevo_cliente(sock);
            }
            for (i=0;i<N_DESCRIPTORES;i++) {
                if (descriptores[i]!=-1)
                    if (FD_ISSET(descriptores[i],&paraleer)) {
                        // hay algo para leer en el i 
						f=fdopen(descriptores[i],"w+");
						setbuf(f,NULL);
						strcpy(buf,"");
						fgets(buf,TAM_BUFF,f);
						
						if (strlen(buf)>0){
						//Se han recibido datos
							opcion=comprobar(buf);
							//Instrucciones a realizar según los parámetros que lleguen del cliente
							switch(opcion) {
								case 0:		devolverCategorias(descriptores[i]);
											break;
							
								case 1:		//printf("[DEBUG] CAT -> %c\n", buf[16]);
                                            switch(buf[16]) {
                                                case '1':   cat = 1;
                                                            break;
                                                case '2':   cat = 2;
                                                            break;
                                                case '3':   cat = 3;
                                                            break;
                                                case '4':   cat = 4;
                                                            break;
                                                case '5':   cat = 5;
                                                            break;
                                                case '6':   cat = 6;
                                                            break;
                                                default:    printf("[ERROR] Categoría inválida.\n");
                                            }

                                            if(cat >= 1 && cat <= 6) {
                                                devuelvePreguntas(descriptores[i], cat, questions);
                                            }

											break;
							
								default:	printf("Error!! Los parámetros enviados no son correctos\n");
											fclose(f);
											exit(-1);
				
							}// fin switch
						}//fin if (strlen(buf)>0)
						else{
						//buf está vacío, han cerrado sesión
							close(descriptores[i]);
							descriptores[i]=-1;
							numclientes--;
							printf("Un usuario ha cerrado sesión\n");
						}//fin else

                    }//fin if(FD_ISSET...)
            }//fin for
        }// fin if (select...)
    }// fin while
}// fin main

/* Añade un cliente al conjunto de descriptores
 * o lo rechaza si sobrepasa el número de clientes permitidos */
void aceptar_nuevo_cliente(int sock) {
    int c_sock;
    struct sockaddr_in cliente;
    int dirlen=sizeof(cliente);
    int i;

    c_sock=accept(sock, (struct sockaddr *) &cliente, &dirlen);
    if (numclientes<N_DESCRIPTORES) {
    // Todavia hay sitio 
        numclientes++;
        for (i=0;i<N_DESCRIPTORES;i++) {
            if (descriptores[i]==-1) {
                descriptores[i]=c_sock;
                break;
            }
        }
    }
}

/* La función comprobar devuelve un entero diferente
 * según la entrada por parte del cliente
 * o -1 si no es un string esperado */
int comprobar (char cadena[]) {
	int op=-1;

	/*La función strstr busca un substring y devuelve un puntero al mismo*/
	if (strstr (cadena,"C CATEGORY LIST")!=NULL) op=0;
	else if (strstr (cadena,"C QUESTION LIST")!=NULL) op=1;
	/* Y así continuamente hasta acabar con todos los posibles mensajes que reciba el servidor */
	return op;
}

/* La función apagado se encarga de cambiar el tiempo
 * de refresco durante la ejecución del servidor. */
void *apagado(void *arg){
    char s[50];
	while(1){
		scanf("%s", s);
		if((strcmp(s, "salir"))==0){
			printf("Cerrando el programa servidor...\n");
			Questions_free(questions);
			sleep(2);
			exit(0);
		}
	}
}

void devuelvePreguntas(int sock, int cat, Questions *questions) {
    int i;
    Question *q;
    char preg[255], num[5];

    printf("Preguntas totales en la categoría: %d\n", questions->perCategory[cat]);
    sprintf(num, "%d", questions->perCategory[cat]);
    Socket_escribir(sock, num);

    for(i = 0; i < questions->perCategory[cat]; i++) {
        q = &questions->data[cat][i];
        strcpy(preg, q->question);
        Socket_escribir(sock, preg);
    }
}
