CC=gcc

CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= -lm

all: xor ocr
xor: toolbox.o xor.o
ocr: toolbox.o ocr.o

xor.o: xor.c network.h
ocr.o: ocr.c network.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} xor

# END
