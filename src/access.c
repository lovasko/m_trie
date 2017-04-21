#include "m_trie.h"
#include "common.h"
#include "node.h"


/** Search for a value in the trie based on a key.
  *
  * @param[in]  tr  trie
  * @param[in]  key key
  * @param[in]  len key length
  * @param[out] val data associated with the key
  *
  * @return status code
  * @retval M_TRIE_E_NULL      tr and/or key is NULL
  * @retval M_TRIE_E_LENGTH    len is zero
  * @retval M_TRIE_E_INVALID   key contains one or more invalid characters
  * @retval M_TRIE_E_NOT_FOUND key is not in the trie
  * @retval M_TRIE_OK          success
**/
int
m_trie_search(m_trie* tr, uint8_t* key, uint32_t len, void** val)
{
  node* nd;
  int ret;

  /* Locate the inner node of the trie. */
  ret = locate(tr, key, len, &nd);
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

/** Insert a value into the trie identified by a key.
  *
  * @param[in] tr  trie
  * @param[in] key key
  * @param[in] len key length
  * @param[in] val data associated with the key
  *
  * @return status code
  * @retval M_TRIE_E_NULL    tr and/or key is NULL
  * @retval M_TRIE_E_LENGTH  key length is zero
  * @retval M_TRIE_E_INVALID key contains one or more invalid characters
  * @retval M_TRIE_E_EXISTS  key already exists
  * @retval M_TRIE_OK        success
**/
int
m_trie_insert(m_trie* tr, uint8_t* key, uint32_t len, void* val)
{
  node* nd;
  int ret;
  uint32_t i;
  int16_t h;

  /* Validate the key. */
  ret = check(tr, key, len);
  if (ret != M_TRIE_OK)
    return ret;

  nd = tr->tr_root;

  /* Traverse the key. */
  for (i = 0; i < len; i++) {

    /* Clear the removal mark from the node. */
    if (nd->nd_type == NODE_TO_FREE)
      nd->nd_type = NODE_REGULAR;

    /* Create new subtree. */
    if (nd->nd_chld == NULL)
      node_chld(tr, &nd);

    /* Initialise the requested node. */
    h = tr->tr_hash(key[i]);
    if (nd->nd_chld[h] == NULL) {
      node_init(tr, &nd->nd_chld[h]);
      nd->nd_chld[h]->nd_key = key[i];
    }

    /* Advance to the selected/created node. */
    nd = nd->nd_chld[h];
  }

  /* Raise an error if the value can not be overwritten. */
  if (nd->nd_type == NODE_DATA && (tr->tr_flags & M_TRIE_OVERWRITE))
    return M_TRIE_E_EXISTS;

  nd->nd_type = NODE_DATA;
  nd->nd_data = val;

  /* Update the new maximal observed length. */
  if (len > tr->tr_maxl)
    tr->tr_maxl = len;

  return M_TRIE_OK;
}
