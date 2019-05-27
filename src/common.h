// Copyright (c) 2015-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#ifndef M_TRIE_COMMON_H
#define M_TRIE_COMMON_H

#include <stdbool.h>
#include <stdint.h>

#include "m_trie.h"
#include "node.h"


uint32_t dfs(struct m_trie* tr,
             struct node* root,
             bool (*act)(struct m_trie*, struct node*));
uint8_t check(const struct m_trie* tr, const uint8_t* key, const uint32_t len);
uint8_t locate(const struct m_trie* tr,
               const uint8_t* key,
               const uint32_t len,
               struct node** nd);

#endif
