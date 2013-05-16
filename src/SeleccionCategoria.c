#include<stdio.h>
#include<stdlib.h>
#include<Socket.h>

void SeleccionCategoria_seleccion(char* categoria1, char* categoria2, int socket){

	char selec;
	printf("¿Qué categoría deseas seleccionar?(a/b)\n>>");
	scanf("%c",&selec);

	while(selec!='a'||selec!='b'){
		if(selec=='a'){
			printf("Seleccionada categoría: %s",categoria1);
			Socket_escribir(socket, categoria1);
		}else if(selec=='b'){
			printf("Seleccionada categoría: %s",categoria2);
			Socket_escribir(socket, categoria2);
		}else{
			printf("Respuesta incorrecta, vuelve a responder.\n>>");
			scanf("%c",&selec);
		}
	}
	
}


char* SeleccionCategoria_Pregunta(int socket){
	
	int i;
	char c;
	char* pregunta,mensaje;
	char* res1, res2, res3, res4;
	mensaje=Socket_leer(int socket);

	c=mensaje[0];
	//Sacamos la pregunta
	while(i=0; c!=' ';i++){
		pregunta[i]=c;
		c=mensaje[i];
	}
	
	//sacamos respuesta1
	c=mensaje[1+i];
	while(i=i; c!=' ';i++){
		res1[i]=c;
		c=mensaje[i];
	}

	//sacamos respuesta2
	c=mensaje[1+i];
	while(i=i; c!=' ';i++){
		res2[i]=c;
		c=mensaje[i];
	}

	//sacamos respuesta3
	c=mensaje[1+i];
	while(i=i; c!=' ';i++){
		res3[i]=c;
		c=mensaje[i];
	}

	//sacamos respuesta4		
	c=mensaje[1+i];
	while(i=i; c!=' ';i++){
		res4[i]=c;
		c=mensaje[i];
	}
	



	printf("¿%s?",pregunta);
	printf("\t1-%s.\n\t2-%s.\n\t3-%s.\n\t4-%s.\n",res1,res2,res3,res4);


}


