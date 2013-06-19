// Prototipos de las funciones de la librería categorias.c

/* 
Prototipo de la función categoria

El primer parámetro indica el número de categoría a obtener, siendo:
	1 - GEOGRAPHY
	2 - ENTERTAINMENT
	3 - HISTORY
	4 - LITERATURE
	5 - SCIENCE_NATURE
	6- SPORTS
	
	El segundo parámetro es un array tipo char donde se almacenará la categoría obtenida.
*/

void categorias(int x, char cat[]);


// Función devolverCategorias para colocar en el lado del Servidor y devolver las categorias de juego del trivial
// Entrada: un entero que indica el socket al que se le deben devolver las categorías.
// Requisitos: haber recibido el mensaje C CATEGORY LIST desde el cliente.
// Salida: ninguna
void devolverCategorias(int socket);


// Función pedirCategorias para colocar en el lado del Cliente y que muestra por pantalla las categorías devueltas por el servidor.
// Entrada: un entero que indica el socket del servidor con el que se va a comunicar.
// Requisitos: no encontrarse en medio de ninguna otra comunicación con el servidor.
// Salida: ninguna.