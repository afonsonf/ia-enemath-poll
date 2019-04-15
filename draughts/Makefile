
EXEC_NAME=checkers

CC=g++

CFLAGS= -std=c++11

# Source files
SRC =               \
	main.cpp	\
  board.cpp  \
	minimax.cpp \
	mcts.cpp 	\
	human.cpp

OBJ =  ${SRC:.cpp=.o}

all: ${EXEC_NAME}

${EXEC_NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${EXEC_NAME} ${OBJ} -lreadline

%.o: %.cpp
	${CC} ${CFLAGS} -c -o $@ $+ -lreadline

clean:
	rm ${EXEC_NAME} *.o -rf
