#include "m_trie.h"

int
m_trie_keys(struct m_trie* trie, struct m_list** out_keys)
{
	if (trie == NULL || out_keys == NULL)
		return M_TRIE_E_NULL;

	*out_keys = &trie->keys;
	return M_TRIE_OK;
}

int
m_trie_values(struct m_trie* trie, struct m_list** out_values)
{
	if (trie == NULL || out_values == NULL)
		return M_TRIE_E_NULL;

	*out_values = &trie->values;
	return M_TRIE_OK;
}

