CC=gcc

CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= -lm

all: xor
xor : toolbox.o xor.o

xor.o: xor.c network.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} xor

# END
