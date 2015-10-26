#include <limits.h>

#include "m_trie.h"
#include "node.h"

int
m_trie_init(struct m_trie* trie, int16_t (*hash)(char))
{
	char i;

	if (trie == NULL)
		return M_TRIE_E_NULL;

	trie->hash = hash;
	trie->children_count = 0;
	for (i = CHAR_MIN; i < CHAR_MAX; i++)
		if (hash(i) >= 0)
			trie->children_count++;

	node_init((struct __m_node**)&trie->root, trie->children_count);

	m_list_init(&trie->keys);
	m_list_init(&trie->values);

	return M_TRIE_OK;
}

