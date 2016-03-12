#include "m_trie.h"

int
m_trie_keys(m_trie* trie, m_list** out_keys)
{
	if (trie == NULL || out_keys == NULL)
		return M_TRIE_E_NULL;

	if (!(trie->aux_store & M_TRIE_AUX_STORE_KEYS))
		return M_TRIE_E_NOT_STORED;

	*out_keys = &trie->keys;
	return M_TRIE_OK;
}

int
m_trie_values(m_trie* trie, m_list** out_values)
{
	if (trie == NULL || out_values == NULL)
		return M_TRIE_E_NULL;

	if (!(trie->aux_store & M_TRIE_AUX_STORE_VALUES))
		return M_TRIE_E_NOT_STORED;

	*out_values = &trie->values;
	return M_TRIE_OK;
}

