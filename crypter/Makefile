.PHONY: all clean test

all: encrypt decrypt cryptoTest runtest clean

runtest: test.exe

encrypt: gcc -o encrypt main.c crypto.c

decrypt: gcc -o decrypt main.c crypto.c

test:	gcc -o test test.c crypto.c

clean:
	rm -f encrypt.exe decrypt.exe test.exe
