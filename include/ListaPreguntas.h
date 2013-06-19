// Cliente: le indicamos el número de la categoría y lista las preguntas
void lista_preguntas(int cat, int sock);

// Servidor: empieza a mandar las preguntas al servidor.
void devuelvePreguntas(int sock, int cat, Questions *questions);