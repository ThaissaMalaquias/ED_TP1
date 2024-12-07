CC=gcc
CFLAGS=-Wall -g
BIN=./bin
OBJ=./obj
SRC=./src
INC=./include
TARGET=tp1.out

FILE?=arquivo.xcsv

all: ${BIN}/${TARGET}

${BIN}/${TARGET}: ${OBJ}/excecoes.o ${OBJ}/load.o ${OBJ}/ordind.o ${OBJ}/main.o
	${CC} ${CFLAGS} -o ${BIN}/${TARGET} ${OBJ}/*.o

${OBJ}/excecoes.o: ${INC}/excecoes.h ${SRC}/excecoes.c
	${CC} ${CFLAGS} -I ${INC}/ -c ${SRC}/excecoes.c -o ${OBJ}/excecoes.o

${OBJ}/load.o: ${INC}/load.h ${SRC}/load.c
	${CC} ${CFLAGS} -I ${INC}/ -c ${SRC}/load.c -o ${OBJ}/load.o

${OBJ}/ordind.o: ${INC}/excecoes.h ${INC}/load.h ${INC}/ordind.h ${SRC}/ordind.c
	${CC} ${CFLAGS} -I ${INC}/ -c ${SRC}/ordind.c -o ${OBJ}/ordind.o

${OBJ}/main.o: ${SRC}/main.c
	${CC} ${CFLAGS} -I ${INC}/ -c ${SRC}/main.c -o ${OBJ}/main.o

run: all
	${BIN}/${TARGET} ${FILE}

valg: all
	valgrind -q ${BIN}/${TARGET} ${FILE}

gdb: all
	gdb --args ${BIN}/${TARGET} ${FILE}

clean:
	rm -f ${OBJ}/*.o ${BIN}/${TARGET}