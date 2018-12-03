// Copyright (c) 2015-2018 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stddef.h>
#include <stdint.h>

#include "m_trie.h"
#include "node.h"


/// Initialise the trie.
/// @return status code
/// @retval M_TRIE_E_NULL    tr and/or hash is NULL
/// @retval M_TRIE_E_INVALID hash accepts no inputs
/// @retval M_TRIE_OK        success
///
/// @param[in] tr    trie
/// @param[in] hash  hash function
/// @param[in] flags behaviour flags
int
m_trie_init(struct m_trie* tr, int16_t (*hash)(uint8_t), const uint8_t flags)
{
  uint16_t i;

  if (tr == NULL || hash == NULL)
    return M_TRIE_E_NULL;

  tr->tr_flags = flags;
  tr->tr_hash  = hash;
  tr->tr_kcnt  = 0;
  tr->tr_ncnt  = 0;
  tr->tr_maxl  = 0;

  // Compute the children count, by counting the number of positive answers
  // from the hash function.
  tr->tr_ccnt = 0;
  for (i = 0; i < 256; i++)
    if (hash((uint8_t)i) >= 0)
      tr->tr_ccnt++;

  // Refuse hash functions that accept no inputs.
  if (tr->tr_ccnt == 0)
    return M_TRIE_E_INVALID;

  // Initialise the root node.
  node_init(tr, (struct node**)&tr->tr_root);

  return M_TRIE_OK;
}

/// Free all memory resources held by the trie. Subsequent initialisation
/// and use of the trie is allowed.
/// @return status code
/// @retval M_TRIE_E_NULL tr is NULL
/// @retval M_TRIE_OK     success
///
/// @param[in] tr trie
int
m_trie_free(struct m_trie* tr)
{
  if (tr == NULL)
    return M_TRIE_E_NULL;

  // Mark all tree nodes for removal and ensure that the garbage-collection
  // process is performed.
  tr->tr_flags |= M_TRIE_CLEANUP;
  m_trie_remove_all(tr);
  node_free(tr, (struct node*)tr->tr_root);
  
  // Reset the internal state.
  tr->tr_root  = NULL;
  tr->tr_hash  = NULL;
  tr->tr_ncnt  = 0;
  tr->tr_kcnt  = 0;
  tr->tr_maxl  = 0;
  tr->tr_ccnt  = 0;
  tr->tr_flags = 0;

  return M_TRIE_OK;
}

/// Retrieve the number of stored keys in the trie.
/// @return status code
/// @retval M_TRIE_E_NULL tr and/or cnt are NULL
/// @retval M_TRIE_OK     success
///
/// @param[in]  tr  trie
/// @param[out] cnt number of keys
int
m_trie_count(const struct m_trie* tr, uint64_t* cnt)
{
  if (tr == NULL || cnt == NULL)
    return M_TRIE_E_NULL;

  *cnt = tr->tr_kcnt;
  return M_TRIE_OK;
}
