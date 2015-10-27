#include "m_trie.h"
#include "node.h"

static void
keys_memory_usage(struct m_trie* trie, uint64_t* out_usage)
{
	struct m_elem* runner;
	size_t size;

	m_list_first(&trie->keys, &runner);
	while (runner != NULL) {
		m_elem_data_size(runner, &size);
		*out_usage += (uint64_t)size;

		m_elem_next(runner, &runner);
	}
}

static void
values_memory_usage(struct m_trie* trie, uint64_t* out_usage)
{
	uint64_t length;

	m_list_length(&trie->values, &length);
	*out_usage += ((uint64_t)sizeof(void*)) * length;
}

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

	if (trie->aux_store & M_TRIE_AUX_STORE_KEYS)
		keys_memory_usage(trie, out_usage);

	if (trie->aux_store & M_TRIE_AUX_STORE_VALUES)
		values_memory_usage(trie, out_usage);

	return M_TRIE_OK;
}

