//////////////////////////////////////////
//Prototipos de funciones//
/////////////////////////////////////////

////Preparar conexión servidor.
int Socket_prepararServidor(char p[],char m[]);
////Preparar conexion cliente y establecer con serivor.
int Socket_prepararCliente(char port[],char ip[]);

//Escribir mensajes en un socket
void Socket_escribir(int sock,char msj[]);

// Leer mensajes en un socket
char* Socket_leer(int sock);

