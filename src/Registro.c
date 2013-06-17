// GRUPO 11:
// Asier Lucas y Jorge Palacios
// Como usuario, quiero poder crear una cuenta usando nombre de usuario y contraseña
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// PARTE SERVIDOR //////////////////////////////////////////////////////////////////
int Registro_comprobarusuarios(char *usuario){
  // Comprobamos si el usuario existia, si estaba dado de alta en el fichero de
  // usuarios registrados, devolvemos 0, si no existía devuelve 1.
  FILE *ficheroservidor;
  int dev=1, noentra=1;
  char usu[20], cla[20];
  ficheroservidor = fopen("usuariosregistrados.cfg","r");

  if(ficheroservidor == NULL) { // si no existe el fichero de usuarios registrados
    dev=1; 
    noentra=0;
  }
   
  if (noentra==1) {
    while(!feof(ficheroservidor)){    
      fscanf(ficheroservidor, "%s %s\n",usu,cla);  
      if (strcmp(usu,usuario)==0) {
	dev=0;
	printf("El usuario existia\n");
      }
    }  
  fclose(ficheroservidor);
  }
  return dev;
}

char Registro_altausuario(int socket, char *envio){
  // Recibimos el socket, y la identificacion del usuario y con estos datos
  // llamamos a la funcion que los guarda en el fichero de registro
  // Devuelve 1 si se ha dado de alta correctamente y 0 si no.
  char usuario[40], clave[40];
  int i=0, a=0;
  while(envio[i]!=' ') { // Extreamos el nombre del usuario.
    usuario[a]=envio[i];
    i++;
    a++;
  }
  usuario[a]=0;

  i++;
  a=0;
  while (envio[i] != 0) { // Extreamos la clave del usuario.
    clave[a]=envio[i];
    i++;
    a++;
  }
  clave[a]=0;
  
  FILE *ficheroservidor;
  if (Registro_comprobarusuarios(usuario)==1) {
    // No existia el usuariosregistrados  
    ficheroservidor = fopen("usuariosregistrados.cfg","a+");
    fprintf(ficheroservidor, "%s",usuario);
    fputc(' ',ficheroservidor);
    fprintf(ficheroservidor, "%s\n", clave);
    fflush(ficheroservidor);
    fclose(ficheroservidor);
    //Confirmacion al cliente registro OK
    return('1');
  }
  else{
    return('0');
  }
}



// PARTE CLIENTE ///////////////////////////////////////////////////////////////////
void Registro_altacliente(int socket, char* envio){
  // Recibe el socket y pedirá al usuario su nombre y su clave para devolverla
  // en la variable envio.
  char usuario[20], clave[20];
  printf("\nIntroduce tu nombre de usuario: ");
  scanf("%s",usuario);
  printf("\nIntroduce tu contraseña: ");
  scanf("%s",clave);
  sprintf(envio,"%s %s",usuario,clave);
}
