// Prototipos de las funciones de dice.c

// Servidor: envía al socket las dos categorías y el dado.
void tirarDado(FILE *sock);

// Cliente: recibe las dos categorías desde el socket.
void recibirCategoria(char cat1[], char cat2[]);