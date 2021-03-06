// Copyright (c) 2015-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "m_trie.h"
#include "node.h"


/// Initialise a trie node.
/// NOTE: this function is for internal use only.
///
/// @param[in]  tr trie
/// @param[out] nd node
void
node_init(struct m_trie* tr, struct node** nd)
{
  tr->tr_ncnt++;

  *nd = malloc(sizeof(struct node));
  (*nd)->nd_data = NULL;
  (*nd)->nd_type = NODE_REGULAR;
  (*nd)->nd_chld = NULL;
  (*nd)->nd_cidx = 0;
  (*nd)->nd_done = 0;
}

/// Initialise all children of the node.
/// NOTE: this function is for internal use only.
///
/// @param[in] tr trie
/// @param[in] nd node
void
node_chld(const struct m_trie* tr, struct node** nd)
{
  uint16_t i;

  (*nd)->nd_chld = malloc(sizeof(struct node*) * (size_t)tr->tr_ccnt);
  for (i = 0; i < tr->tr_ccnt; i++) {
    (*nd)->nd_chld[i] = NULL;
  }
}

/// Free all memory resources held by the trie node.
/// NOTE: this function is for internal use only.
///
/// @param[in] tr trie
/// @param[in] nd node
void
node_free(struct m_trie* tr, struct node* nd)
{
  tr->tr_ncnt--;

  free(nd->nd_chld);
  free(nd);
}
