CC = gcc
CFLAGS = -Wall -g
LIB = -lm
HDR = data.h list.h tree.h utils.h

SRC1 = map1.c data.c list.c tree.c utils.c
OBJ1 = $(SRC1:.c=.o)
EXE1 = map1

SRC2 = map2.c data.c list.c tree.c utils.c
OBJ2 = $(SRC2:.c=.o)
EXE2 = map2

all: $(EXE1) $(EXE2)
$(EXE1): $(HDR) $(OBJ1)
	$(CC) $(CFLAGS) -o $(EXE1) $(OBJ1) $(LIB)

$(EXE2): $(HDR) $(OBJ2)
	$(CC) $(CFLAGS) -o $(EXE2) $(OBJ2) $(LIB)

clean:
	rm -f $(EXE1) $(EXE2) *.o

$(OBJ1): $(HDR)
$(OBJ2): $(HDR)