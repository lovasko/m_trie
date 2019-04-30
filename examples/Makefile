# Copyright (c) 2015-2019 Daniel Lovasko
# All Rights Reserved
#
# Distributed under the terms of the 2-clause BSD License. The full
# license is in the file LICENSE, distributed as part of this software.

CC=cc
CFLAGS=-O3 -Wall -Wextra -std=c99
LDFLAGS=-lmtrie

all: words

words: words.c
	$(CC) $(CFLAGS) -o words words.c $(LDFLAGS)

clean:
	rm words
