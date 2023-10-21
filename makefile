#Compiler
CC := gcc

#Compiler flags
CFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra -Wpedantic

#Main
MAIN := main.c
#Dependancies
DEPEN := depen/*.c
#Binary name
BIN := asteroids

build:
	${CC} -o ${BIN} ${MAIN} ${DEPEN} ${CFLAGS}

run:
	${CC} -o ${BIN} ${MAIN} ${DEPEN} ${CFLAGS}
	./${BIN}

clean:
	rm -rf ${BIN}
