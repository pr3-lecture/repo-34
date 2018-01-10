.PHONY: all clean test

all: encrypt decrypt cryptoTest runtest clean

runtest:
	test.exe

encrypt: crypto.o
	gcc -o encrypt crypto.o

decrypt: crypto.o
	gcc -o decrypt crypto.o

cryptoTest: test.o
	gcc -o test test.o

crypto.o: crypto.c
	gcc -Wall -c crypto.c

test.o: test.c
	gcc -Wall -c test.c

clean:
	rm -f run.o test.o crypto.o test decrypt encrypt
