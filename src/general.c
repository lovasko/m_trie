#include <string.h>

#include "m_trie.h"
#include "node.h"


/** Initialise the trie.
  *
  * @param[in] tr    trie
  * @param[in] hash  hash function
  * @param[in] flags behaviour flags
  *
  * @return status code
  * @retval M_TRIE_E_NULL    tr and/or hash is NULL
  * @retval M_TRIE_E_INVALID hash accepts no inputs
  * @retval M_TRIE_OK        success
**/
int
m_trie_init(m_trie* tr, int16_t (*hash)(uint8_t), uint8_t flags)
{
  uint8_t i;

  if (tr == NULL || hash == NULL)
    return M_TRIE_E_NULL;

  tr->tr_flags = flags;
  tr->tr_hash = hash;
  tr->tr_ncnt = 0;
  tr->tr_maxl = 0;

  /* Compute the children count, by counting the number of positive
   * answers from the hash function. */
  tr->tr_ccnt = 0;
  for (i = 0; i < 255; i++)
    if (hash(i) >= 0)
      tr->tr_ccnt++;

  /* Refuse hash functions that accept no inputs. */
  if (tr->tr_ccnt == 0)
    return M_TRIE_E_INVALID;

  /* Initialise the root node. */
  node_init(tr, (node**)&tr->tr_root);

  return M_TRIE_OK;
}

/** Free all memory resources held by the trie. Subsequent initialisation
  * and use of the trie is allowed.
  *
  * @param[in] tr trie
  *
  * @return status code
  * @retval M_TRIE_E_NULL tr is NULL
  * @retval M_TRIE_OK     success
**/
int
m_trie_free(m_trie* tr)
{
  if (tr == NULL)
    return M_TRIE_E_NULL;

  m_trie_remove_all(tr);
  m_trie_trim(tr);

  node_free(tr, (node*)tr->tr_root);
  memset(tr, 0, sizeof(m_trie));

  return M_TRIE_OK;
}
