#include <stdio.h>
#include <string.h>

#include <Connector.h>
#include <Questions.h>
#include <Question.h>
#include <Socket.h>

void lista_preguntas(int cat, int sock) {
	int i;
	char *preg, *num, msg[17];

	strcpy(msg, "C QUESTION LIST ");
	msg[17] = (char)cat;
    Socket_escribir(sock, msg);

	num = Socket_leer(sock);
	printf("Preguntas totales en la categoría: %s\n", num);

	for(i = 0; i < (int)num; i++) {
		preg = Socket_leer(sock);
		printf("Pregunta %d: %s\n", i+1, preg);
	}
}

void devuelvePreguntas(int sock, int cat, Questions *questions) {
    int i;
    Question *q;
    char preg[255];

    printf("Preguntas totales en la categoría: %d\n", questions->perCategory[cat]);

    for(i = 0; i < questions->perCategory[cat]; i++) {
        q = &questions->data[cat][i];
        strcpy(preg, q->question);
        Socket_escribir(sock, preg);
    }
}
