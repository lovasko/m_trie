#ifndef M_TRIE_KEY_H
#define M_TRIE_KEY_H

#include <stdint.h>

#include "m_trie.h"

int key_valid(struct m_trie* trie, char* key, uint32_t key_length);

#endif

