// GRUPO 11:
// Asier Lucas y Jorge Palacios
// Como usuario, cuando llego a 10 preguntas acertadas, gano la partida y estoy disponible de nuevo. El que pierde está disponible de nuevo

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ganador.h>

void Comprueba_Ganador (char **no_disponibles,char **usuarios char *sockets, partidas *ppartida, int player) { //Depende de lo que nos pasen
  int i,j;
// Cada vez que se acierte una pregunta por uno de los jugadores habrá que lanzar esta funcion
// para comprobar si ha llegado a los 10 aciertos alguno de los dos, si es así mostrará mensaje
// y liberará ambos jugadores para volver a jugar.
// Devuelve 1 si gana el jugador 1 y 0 si gana el jugador 2
  if (ppartida[player].PJugador1==10) {
    printf("El ganador de la partida es el jugador... %s",ppartida[player].Jugador1);
    for (i=0;i<20;i++)
      if (strcmp(ppartida[player].Jugador1,**usuarios[i])==0)
         Socket_escribir(*sockets[i], "Win");
  }
  else if (ppartida[player].PJugador2==10) {
    printf("El ganador de la partida es el jugador... %s",ppartida[player].Jugador2);
    for (j=0;j<20;j++)
      if (strcmp(ppartida[player].Jugador2,**usuarios[j])==0)
         Socket_escribir(*sockets[i], "Win");        
     }
  else {
     return;
  }
  //buscamos al usuario en los arrays de no_disponibles
  for (i=0;i<20;i++) {//20 es el valor de la constante MAX_USUARIOS
    if (strcmp(ppartida[player].PJugador1,**no_disponibles[i])==0) //si encontramos jugador1 en no_disponibles
       Liberar_Jugador(no_disponibles, i);			     //liberarlo
    else if (strcmp(ppartida[player].PJugador2,**no_disponibles[i])==0) //si encontramos jugador2 en no_disponibles
           Liberar_Jugador(no_disponibles, i);	                          //liberarlo
  }
  volcar_no_disponibles();
}


void Liberar_Jugador (char **no_disponibles, int i) {
  while(no_disponibles[i]!=NULL) { // suponemos que el ultimo estara siempre a null
    no_disponibles[i]=no_disponibles[i+1];
    i++;
  }
}









/*
void Liberar_Jugadores (partidas *partida, int player) {
// Liberamos a los jugadores que han terminado una partida, ambos los sacamos del fichero de jugadores no_disponibles.txt que
// están almacenados aquellos que están jugando en es momento, y los volvemos a almacenar en el fichero de dispoibles.txt
  FILE  *f;
  FILE *AUX; 
 // char borra[]="                    ";
  char jugador[20];
  f = fopen("no_disponibles.txt","w+");
  AUX = fopen("auxiliar.txt","w+");
  while (!feof (f)) {
    fscanf(f, "%s\n",jugador);
    if(strcmp(partidas[player].PJugador1,jugador)==0 || strcmp(partidas[player].PJugador2,jugador)==0){	 }
    else
       fprintf(AUX, "%s",jugador);
  }
  fclose(aux);
  fclose(f);
  copy_file("auxiliar.txt","no_disponibles.txt"); 
 
// aqui los dos jugadores que han salido de no disponibles habria que añadirlos al fichero o donde guarden los disponibles no¿?
// que si lo manejan como lo no disponibles seria algo asi....
// g=fopen("disponibles.txt","a");
// fprintf(g, "%s",partidas[player].PJugador1);
// fprintf(g, "%s",partidas[player].PJugador2);
// fclose(g);
}

   

void copy_file(char* f_org,char* f_dest) {				// Función para copiar el fichero fichaux.cfg en servidor.cfg
   FILE *fp_org,*fp_dest;
   char c;
   if (!(fp_org = fopen(f_org,"rt")) || !(fp_dest = fopen(f_dest,"wt"))) {	
      perror("Error de apertura de ficheros");
      exit(EXIT_FAILURE);
   }
   while ((c=fgetc(fp_org)) != EOF && !ferror(fp_org) && !ferror(fp_dest))
      fputc(c,fp_dest);
   if (ferror(fp_org) || ferror(fp_org))
      fclose(fp_org);
   fclose(fp_dest);
}
*/
  
