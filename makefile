CC=gcc
CFLAGS=-Wall -g
BIN=./bin
OBJ=./obj
SRC=./src
INC=./include
TARGET=tp1_exec

all: ${BIN}/${TARGET}

${BIN}/${TARGET}: ${OBJ}/excecoes.o ${OBJ}/ordint.o ${OBJ}/main.o
	${CC} ${CFLAGS} -o ${BIN}/${TARGET} ${OBJ}/*.o

${OBJ}/excecoes.o: ${INC}/excecoes.h ${SRC}/excecoes.c
	${CC} ${CFLAGS} -I ${INC}/ -c ${SRC}/excecoes.c -o ${OBJ}/excecoes.o

${OBJ}/ordint.o: ${INC}/excecoes.h ${INC}/ordint.h ${SRC}/ordint.c
	${CC} ${CFLAGS} -I ${INC}/ -c ${SRC}/ordint.c -o ${OBJ}/ordint.o

${OBJ}/main.o: ${SRC}/main.c
	${CC} ${CFLAGS} -I ${INC}/ -c ${SRC}/main.c -o ${OBJ}/main.o

run: all
	${BIN}/${TARGET}

valg: all
	valgrind -q ${BIN}/${TARGET}

gdb: all
	gdb ${BIN}/${TARGET}

clean:
	rm -f ${OBJ}/*.o ${BIN}/tp1_exec