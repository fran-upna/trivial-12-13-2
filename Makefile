
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c ${DEBUG} -Iinclude
LFLAGS = -Wall ${DEBUG} -Iinclude

all: folders Questions.o client server

clean:
	rm -f lib/*.o
	rm -rf bin/*.dSYM
	rm -f bin/trivial
	rm -f data/questions.db

server:
	${CC} ${LFLAGS} src/trivial_server.c -o bin/trivial_server lib/Questions.o

client:
	${CC} ${LFLAGS} src/trivial_client.c -o bin/trivial_client lib/Questions.o

Questions.o:
	${CC} ${CFLAGS} src/Questions.c -o lib/Questions.o

folders:
	if [ ! -e lib ]; then mkdir lib; fi
	if [ ! -e bin ]; then mkdir bin; fi
	if [ ! -e data ]; then mkdir data; fi
