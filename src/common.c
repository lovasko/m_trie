#include "m_trie.h"
#include "common.h"


/** Check the sanity of the user input.
  * NOTE: this function is for internal use only.
  *
  * @param[in] trie trie
  * @param[in] key  key
  * @param[in] len  key length
  *
  * @return status code
  * @retval M_TRIE_E_NULL    trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH  key length is zero
  * @retval M_TRIE_E_INVALID key contains invalid characters
  * @retval M_TRIE_OK        success
**/
int
check(m_trie* trie, char* key, size_t len)
{
  size_t i;

  if (trie == NULL || key == NULL)
    return M_TRIE_E_NULL;

  if (len == 0)
    return M_TRIE_E_LENGTH;

  /* The hash function must return valid value for all
   * elements of the key. */
  for (i = 0; i < len; i++)
    if (trie->tr_hash(key[i]) < 0)
      return M_TRIE_E_INVALID;

  return M_TRIE_OK;
}

/** Locate a node within the trie based on a key.
  * NOTE: this function is for internal use only.
  *
  * @param[in]  trie trie
  * @param[in]  key  key
  * @param[in]  len  key length
  * @param[out] out  found node
  *
  * @return status code
  * @retval M_TRIE_E_NULL      trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH    key length is zero
  * @retval M_TRIE_E_INVALID   key contains invalid characters
  * @retval M_TRIE_E_NOT_FOUND key is not stored in the trie
  * @retval M_TRIE_OK          success
**/
int
locate(m_trie* trie, char* key, size_t len, node** out)
{
  node* nd;
  size_t i;
  int ret;

  /* Validate the key. */
  ret = check(trie, key, len);
  if (ret != M_TRIE_OK)
    return ret;

  nd = trie->tr_root;

  /* Follow the elements of the key. */
  for (i = 0; i < len; i++)
    if (nd->nd_chld == NULL
     || (nd = nd->nd_chld[trie->tr_hash(key[i])]) == NULL)
      return M_TRIE_E_NOT_FOUND;

  *out = nd;
  return M_TRIE_OK;
}
