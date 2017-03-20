#include "m_trie.h"
#include "common.h"
#include "node.h"

/** Search for a key in the trie.
 *
 * @param[in]  trie trie
 * @param[in]  key  key
 * @param[in]  len  key length
 * @param[out] val  data associated with the key
 *
 * @return status code
 * @retval M_TRIE_E_NULL      trie and/or key is NULL
 * @retval M_TRIE_E_LENGTH    length is zero
 * @retval M_TRIE_E_INVALID   key contains invalid characters
 * @retval M_TRIE_E_NOT_FOUND key is not in the trie
 * @retval M_TRIE_OK          success
**/
int
m_trie_search(m_trie* trie, char* key, size_t len, void** val)
{
  node* nd;
  int ret;

  /* Locate the inner node of the trie. */
  ret = locate(trie, key, len, &nd);
  if (ret != M_TRIE_OK)
    return ret;

  /* Check whether the node contains data. */
  if (nd->nd_type != NODE_DATA)
    return M_TRIE_E_NOT_FOUND;

  /* Return the value based on the caller's interest. */
  if (val != NULL)
    *val = nd->nd_data;

  return M_TRIE_OK;
}

/** Insert a value into the trie.
 *
 * @param[in] trie trie
 * @param[in] key  key
 * @param[in] len  key length
 * @param[in] val  data associated with the key
 *
 * @return status code
 * @retval M_TRIE_E_NULL    trie and/or key is NULL
 * @retval M_TRIE_E_LENGTH  key length is zero
 * @retval M_TRIE_E_INVALID key contains an invalid character
 * @retval M_TRIE_E_EXISTS  key exists (only when overwriting is not allowed)
 * @retval M_TRIE_OK        success
**/
int
m_trie_insert(m_trie* trie, char* key, size_t len, void* val)
{
  size_t i;
  int ret;
  short h;
  node* nd;

  /* Validate the key. */
  ret = check(trie, key, len);
  if (ret != M_TRIE_OK)
    return ret;

  nd = trie->tr_root;

  /* Traverse the key. */
  for (i = 0; i < len; i++) {

    /* Remove the removal mark from the node. */
    if (nd->nd_type == NODE_TO_FREE)
      nd->nd_type = NODE_REGULAR;

    /* Create new subtree. */
    if (nd->nd_chld == NULL)
      node_chld(trie, &nd);

    /* Initialise the needed node. */
    h = trie->tr_hash(key[i]);
    if (nd->nd_chld[h] == NULL) {
      node_init(trie, &nd->nd_chld[h]);
      nd->nd_chld[h]->nd_key = key[i];
    }

    /* Advance to the selected/created node. */
    nd = nd->nd_chld[h];
  }

  /* Raise an error if the value can not be overwritten. */
  if (nd->nd_type == NODE_DATA && (trie->tr_flags & M_TRIE_OVERWRITE))
    return M_TRIE_E_EXISTS;

  nd->nd_type = NODE_DATA;
  nd->nd_data = val;

  return M_TRIE_OK;
}
