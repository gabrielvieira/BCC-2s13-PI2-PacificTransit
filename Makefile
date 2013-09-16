CC= gcc -std=c99
CFLAGS= -W -Wall
EXEC= foca_legal
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIBS=  -lallegro -lallegro_primitives 

all: exemplo

exemplo: $(OBJ)
	$(CC) -o $(EXEC) $^ $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
