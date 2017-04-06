CC=clang
CFLAGS=-O3 -Wall -Wextra -Weverything -ansi -pedantic -Wno-documentation-unknown-command
LDFLAGS=-lmtrie

all: words

words: words.c
	$(CC) $(CFLAGS) -o words words.c $(LDFLAGS)

clean:
	rm words
