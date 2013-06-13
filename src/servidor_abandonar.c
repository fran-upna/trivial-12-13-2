
#include <abandonar.h>;



  if(strncmp(buf,"Abandonar",4)==0){
    mandar_mensajes_ganar_perder();
    eliminar_usuario();
    eliminar_partida();
  }
    

