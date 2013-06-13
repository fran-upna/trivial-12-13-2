

printf("2.Abandonar\n");

case 2:



  fprintf(f,"Abandonar\n");

  if(fgets(f,100,buf)!=NULL){
    if(strncmp(buf,"Lost",4))
      printf("Has perdido, ahora puedes entrar en otra partida\n");
    else if(strncmp(buf,"Win",3)){    
      printf("Enhorabuena!, has ganado, ahora puedes entrar en otra partida\n");