#include <limits.h>

#include "m_trie.h"
#include "node.h"


/** Initialise the trie.
  *
  * @param[in] trie  trie
  * @param[in] hash  hash function
  * @param[in] flags behaviour flags
  *
  * @return status code
  * @retval M_TRIE_E_NULL    trie and/or hash is NULL
  * @retval M_TRIE_E_INVALID hash accepts no inputs
  * @retval M_TRIE_OK        success
**/
int
m_trie_init(m_trie* trie, short (*hash)(char), int flags)
{
  char i;

  if (trie == NULL || hash == NULL)
    return M_TRIE_E_NULL;

  trie->tr_flags = flags;
  trie->tr_hash = hash;
  trie->tr_ncnt = 0;

  /* Compute the children count, by counting the number of positive
   * answers from the hash function. */
  trie->tr_ccnt = 0;
  for (i = CHAR_MIN; i < CHAR_MAX; i++)
    if (hash(i) >= 0)
      trie->tr_ccnt++;

  /* Refuse hash functions that accept no inputs. */
  if (trie->tr_ccnt == 0)
    return M_TRIE_E_INVALID;

  /* Initialise the root node. */
  node_init(trie, (node**)&trie->tr_root);

  return M_TRIE_OK;
}

/** Free all memory resources held by the trie. Subsequent initialisation
  * and use of the trie is allowed.
  *
  * @param[in] trie trie
  *
  * @return status code
  * @retval M_TRIE_E_NULL trie is NULL
  * @retval M_TRIE_OK     success
**/
int
m_trie_free(m_trie* trie)
{
  if (trie == NULL)
    return M_TRIE_E_NULL;

  m_trie_remove_prefix(trie, NULL, 0);
  m_trie_trim(trie);
  node_free(trie, (node*)trie->tr_root);

  return M_TRIE_OK;
}
