#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Connector.h>
#include <Questions.h>
#include <Question.h>

void lista_categorias(int cat) {
	int i;

	Connector connector;
	Questions *preguntas;
	Question preg, *q;
	
	strcpy(connector.questionsFilename, "data/questions.db");
	
	preguntas = Questions_init();
	Questions_load(&connector, preguntas);

	Questions_add(&connector, preguntas, &preg);

	printf("Preguntas totales en la categoría: %d\n", preguntas->perCategory[cat]);

	for(i = 0; i < preguntas->perCategory[cat]; i++) {
		q = &preguntas->data[cat][i];
		printf("Pregunta %d: %s\n", i+1, q->question);
	}

	Questions_free(preguntas);
}
