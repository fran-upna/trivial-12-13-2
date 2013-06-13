//Eliminar partida
    eliminar_partida(int s){
      partidas aux,aux2;
      char* jugador;
      for(i=0;descriptores[i]!=NULL;i++){
	if(descriptores[i]==s){
	  jugador=identificadores[i];
	}
      }
      if (ppartidas!=NULL){
	aux=ppartidas;
	if(aux->jugador1==jugador){
	  ppartidas=aux->sig;
	  free(aux);
	}
	else if(aux->jugador2==jugador){
	  ppartidas=aux->sig;
	  free(aux);
	}
	else while(aux->sig!=NULL){
	  if(aux->sig->jugador1==jugador){
	    aux2=aux->sig;
	    aux->sig=aux2->sig;
	    free(aux2);
	  }
	  else if(aux->sig->jugador2==jugador){
	    aux2=aux->sig;
	    aux->sig=aux2->sig;
	    free(aux2);
	  }
	  aux=aux->sig;
	}
	volcar_partidas();
      }
    
    
    
    volcar_partidas(){
      partidas aux;
      FILE* f;
      aux=ppartidas;
      f=fopen("partidas_en_juego.txt","w");
      while(aux->sig!=NULL){
	fwrite(&aux,sizeof(aux),1,f);
	aux=aux->sig;
      }
    }
      
      
      
      
      
 
      
      
//Victoria derrota
    mandar_mensajes_ganar_perder(int s){
      char* jugador,jugador2,msj;
      int i,j;
      
      msj="Lost";
      msj[msj.length]=0;
      socket_escribir(s,msj);
      for(i=0;descriptores[i]!=NULL;i++){
	if(descriptores[i]==s){
	  jugador=identificadores[i];
	}
      }
      for(i=0;partidas_en_juego[i]!=NULL;i++){
	if(strcmp(partidas_en_juego[i].jugador1,jugador)==0){
	  jugador2=partidas_en_juego[i].jugador2;
	  for(j=0;strcmp(jugador2,identificadores[j])!=0;j++){
	      msj="Win";
	      msj[msj.length]=0;
	      socket_escribir(descriptores[j],msj);
	  }
	}
	else if(strcmp(partidas_en_juego[i].jugador2,jugador)==0){
	  jugador2=partidas_en_juego[i].jugador1;
	  for(j=0;strcmp(jugador2,identificadores[j])!=0;j++){
	      msj="Win";
	      msj[msj.length]=0;
	      socket_escribir(descriptores[j],msj);
	  }
	}
      }
    }
      

//eliminar_usuario
    eliminar_usuario(int s){
      char* jugador,jugador2;
      int i,j;
      for(i=0;descriptores[i]!=NULL;i++){
	if(descriptores[i]==s){
	  jugador=identificadores[i];
	}
      }
      for(i=0;partidas_en_juego[i]!=NULL;i++){
	if(strcmp(partidas_en_juego[i].jugador1,jugador)==0){
	  jugador2=partidas_en_juego[i].jugador2;
	  for(j=0;no_disponibles[j]!=NULL;j++){
	    if(strcmp(no_disponibles[j],jugador)==0){
	      for(j;no_disponibles[j+1]!=NULL;j++){
		no_disponibles[j]=no_disponibles[j+1];
	      }
	      no_disponibles[j]=NULL;
	    }
	  }
	  for(j=0;no_disponibles[j]!=NULL;j++){
	    if(strcmp(no_disponibles[j],jugador2)==0){
	      for(j;no_disponibles[j+1]!=NULL;j++){
		no_disponibles[j]=no_disponibles[j+1];
	      }
	      no_disponibles[j]=NULL;
	    }
	  }
	}      
	if(strcmp(partidas_en_juego[i].jugador2,jugador)==0){
	  jugador2=partidas_en_juego[i].jugador1;
	  for(j=0;no_disponibles[j]!=NULL;j++){
	    if(strcmp(no_disponibles[j],jugador)==0){
	      for(j;no_disponibles[j+1]!=NULL;j++){
		no_disponibles[j]=no_disponibles[j+1];
	      }
	      no_disponibles[j]=NULL;
	    }
	  }
	  for(j=0;no_disponibles[j]!=NULL;j++){
	    if(strcmp(no_disponibles[j],jugador2)==0){
	      for(j;no_disponibles[j+1]!=NULL;j++){
		no_disponibles[j]=no_disponibles[j+1];
	      }
	      no_disponibles[j]=NULL;
	    }
	  }
	}
      }
      volcado_no_disponibles();
    }
      
