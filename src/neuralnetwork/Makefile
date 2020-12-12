CC=gcc

CPPFLAGS=`pkg-config --cflags sdl` -MMD -g
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g
LDFLAGS=
LDLIBS= -lm
all: xor ocr
xor: toolbox.o xor.o
ocr: toolbox.o ocr.o ./types/matrix.o lecture.o
lecture : lecture.o ./types/matrix.o

xor.o: xor.c network.h
ocr.o: ocr.c network.h lecture.h ./types/matrix.c ./types/matrix.h
lecture.o : lecture.c lecture.h ./types/matrix.c ./types/matrix.h

clean:
	${RM} *.o
	${RM} *.d
	${RM} xor
	${RM} lecture
	${RM} ocr
# END
