#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Questions.h>
#include <QuestionType.h>
#include <Question.h>
#include <Connector.h>

Questions *Questions_init() {
	Questions *questions = (Questions *)malloc(sizeof(Questions));

	questions->total = 0;
	questions->perCategory[GEOGRAPHY] = 0;
	questions->perCategory[ENTERTAINMENT] = 0;
	questions->perCategory[HISTORY] = 0;
	questions->perCategory[LITERATURE] = 0;
	questions->perCategory[SCIENCE_NATURE] = 0;
	questions->perCategory[SPORTS] = 0;

	return questions;
}

void Questions_addToList(Questions *questions, Question *new) {
	int category = new->category;
	questions->data[category] = (Question *)realloc(questions->data[category], (questions->perCategory[category] + 1) * sizeof(Question));
	questions->total++;
	questions->perCategory[category]++;

	Question *q = &(questions->data[category][questions->perCategory[category] - 1]);
	q->category = new->category;
	strcpy(q->question, new->question);
	strcpy(q->valid, new->valid);
	strcpy(q->invalid1, new->invalid1);
	strcpy(q->invalid2, new->invalid2);
	strcpy(q->invalid3, new->invalid3);
	//memcpy(&(questions->data[category][questions->perCategory[category] - 1]), &new, sizeof(Question));
}

/**
 * Leemos todas las preguntas usando el conector dado
 * 
 * @param  Connector connector
 */
void Questions_load(Connector *connector, Questions *questions) {
	FILE *fd = fopen(connector->questionsFilename, "rb");
	while(!feof(fd)) {
		Question current;
		size_t read = fread(&current, sizeof(Question), 1, fd);
		if(read == 1) {
			Questions_addToList(questions, &current);
		}
	}
	fclose(fd);
}

/**
 * Grabamos todas las preguntas usando conector
 * 
 * @param Connector 	connector
 * @param Question 		questions
 */
void Questions_save(Connector *connector, Questions *questions) {
	int nCategory = 0;
	int nQuestion = 0;

	FILE *fd = fopen(connector->questionsFilename, "wb");

	for(nCategory = 0; nCategory < 6; nCategory++) {
		int nQuestions = questions->perCategory[nCategory];
		for(nQuestion = 0; nQuestion < nQuestions; nQuestion++) {
			Question *question = &questions->data[nCategory][nQuestion];
			fwrite(question, sizeof(Question), 1, fd);
		}
	}

	fclose(fd);
}

/**
 * Añadimos una pregunta al listado y la grabamos usando el conector
 * 
 * @param Connector 	connector
 * @param Questions 	questions
 * @param Question 		question
 */
void Questions_add(Connector *connector, Questions *questions, Question *question) {
	// Grabamos en el fichero
	FILE *fd = fopen(connector->questionsFilename, "ab");
	fwrite(question, sizeof(Question), 1, fd);
	fclose(fd);

	// Actualizamos el listado
	Questions_addToList(questions, question);
}

/**
 * Eliminamos una pregunta
 * 
 * @param Connector 	connector
 * @param Questions 	questions
 * @param QuestionType 	category
 * @param int 			index
 */
void Questions_remove(Connector *connector, Questions *questions, QuestionType category, int index) {
	int nCategory = 0;
	int nQuestion = 0;

	FILE *fd = fopen(connector->questionsFilename, "wb");

	for(nCategory = 0; nCategory < 6; nCategory++) {
		int nQuestions = questions->perCategory[nCategory];
		for(nQuestion = 0; nQuestion < nQuestions; nQuestion++) {
			if(nCategory != category || nQuestion != index) {
				Question *question = &questions->data[nCategory][nQuestion];
				fwrite(question, sizeof(Question), 1, fd);
			}
		}
	}

	fclose(fd);
}

/**
 * Libera la memoria del Questions dado
 * @param Questions	questions
 */
void Questions_free(Questions *questions) {
	free(questions);
}
