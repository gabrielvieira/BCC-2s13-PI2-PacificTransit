CC= gcc -std=c99
CFLAGS= -W -Wall
EXEC= Pacific
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIBS=  -lallegro -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro -lallegro_font -lallegro_ttf -lallegro_image

all: exemplo

exemplo: $(OBJ)
	$(CC) -o $(EXEC) $^ $(CFLAGS) $(LIBS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf *.o
