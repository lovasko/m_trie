#include <limits.h>

#include "m_trie.h"
#include "node.h"

/**
  * Initialise the trie.
  *
  * @param[in] trie trie
  * @param[in] hash hash function
  * @param[in] owrt overwrite mode
  *
  * @return status code
  * @retval M_TRIE_E_NULL   tr and/or hash is NULL
  * @retval M_TRIE_EUNKNOWN no such overwrite mode
  * @retval M_TRIE_OK       success
**/
int
m_trie_init(m_trie* trie, int16_t (*hash)(char), uint8_t owrt)
{
	char i;

	if (trie == NULL || hash == NULL)
		return M_TRIE_E_NULL;

	if (owrt != M_TRIE_OVERWRITE_ALLOW
	 && owrt != M_TRIE_OVERWRITE_PREVENT)
		return M_TRIE_E_UNKNOWN;

	trie->owrt = owrt;
	trie->hash = hash;
	trie->maxl = 0;
	trie->ccnt = 0;
	for (i = CHAR_MIN; i < CHAR_MAX; i++)
		if (hash(i) >= 0)
			trie->ccnt++;

	node_init((struct _node**)&trie->root);

	return M_TRIE_OK;
}

/**
  * Free all memory resources held by the trie.
  *
  * @param[in] trie trie
  * 
  * @return status code
  * @retval M_TRIE_E_NULL tr is NULL
  * @retval M_TRIE_OK     success
**/
int
m_trie_free(m_trie* trie)
{
	if (trie == NULL)
		return M_TRIE_E_NULL;

	m_trie_remove_all(trie);
	node_free(trie->root);

	return M_TRIE_OK;
}

