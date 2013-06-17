
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c ${DEBUG} -Iinclude
LFLAGS = -Wall ${DEBUG} -Iinclude

all: client server

clean:
	rm -f lib/*.o
	rm -rf bin/*.dSYM
	rm -f bin/trivial
	rm -f data/questions.db

server: folders Questions.o Socket.o
	${CC} ${LFLAGS} src/trivial_server.c -o bin/trivial_server lib/Questions.o lib/Socket.o

client: folders Questions.o
	${CC} ${LFLAGS} src/trivial_client.c -o bin/trivial_client lib/Questions.o

Questions.o:
	${CC} ${CFLAGS} src/Questions.c -o lib/Questions.o

folders:
	if [ ! -e lib ]; then mkdir lib; fi
	if [ ! -e bin ]; then mkdir bin; fi
	if [ ! -e data ]; then mkdir data; fi

Socket.o:
	${CC} ${CFLAGS} src/Socket.c -o lib/Socket.o

dice:
	${CC} ${CFLAGS} include/dice.h -o lib/dice.o
tiempo_pregunta:
	${CC} ${CFLAGS} src/tiempo_pregunta.c -o lib/tiempo_pregunta.o

lista_preguntas: folders Questions.o
	${CC} ${CFLAGS} src/ListaPreguntas.c -o lib/ListaPreguntas.o lib/Questions.o

client_admin: folders lista_preguntas Questions.o
	${CC} ${LFLAGS} src/trivial_client_adm.c -o bin/trivial_client_adm lib/ListaPreguntas.o lib/Questions.o
