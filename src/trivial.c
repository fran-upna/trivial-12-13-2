#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Questions.h>
#include <Connector.h>

Questions *questions;
Connector connector;

int main(int argc, char *argv[]) {
	// Indicamos al conector el fichero con las preguntas
	strcpy(connector.questionsFilename, "data/questions.db");

	// Cargamos todas las preguntas en memoria
	questions = Questions_init();
	Questions_load(&connector, questions);

	// Liberamos memoria
	Questions_free(questions);

	return 0;
}
