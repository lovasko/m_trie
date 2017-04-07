#ifndef M_TRIE_COMMON_H
#define M_TRIE_COMMON_H

#include "m_trie.h"
#include "node.h"


int check(m_trie* trie, uint8_t* key, uint32_t len);
int locate(m_trie* trie, uint8_t* key, uint32_t len, node** nd);

#endif
