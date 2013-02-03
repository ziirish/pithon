CC=gcc
CFLAGS=-std=c99 -Wall -Werror -W -fno-builtin -g `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_image
SOURCES=$(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=pithon
.PHONY: clean

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)

