OBJS = main.o
CFLAGS = -Wall
INCLUDES =
LIBS =
CC = g++

main:${OBJS}
	${CC} ${CFLAGS} ${INCLUDES} -o $@ ${OBJS} ${LIBS}
	
clean:
	-rm -f *.o core *.core
	
.cpp.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $< ${LIBS}

.c.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $< ${LIBS}
