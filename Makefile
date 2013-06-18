CC = gcc
DEBUG = -g
CFLAGS = -Wall -c ${DEBUG} -Iinclude
LFLAGS = -Wall ${DEBUG} -Iinclude

all: client server

clean:
	rm -f lib/*.o
	rm -rf bin/*.dSYM
	rm -f bin/*
	> data/questions.db

server: folders Questions.o Socket.o SeleccionCategoria.o
	${CC} ${LFLAGS} src/trivial_server.c -o bin/trivial_server lib/Questions.o lib/Socket.o lib/SeleccionCategoria.o lib/Registro.o

client: folders Questions.o Socket.o SeleccionCategoria.o
	${CC} ${LFLAGS} src/trivial_client.c -o bin/trivial_client lib/Questions.o lib/Registro.o

Questions.o:
	${CC} ${CFLAGS} src/Questions.c -o lib/Questions.o

SeleccionCategoria.o: 
	${CC} ${CFLAGS} src/SeleccionCategoria.c -o lib/SeleccionCategoria.o

folders:
	if [ ! -e lib ]; then mkdir lib; fi
	if [ ! -e bin ]; then mkdir bin; fi
	if [ ! -e data ]; then mkdir data; fi

Socket.o:
	${CC} ${CFLAGS} src/Socket.c -o lib/Socket.o

dice:
	${CC} ${CFLAGS} src/dice.c -o lib/dice.o

Registro.o:
	${CC} ${CFLAGS} src/Registro.c -o lib/Registro.o

categorias:
	${CC} ${CFLAGS} src/categorias.c -o lib/categorias.o

tiempo_pregunta:
	${CC} ${CFLAGS} src/tiempo_pregunta.c -o lib/tiempo_pregunta.o

lista_preguntas: folders Questions.o
	${CC} ${CFLAGS} src/ListaPreguntas.c -o lib/ListaPreguntas.o lib/Questions.o

client_admin: folders lista_preguntas Questions.o
	${CC} ${LFLAGS} src/trivial_client_adm.c -o bin/trivial_client_adm lib/ListaPreguntas.o lib/Questions.o
