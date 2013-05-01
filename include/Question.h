#include <QuestionType.h>

#ifndef QUESTION_H
#define QUESTION_H

typedef struct {
	QuestionType category;
	char question[255];
	char valid[64];
	char invalid1[64];
	char invalid2[64];
	char invalid3[64];
} Question;

#endif
