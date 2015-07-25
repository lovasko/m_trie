#!/bin/sh

INC_DIR=/usr/include
LIB_DIR=/usr/lib

cp -v bin/libmtrie.so "${LIB_DIR}"
cp -v src/m_trie.h "${INC_DIR}"

