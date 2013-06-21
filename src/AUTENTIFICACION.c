#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int autentificacion(char buf[], int c_sock)
{
   char usuario[8], contrasena[8];
   sscanf(buf, "P AUTH %s %s\n",usuario,contrasena); 
   FILE* f = fopen("servidor.cfg", "r");//Este fichero es en el que estan almacenados todos los usuarios registrados
   if(f == NULL)   
      puts("Error al leer el fichero servidor.cfg");
   else
   {
      rewind(f);
      char usuariop[8], contrasenap[8];
      bzero(usuariop,8);
      bzero(contrasenap, 8);     
      // Comprobamos si el usuario existe y la clave es correcta
      int existe = 0;          
      while(fscanf(f, "%s %s\n", usuariop,contrasenap) == 2)
      {        
         if((strcmp(usuario, usuariop) == 0) && (strcmp(contrasena,contrasenap) == 0))
	    existe = 1;
      }				  
      if(existe == 1)
      {
         printf("El usuario %s si existe\n",usuario);
         return 1;
         //escribir(c_sock,"S AUTH OK\n",strlen("S AUTH OK\n"));
      }
      else if(existe == 0)
      {
         printf("El usuario %s no existe\n",usuario);
         return 0;

      }                   
      fclose(f);
   }	
}
