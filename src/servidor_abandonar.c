partidas_en_juego

struct partidas{
//if(fgets(f,100,buf)!=NULL){
  if(strncmp(buf,"Abandonar",4)==0){
    mandar_mensajes_ganar_perder(i);
    socket_escribir(sock,"Lost\n");
    socket_escribir(sock2,"Win\n");//No sabemos si es un socket para ambos o 2 sockets


    f=fopen("partidas_en_juego.txt","r");
    g=fopen("partidas_aux.txt","w");
    while(!feof(f)){
      fgets(f,100,buf);
      if(strcmp(buf,partida)!=0)
	fprintf(g,"%s\n",buf);
    }
    fclose(f);
    fclose(g);
    f=fopen("partidas_en_juego.txt","w");
    g=fopen("partidas_aux.txt","r");
    while(!feof(g)){
      fgets(g,100,buf);
      fprintf(f,"%s\n",buf);
    }
    fclose(f);
    fclose(g);

    f=fopen("jugadores_libres.txt","w+");
    socket_escribir(f,"%s\n",jugador1);
    socket_escribir(f,"%s\n",jugador2);
    
    
    lees unn str
    comp
    si no es meter en aux
    si es no meterlo
    llegar fin
    leer y meter todas en 
    
//Eliminar partida    
    eliminar_partida(partidas partida_actual){
      FILE *f,*g;
      partidas aux;
      f=fopen("partidas_en_juego.txt","r");
      g=fopen("partidas_aux.txt","w");
      while(!feof(f)){
	fread(&aux,sizeof(aux),1,f);
	if(strcpy(partida_actual.CodPartida,aux.CodPartida))
	  fwrite(&aux,sizeof(aux),1,g);
      }
      fclose(f);fclose(g);
      f=fopen("partidas_en_juego.txt","w");
      g=fopen("partidas_aux.txt","r");      
      while(!feof(g)){
	fread(&aux,sizeof(aux),1,g);
	fwrite(&aux,sizeof(aux),1,f);
      }
      remove("partidas_aux.txt");
    }
      
      
//Victoria derrota
    mandar_mensajes_ganar_perder(int pos,int* descriptores,char** identificadores){
      char* jugador1,jugador2;
      int i,pos2;
      int len=sizeof(descriptores)/sizeof(int);
      while(!eof(f)){
	fread(&num, sizeof(num), 1,f);
	if (strcpy(partida_actual.CodPartida, num.CodPartida)==0){
	  jugador1=num.jugador1;
	  jugador2=num.jugador2;
	}
      }
      if(strcpy(identificadores[pos],jugador1)==0)
	for(i=0;i<len;i++)
	  if(strcpy(identificadores[i],jugador2)==0)
	    pos2=i;
      else if(strcpy(identificadores[pos],jugador2)==0)
	for(i=0;i<len;i++)
	  if(strcpy(identificadores[i],jugador1)==0)
	    pos2=i;
	  
      socket_escribir(pos,"Lost\n");
      socket_escribir(pos2,"Win\n");
    }
    
    eliminar_usuario(){
      FILE *f,*g, *h;
      partidas num;
      char* jugador1,jugador2;
      f=fopen("partidas_en_juego","r");
      h=fopen("no_disponibles","r");
      g=fopen("aux","w");
      while(!eof(f)){
	fread(&num, sizeof(num), 1,f);
	if (strcpy(partida_actual.CodPartida, num.CodPartida)==0){
	  jugador1=num.jugador1;
	  jugador2=num.jugador2;
	}
      }
      fclose(f);
      while(!eof(h)){
	fread(&num, sizeof(num), 1,h);    
	if ((strcpy(jugador1,num.jugador1)!=0)&&(strcpy(jugador2,num.jugador2)!=0)){
	  fwrite(&num, sizeof(num), 1, g);
	}   
      }
      fclose(h);fclose(g);
      h=open("no_disponibles","w");
      g=open("aux","r");
      while(!eof(g)){
	fread(&num, sizeof(num), 1,g);
	fwrite(&num, sizeof(num), 1, h);
      }
      fclose(h);fclose(g);  
    }
	
      
      
      
      
      
    