CC=gcc
CFLAGS=-Wall

objects = main.o wrappers.o

dbg: $(objects)
	$(CC) $(CFLAGS) -o $@ $(objects)

$(objects): wrappers.h

.PHONY: clean
clean:
	rm $(wildcard *.o) dbg