CC=gcc
CFLAGS=-Wall

objects = main.o wrappers.o userInput.o tracee.o hashTable.o

dbg: $(objects)
	$(CC) $(CFLAGS) -o $@ $(objects)

main.o: userInput.h wrappers.h tracee.h hashTable.h
wrappers.o: wrappers.h
userInput.o: tracee.h
tracee.o: tracee.h wrappers.h
hashTable.o: hashTable.h

.PHONY: clean
clean:
	rm $(wildcard *.o) dbg