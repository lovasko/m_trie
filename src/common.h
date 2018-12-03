// Copyright (c) 2015-2018 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#ifndef M_TRIE_COMMON_H
#define M_TRIE_COMMON_H

#include "m_trie.h"
#include "node.h"


int check(m_trie* tr, uint8_t* key, uint32_t len);
int locate(m_trie* tr, uint8_t* key, uint32_t len, node** nd);

#endif
