CC=clang
CFLAGS=-O3 -Wall -Wextra -Weverything -ansi -pedantic -Wno-documentation-unknown-command
LIB_DIR=/usr/lib
INC_DIR=/usr/include

.PHONY: test

all: bin/libmtrie.so

bin/libmtrie.so: obj/access.o obj/common.o obj/general.o obj/hash.o obj/node.o obj/remove.o
	$(CC) -fPIC -o bin/libmtrie.so -shared obj/access.o obj/common.o obj/general.o obj/hash.o obj/node.o obj/remove.o

obj/access.o: src/access.c
	$(CC) $(CFLAGS) -c src/access.c -o obj/access.o

obj/common.o: src/common.c
	$(CC) $(CFLAGS) -c src/common.c -o obj/common.o

obj/general.o: src/general.c
	$(CC) $(CFLAGS) -c src/general.c -o obj/general.o

obj/hash.o: src/hash.c
	$(CC) $(CFLAGS) -c src/hash.c -o obj/hash.o

obj/node.o: src/node.c
	$(CC) $(CFLAGS) -c src/node.c -o obj/node.o

obj/remove.o: src/remove.c
	$(CC) $(CFLAGS) -c src/remove.c -o obj/remove.o

install:
	cp bin/libmtrie.so $(LIB_DIR)
	cp src/m_trie.h $(INC_DIR)

test:
	(cd test ; ./test.sh)

clean:
	rm obj/*.o
	rm bin/libmtrie.so
