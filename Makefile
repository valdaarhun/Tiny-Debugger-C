CC=gcc
CFLAGS=-Wall

objects = main.o wrappers.o userInput.o tracee.o

dbg: $(objects)
	$(CC) $(CFLAGS) -o $@ $(objects)

main.o: userInput.h wrappers.h tracee.h
wrappers.o: wrappers.h
userInput.o: tracee.h
tracee.o: tracee.h wrappers.h

.PHONY: clean
clean:
	rm $(wildcard *.o) dbg