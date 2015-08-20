#include "m_trie.h"
#include "node.h"
#include "key.h"

static void
free_dfs(struct __m_node* start, uint8_t max_children_count)
{
	struct m_list stack;
	struct __m_node* node;
	struct m_elem* first;
	uint8_t i;

	m_list_init(&stack);
	m_list_prepend(&stack, M_LIST_COPY_SHALLOW, start, 0);
	while (m_list_is_empty(&stack) != M_LIST_TRUE) {
		m_list_first(&stack, &first);	
		m_elem_data(first, (void**)&node);
		m_list_remove_first(&stack);

		for (i = 0; i < max_children_count; i++)
			if (node->children[i] != NULL)
				m_list_prepend(&stack, M_LIST_COPY_SHALLOW, node->children[0], 0);

		node_free(&node);
	}
}

static void
free_path(struct m_list* path, uint8_t max_children_count)
{
	int has_children;
	struct __m_node* node;
	struct m_elem* first;
	uint8_t i;

	while (m_list_is_empty(path) != M_LIST_TRUE) {
		m_list_first(path, &first);
		m_elem_data(first, (void**)&node);
		m_list_remove_first(path);

		has_children = 0;
		for (i = 0; i < max_children_count; i++) {
			if (node->children[i] != NULL) {
				has_children = 1;
				break;
			}
		}

		if (has_children)
			break;
		else
			node_free(&node);
	}
}

int
m_trie_remove(struct m_trie* trie, char* key, uint32_t key_length, int mode)
{
	struct m_list path;
	struct __m_node* node;
	uint32_t i;

	if (trie == NULL || key == NULL)
		return M_TRIE_E_NULL;

	if (!key_valid(trie, key, key_length))
		return M_TRIE_E_KEY_INVALID;

	node = trie->root;

	if (!(mode & M_TRIE_REMOVE_NO_CLEANUP)) {
		m_list_init(&path);	
		m_list_append(&path, M_LIST_COPY_SHALLOW, node, 0);
	}

	for (i = 0; i < key_length; i++) {
		if ((node = node->children[trie->hash(key[i])]) == NULL)
			return M_TRIE_E_NOT_FOUND;
		else {
			if (!(mode & M_TRIE_REMOVE_NO_CLEANUP))
				m_list_append(&path, M_LIST_COPY_SHALLOW, node, 0);
		}
	}
	m_list_remove_last(&path);
	
	if (node->type == M_TRIE_NODE_TYPE_REGULAR 
	 && !(mode & M_TRIE_REMOVE_PREFIX)) {
		if (!(mode & M_TRIE_REMOVE_NO_CLEANUP))
			m_list_clear(&path);
		return M_TRIE_E_PREFIX;
	}
	
	free_dfs(node, trie->children_count);

	if (!(mode & M_TRIE_REMOVE_NO_CLEANUP))
		free_path(&path, trie->children_count);

	return M_TRIE_OK;
}

