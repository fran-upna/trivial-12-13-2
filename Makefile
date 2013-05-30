CC = gcc
DEBUG = -g
CFLAGS = -Wall -c ${DEBUG} -Iinclude
LFLAGS = -Wall ${DEBUG} -Iinclude

all: Questions.o Socket.o dice.o listar_cliente.o client server

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
	${CC} ${CFLAGS} src/dice.c -o lib/dice.o

Registro.o:
	${CC} ${CFLAGS} src/Registro.c -o lib/Registro.o

listar_cliente.o:
	${CC} ${CFLAGS} src/listar_cliente.c -o lib/listar_cliente.o

