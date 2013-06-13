#include <stdio.h>
#include <string.h>
#include <QuestionType.h>

void categorias(int x, char cat[]) {
	switch(x) {
		case GEOGRAPHY: strcpy(cat, "GEOGRAPHY");
				break;
		case ENTERTAINMENT: strcpy(cat, "ENTERTAINMENT");
				break;
		case HISTORY: strcpy(cat, "HISTORY");
				break;
		case LITERATURE: strcpy(cat, "LITERATURE");
				break;
		case SCIENCE_NATURE: strcpy(cat, "SCIENCE_NATURE");
				break;
		case SPORTS: strcpy(cat, "SPORTS");
				break;
		default: printf("No existe categoría.\n");
	}
}
