/* Prototipo de la función que inicia el contador
***USO***
La función debe ser llamada desde el cliente en el momento que a este se le plantea la pregunta. Si el contador
que implementa esta función llega a 10, se envía un P_FAIL al servidor y este responderá como deba responder en 
caso de fallo de pregunta. Si se responde la pregunta antes de que el contador llegue a 10, este se parará y seguirá
la ejecución normalmente.
*/

void iniciarContador(FILE* sock);