// Copyright (c) 2015-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stddef.h>
#include <stdint.h>

#include "m_trie.h"
#include "common.h"


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
int
check(const struct m_trie* tr, const uint8_t* key, const uint32_t len)
{
  uint32_t i;

  if (tr == NULL || key == NULL)
    return M_TRIE_E_NULL;

  if (len == 0)
    return M_TRIE_E_LENGTH;

  // The hash function must return valid value for all elements of the key.
  for (i = 0; i < len; i++)
    if (tr->tr_hash(key[i]) < 0)
      return M_TRIE_E_INVALID;

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
int
locate(const struct m_trie* tr,
       const uint8_t* key,
       const uint32_t len,
       struct node** out)
{
  struct node* nd;
  int ret;
  uint32_t i;

  // Validate the key.
  ret = check(tr, key, len);
  if (ret != M_TRIE_OK)
    return ret;

  nd = tr->tr_root;

  // Follow the elements of the key.
  for (i = 0; i < len; i++)
    if (nd->nd_chld == NULL || (nd = nd->nd_chld[tr->tr_hash(key[i])]) == NULL)
      return M_TRIE_E_NOT_FOUND;

  *out = nd;
  return M_TRIE_OK;
}
