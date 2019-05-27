// Copyright (c) 2015-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "m_trie.h"
#include "common.h"
#include "node.h"


/// Mark a node to be freed during the garbage-collection procedure.
/// @return always false, as this function does not actually free the memory
///
/// @param[in] tr unused
/// @param[in] nd node
static bool
mark_to_free(struct m_trie* tr, struct node* nd)
{
  (void)tr;

  // Update the number of stored keys.
  if (nd->nd_type == NODE_DATA) {
    tr->tr_kcnt--;
  }

  nd->nd_type = NODE_TO_FREE;

  // Marking nodes to be freed never actually free any node.
  return 0;
}

/// Deallocate resources for all child nodes marked as to be freed.
/// @return overall free decision
/// @retval false no node was freed
/// @retval true  one or more child nodes were freed
///
/// @param[in] tr trie
/// @param[in] nd node
static bool
free_child_nodes(struct m_trie* tr, struct node* nd)
{
  uint16_t i;
  bool keep;

  keep = false;

  // Traverse all child nodes.
  if (nd->nd_chld != NULL) {
    for (i = 0; i < tr->tr_ccnt; i++) {
      if (nd->nd_chld[i] != NULL) {

        // Free all child nodes that request it.
        if (nd->nd_chld[i]->nd_type == NODE_TO_FREE) {
          node_free(tr, nd->nd_chld[i]);
          nd->nd_chld[i] = NULL;
        } else {
          // Keep this node if some of its child nodes were not marked for
          // removal.
          keep = true;
        }
      }
    }
  }

  // Optionally mark the node for removal.
  if (keep == false && nd->nd_type != NODE_DATA) {
    nd->nd_type = NODE_TO_FREE;
    return true;
  }

  return false;
}

/// Remove a key from the trie.
/// @return status code
/// @retval M_TRIE_E_NULL      tr and/or key is NULL
/// @retval M_TRIE_E_LENGTH    key length is zero
/// @retval M_TRIE_E_INVALID   key contains invalid characters
/// @retval M_TRIE_E_NOT_FOUND key is not in tr
/// @retval M_TRIE_E_NO_VALUE  no value is associated with the key
/// @retval M_TRIE_OK          success
///
/// @param[in] tr   trie
/// @param[in] key  key
/// @param[in] len  key length
/// @param[in] pfix prefix decision
uint8_t
m_trie_remove(struct m_trie* tr,
              const uint8_t* key,
              const uint32_t len,
              const bool pfix)
{
  struct node* nd;
  uint8_t ret;

  // Locate the inner node of the trie.
  ret = locate(tr, key, len, &nd);
  if (ret != M_TRIE_OK) {
    return ret;
  }

  // Run a different procedure for prefix and normal removal modes.
  if (pfix == true) {
    // Traverse the trie to mark all subtree nodes for removal.
    dfs(tr, nd, mark_to_free);
  } else {
    // Optionally deallocate the data associated with the node.
    if (tr->tr_flags & M_TRIE_FREE)
      free(nd->nd_data);

    // Mark the node to be up for removal, so that subsequent trim deletes it.
    nd->nd_type = NODE_TO_FREE;
    nd->nd_data = NULL;

    // Update the number of stored keys.
    tr->tr_kcnt--;
  }

  // Optionally run the garbage-collection procedure.
  if (tr->tr_flags & M_TRIE_CLEANUP) {
    m_trie_trim(tr);
  }

  return M_TRIE_OK;
}

/// Remove all keys from the trie.
/// @returns status code
/// @retval M_TRIE_E_NULL tr is NULL
/// @retval M_TRIE_OK     success
///
/// @param[in] tr trie
uint8_t
m_trie_remove_all(struct m_trie *tr)
{
  if (tr == NULL) {
    return M_TRIE_E_NULL;
  }

  // Mark all nodes of the tree to be up for removal.
  dfs(tr, tr->tr_root, mark_to_free);

  // Optionally run the garbage-collection procedure.
  if (tr->tr_flags & M_TRIE_CLEANUP) {
    m_trie_trim(tr);
  }

  return M_TRIE_OK;
}

/// Garbage-collect nodes that have only regular nodes in their subtree. Such
/// state can arise after one or more calls to one of the m_trie_remove and
/// m_trie_remove_all functions.
/// @return status code
/// @retval M_TRIE_E_NULL tr is NULL
/// @retval M_TRIE_OK     success
///
/// @param[in] tr trie
uint8_t
m_trie_trim(struct m_trie* tr)
{
  uint32_t maxl;

  if (tr == NULL) {
    return M_TRIE_E_NULL;
  }

  maxl = dfs(tr, tr->tr_root, free_child_nodes);
  tr->tr_maxl = maxl + 1;

  return M_TRIE_OK;
}
