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


/// Depth-first traverse the trie and execute an action on each node.
/// @return new maximal length of a key
///
/// @param[in] tr   trie
/// @param[in] root node where to start the traversal
/// @param[in] act  action to perform
static uint32_t
dfs(struct m_trie* tr,
    struct node* root,
    bool (*act)(struct m_trie*, struct node*))
{
  struct node** stack;
  struct node* nd;
  int64_t top;
  uint32_t newl;
  bool del;

  // Initialise the stack structure.
  stack = malloc(sizeof(struct node*) * (tr->tr_maxl + 1));
  top = 0;
  newl = 0;
  stack[0] = root;
  stack[0]->nd_cidx = stack[0]->nd_done = 0;

  // Perform a depth-first traversal of the trie.
  while (top >= 0) {
    nd = stack[top];

    // If there are no child nodes to process.
    if (nd->nd_chld == NULL)
      nd->nd_done = 1;

    // If we have processed all child nodes.
    if (nd->nd_done == 1) {
      // Perform the action on the node.
      del = act(tr, nd);

      // Remove the node from the stack.
      top--;

      // If the node was not deleted by the action, try to update the new
      // maximal length of a key.
      if (del == false && top > newl)
        newl = (uint32_t)top;

    } else {
      if (nd->nd_chld != NULL) {
        // Advance to the next existing child node.
        for (; nd->nd_cidx < tr->tr_ccnt-1; nd->nd_cidx++)
          if (nd->nd_chld[nd->nd_cidx] != NULL)
            break;

        // Mark the node done if all its child nodes were traversed.
        if (nd->nd_cidx == tr->tr_ccnt-1 && nd->nd_chld[nd->nd_cidx] == NULL)
          nd->nd_done = 1;

        // Add the next node to process to the stack.
        if (nd->nd_done == 0) {
          stack[top + 1] = nd->nd_chld[nd->nd_cidx];
          stack[top + 1]->nd_cidx = 0;
          stack[top + 1]->nd_done = 0;
          top++;

          // Move the pointer to the next node if possible.
          if (nd->nd_cidx == tr->tr_ccnt-1)
            nd->nd_done = 1;
          else
            nd->nd_cidx++;
        }
      }
    }
  }

  free(stack);
  return newl;
}

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
  if (nd->nd_type == NODE_DATA)
    tr->tr_kcnt--;

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
/// @param[in] pfix prefix mode
uint8_t
m_trie_remove(struct m_trie* tr,
              const uint8_t* key,
              const uint32_t len,
              const uint8_t pfix)
{
  struct node* nd;
  uint8_t ret;

  // Locate the inner node of the trie.
  ret = locate(tr, key, len, &nd);
  if (ret != M_TRIE_OK)
    return ret;

  // Run a different procedure for prefix and normal removal modes.
  if (pfix) {
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
  if (tr->tr_flags & M_TRIE_CLEANUP)
    m_trie_trim(tr);

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
  if (tr == NULL)
    return M_TRIE_E_NULL;

  // Mark all nodes of the tree to be up for removal.
  dfs(tr, tr->tr_root, mark_to_free);

  // Optionally run the garbage-collection procedure.
  if (tr->tr_flags & M_TRIE_CLEANUP)
    m_trie_trim(tr);

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

  if (tr == NULL)
    return M_TRIE_E_NULL;

  maxl = dfs(tr, tr->tr_root, free_child_nodes);
  tr->tr_maxl = maxl + 1;

  return M_TRIE_OK;
}
