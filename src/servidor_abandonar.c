

//if(fgets(f,100,buf)!=NULL){
  if(strncmp(buf,"Abandonar",4)==0){
    fprintf(f,"Lost\n");
    fclose(f);
    f=fdopen(sock,"w");
    fprintf("Win\n");
    fclose(f);


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
    fprintf(f,"%s\n",jugador1);
    fprintf(f,"%s\n",jugador2);