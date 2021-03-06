# Copyright (c) 2015-2019 Daniel Lovasko
# All Rights Reserved
#
# Distributed under the terms of the 2-clause BSD License. The full
# license is in the file LICENSE, distributed as part of this software.

CC=cc
WARNINGS=-Wall -Wextra -Werror -fstrict-aliasing
STANDARDS=-std=c99
CFLAGS=-O3 -fPIC $(WARNINGS) $(STANDARDS)
LDFLAGS=-fPIC
LIB_DIR=/usr/lib
INC_DIR=/usr/include

all: bin/libmtrie.so

bin/libmtrie.so: obj/access.o  \
                 obj/common.o  \
                 obj/general.o \
                 obj/hash.o    \
                 obj/node.o    \
                 obj/remove.o
	$(CC) $(LDFLAGS) -shared -o bin/libmtrie.so \
                 obj/access.o  \
                 obj/common.o  \
                 obj/general.o \
                 obj/hash.o    \
                 obj/node.o    \
                 obj/remove.o

obj/access.o: src/access.c
	$(CC) $(CFLAGS) -c src/access.c  -o obj/access.o

obj/common.o: src/common.c
	$(CC) $(CFLAGS) -c src/common.c  -o obj/common.o

obj/general.o: src/general.c
	$(CC) $(CFLAGS) -c src/general.c -o obj/general.o

obj/hash.o: src/hash.c
	$(CC) $(CFLAGS) -c src/hash.c    -o obj/hash.o

obj/node.o: src/node.c
	$(CC) $(CFLAGS) -c src/node.c    -o obj/node.o

obj/remove.o: src/remove.c
	$(CC) $(CFLAGS) -c src/remove.c  -o obj/remove.o

install:
	cp bin/libmtrie.so $(LIB_DIR)
	cp src/m_trie.h $(INC_DIR)

test:
	(cd test ; bash test.sh)

clean:
	rm -f bin/libmtrie.so
	rm -f obj/access.o
	rm -f obj/common.o
	rm -f obj/general.o
	rm -f obj/hash.o
	rm -f obj/node.o
	rm -f obj/remove.o
