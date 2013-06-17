#include <stdio.h>
#include <string.h>
#include <Connector.h>
#include <Questions.h>
#include <Question.h>

int main(void) {
	int cat;

	printf("Indique la categoría de la que desea listar las preguntas: ");
	scanf("%d", &cat);

	Connector connector;
	Questions *preguntas;
	Question preg, preg2, preg3;
	
	strcpy(connector.questionsFilename, "data/questions.db");
	
	preguntas = Questions_init();
	Questions_load(&connector, preguntas);
	
	// Creamos dos preguntas de ejemplo
	preg.category = ENTERTAINMENT;
	strcpy(preg.question, "Pregunta1");
	strcpy(preg.valid, "Valida");
	strcpy(preg.invalid1, "Invalida1");
	strcpy(preg.invalid2, "Invalida2");
	strcpy(preg.invalid3, "Invalida3");
	
	preg3.category = ENTERTAINMENT;
	strcpy(preg3.question, "Pregunta2");
	strcpy(preg3.valid, "Valida2");
	strcpy(preg3.invalid1, "Invalida12");
	strcpy(preg3.invalid2, "Invalida22");
	strcpy(preg3.invalid3, "Invalida32");

	Questions_add(&connector, preguntas, &preg);
	Questions_add(&connector, preguntas, &preg3);

	Questions_load(&connector, preguntas);

	printf("Mostramos las preguntas: \n");
	
	preg2 = *(preguntas -> data[cat]);
	
	printf("Pregunta 1 -> %s\n", preg2.question);
	
	preg2 = *(preguntas -> data[cat]);
	
	printf("Pregunta 2 -> %s\n", preg2.question);
	
	return 0;
}
