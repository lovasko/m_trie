CC=clang
CFLAGS=-O3 -Wall -Wextra -Weverything -ansi -pedantic -Wno-documentation-unknown-command

all: words

words: words.c
	$(CC) $(CFLAGS) -fPIC -o words -c words.c

clean:
	rm words
