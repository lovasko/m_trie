#ifndef M_TRIE_COMMON_H
#define M_TRIE_COMMON_H

#include "m_trie.h"
#include "node.h"


int check(m_trie* trie, char* key, size_t len);
int locate(m_trie* trie, char* key, size_t len, node** nd);

#endif
