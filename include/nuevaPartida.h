// Prototipos de las funciones de nuevaPartida.c

// PARA EL SERVIDOR
// Iniciar una nueva partida en el servidor. 
void nuevaPartidaClient(int socket);
// Carga de los datos del fichero de no_disponibles en la variable global no_disponibles.
void cargar_no_disponibles();
// Carga de los datos del fichero de nuevas_partidas en la variable global p_nuevaspartidas.
void cargar_nuevas_partidas();
// Volcado de los datos de la variable global no_disponibles en el fichero no_disponibles.
// REQUISITO: DEBE SER EJECUTADA SIEMPRE JUSTO DESPUÉS DE ACTUALIZAR LA VARIABLE para conseguir coherencia con el fichero.
void volcar_no_disponibles();
// Volcado de los datos de la variable global p_nuevaspartidas en el fichero nuevas_partidas.
// REQUISITO: DEBE SER EJECUTADA SIEMPRE JUSTO DESPUÉS DE ACTUALIZAR LA VARIABLE para conseguir coherencia con el fichero.
void volcar_nuevas_partidas();

// PARA EL CLIENTE
// Iniciar una nueva partida en el lado del cliente.
void nuevaPartidaClient(int socket);