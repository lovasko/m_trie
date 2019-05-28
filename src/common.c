// Copyright (c) 2015-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stdlib.h>

#include "m_trie.h"
#include "common.h"


/// Depth-first traverse the trie and execute an action on each node.
/// NOTE: this function is for internal use only.
/// @return new maximal length of a key
///
/// @param[in] tr   trie
/// @param[in] root node where to start the traversal
/// @param[in] act  action to perform
uint32_t
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
    if (nd->nd_chld == NULL) {
      nd->nd_done = 1;
    }

    // If we have processed all child nodes.
    if (nd->nd_done == 1) {
      // Perform the action on the node.
      del = act(tr, nd);

      // Remove the node from the stack.
      top--;

      // If the node was not deleted by the action, try to update the new
      // maximal length of a key.
      if (del == false && top > newl) {
        newl = (uint32_t)top;
      }
    } else {
      if (nd->nd_chld != NULL) {
        // Advance to the next existing child node.
        for (; nd->nd_cidx < tr->tr_ccnt-1; nd->nd_cidx++) {
          if (nd->nd_chld[nd->nd_cidx] != NULL) {
            break;
          }
        }

        // Mark the node done if all its child nodes were traversed.
        if (nd->nd_cidx == tr->tr_ccnt-1 && nd->nd_chld[nd->nd_cidx] == NULL) {
          nd->nd_done = 1;
        }

        // Add the next node to process to the stack.
        if (nd->nd_done == 0) {
          stack[top + 1] = nd->nd_chld[nd->nd_cidx];
          stack[top + 1]->nd_cidx = 0;
          stack[top + 1]->nd_done = 0;
          top++;

          // Move the pointer to the next node if possible.
          if (nd->nd_cidx == tr->tr_ccnt-1) {
            nd->nd_done = 1;
          } else {
            nd->nd_cidx++;
          }
        }
      }
    }
  }

  free(stack);
  return newl;
}

/// Check the sanity of the user input.
/// NOTE: this function is for internal use only.
/// @return status code
/// @retval M_TRIE_E_NULL    tr and/or key is NULL
/// @retval M_TRIE_E_LENGTH  key length is zero
/// @retval M_TRIE_E_INVALID key contains invalid characters
/// @retval M_TRIE_OK        success
///
/// @param[in] tr  trie
/// @param[in] key key
/// @param[in] len key length
uint8_t
check(const struct m_trie* tr, const uint8_t* key, const uint32_t len)
{
  uint32_t i;
  int16_t h;

  if (tr == NULL || key == NULL) {
    return M_TRIE_E_NULL;
  }

  if (len == 0) {
    return M_TRIE_E_LENGTH;
  }

  // The hash function must return valid value for all elements of the key.
  for (i = 0; i < len; i++) {
    h = tr->tr_hash(key[i]);
    if (h < 0) {
      return M_TRIE_E_INVALID;
    }
  }

  return M_TRIE_OK;
}

/// Locate a node within the trie based on a key.
/// NOTE: this function is for internal use only.
/// @return status code
/// @retval M_TRIE_E_NULL      tr and/or key is NULL
/// @retval M_TRIE_E_LENGTH    key length is zero
/// @retval M_TRIE_E_INVALID   key contains invalid characters
/// @retval M_TRIE_E_NOT_FOUND key is not stored in the trie
/// @retval M_TRIE_OK          success
///
/// @param[in]  tr  trie
/// @param[in]  key key
/// @param[in]  len key length
/// @param[out] out found node
uint8_t
locate(const struct m_trie* tr,
       const uint8_t* key,
       const uint32_t len,
       struct node** out)
{
  struct node* nd;
  uint32_t i;
  int16_t h;
  uint8_t ret;

  // Validate the key.
  ret = check(tr, key, len);
  if (ret != M_TRIE_OK) {
    return ret;
  }

  nd = tr->tr_root;

  // Follow the elements of the key.
  for (i = 0; i < len; i++) {
    // Scenario when there are no more nodes to follow, but the key is still
    // available.
    if (nd->nd_chld == NULL) {
      return M_TRIE_E_NOT_FOUND;
    }

    // Advance to the next node based on the key element.
    h = tr->tr_hash(key[i]);
    nd = nd->nd_chld[h];
    if (nd == NULL) {
      return M_TRIE_E_NOT_FOUND;
    }
  }

  *out = nd;
  return M_TRIE_OK;
}
