#ifdef M_TRIE_DEBUG

#include "m_trie.h"
#include "node.h"

int
m_trie_children_stats(struct m_trie* trie, uint64_t** out_stats)
{
	struct m_list queue;
	struct m_elem* first;
	struct __m_node* node;
	uint8_t i;
	uint8_t count;

	*out_stats = malloc(sizeof(uint64_t) * trie->children_count);
	for (i = 0; i < trie->children_count; i++)
		(*out_stats)[i] = 0;

	if (trie == NULL || out_stats == NULL)
		return M_TRIE_E_NULL;

	m_list_init(&queue);
	m_list_append(&queue, M_LIST_COPY_SHALLOW, trie->root, 1);

	while (m_list_is_empty(&queue) != M_LIST_TRUE) {
		m_list_first(&queue, &first);
		m_elem_data(first, (void**)&node);
		m_list_remove_first(&queue);

		count = 0;

		if (node->children != NULL) {
			for (i = 0; i < trie->children_count; i++) {
				if (node->children[i] == NULL)
					count++;
				else
					m_list_append(&queue, M_LIST_COPY_SHALLOW, node->children[i], 1);
			}
		}

		(*out_stats)[count]++;
	}

	return M_TRIE_OK;
}

#else

typedef int no_debug_dummy;

#endif

