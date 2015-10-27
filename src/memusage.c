#include "m_trie.h"
#include "node.h"

int
m_trie_memory_usage(struct m_trie* trie, uint64_t* out_usage)
{
	struct m_list queue;
	struct m_elem* first;
	struct __m_node* node;
	uint8_t i;

	if (trie == NULL || out_usage == NULL)
		return M_TRIE_E_NULL;

	*out_usage = 0;

	m_list_init(&queue);
	m_list_append(&queue, M_LIST_COPY_SHALLOW, trie->root, 1);

	while (m_list_is_empty(&queue) != M_LIST_TRUE) {
		m_list_first(&queue, &first);
		m_elem_data(first, (void**)&node);
		m_list_remove_first(&queue);

		*out_usage += sizeof(void*) * trie->children_count;
		*out_usage += sizeof(struct __m_node);

		for (i = 0; i < trie->children_count; i++)
			if (node->children[i] != NULL)
				m_list_append(&queue, M_LIST_COPY_SHALLOW, node->children[i], 1);
	}

	return M_TRIE_OK;
}

