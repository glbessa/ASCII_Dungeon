CC = gcc
CFLAGS = -Wall -lncurses -I$(IDIR) -g

IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: compile

compile: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o game

run:
	./game

clean:
	rm main