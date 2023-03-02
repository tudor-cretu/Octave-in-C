# Copyright 2022 Echipa PCLP1

# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS = my_octave

build: $(TARGETS)

my_octave: my_octave.c function.c function.h
	$(CC) $(CFLAGS) my_octave.c function.c function.h -o my_octave

pack:
	zip -FSr 315CA_CretuMihneaTudor_Tema2.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean