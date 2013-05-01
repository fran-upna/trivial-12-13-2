#include <QuestionType.h>
#include <Question.h>
#include <Connector.h>

typedef struct {
	// Número total del preguntas (de cualquiera categoría)
	int total;
	// Número de preguntas por categoría
	int perCategory[6];
	// Preguntas por categoría
	Question *data[6];
} Questions;

Questions *Questions_init();
void Questions_load(Connector *connector, Questions *questions);
void Questions_add(Connector *connector, Questions *questions, Question *question);
void Questions_remove(Connector *connector, Questions *questions, QuestionType category, int index);
void Questions_free(Questions *questions);