#include <string.h>

#include "m_trie.h"
#include "node.h"
#include "key.h"

int
m_trie_get(struct m_trie* trie,
           char* key,
           uint32_t key_length,
           void** out_data)
{
	uint32_t i;
	struct __m_node* node;

	if (trie == NULL || key == NULL)
		return M_TRIE_E_NULL;

	if (!key_valid(trie, key, key_length))
		return M_TRIE_E_KEY_INVALID;

	node = trie->root;

	for (i = 0; i < key_length; i++) {
		if (node->children == NULL ||
		    (node = node->children[trie->hash(key[i])]) == NULL)
			return M_TRIE_E_NOT_FOUND;
	}

	if (node->type != M_TRIE_NODE_TYPE_DATA)
		return M_TRIE_E_NOT_FOUND;

	if (out_data != NULL)
		*out_data = node->data;

	return M_TRIE_OK;
}

int
m_trie_set(struct m_trie* trie,
           char* key,
           uint32_t key_length,
           uint8_t copy,
           uint8_t overwrite,
           void* data,
           size_t data_size)
{
	uint32_t i;
	int16_t h;
	struct __m_node* node;

	if (trie == NULL || key == NULL)
		return M_TRIE_E_NULL;

	if (!key_valid(trie, key, key_length))
		return M_TRIE_E_KEY_INVALID;

	node = trie->root;

	for (i = 0; i < key_length; i++) {
		h = trie->hash(key[i]);

		if (node->children == NULL)
			node_init_children(&node, trie->children_count);

		if (node->children[h] == NULL) {
			node_init(&node->children[h]);
			node->children[h]->key = key[i];
		}

		node = node->children[h];
	}

	if (node->type == M_TRIE_NODE_TYPE_DATA 
	 && overwrite == M_TRIE_OVERWRITE_PREVENT) {
		return M_TRIE_E_EXISTS;
	}

	node->type = M_TRIE_NODE_TYPE_DATA;

	if (copy == M_TRIE_COPY_DEEP) {
		if (data == NULL || data_size == 0) {
			node->data = NULL;
			node->copy = M_TRIE_NODE_COPY_NULL;
		} else {
			node->data = malloc(data_size);
			memcpy(node->data, data, data_size);
			node->copy = M_TRIE_NODE_COPY_DEEP;
		}
	} else if (copy == M_TRIE_COPY_SHALLOW) {
		node->data = data;
		node->copy = M_TRIE_NODE_COPY_SHALLOW;
	} else {
		return M_TRIE_E_COPY_INVALID;	
	}

	if (trie->aux_store & M_TRIE_AUX_STORE_KEYS)
		m_list_append(&trie->keys, M_LIST_COPY_DEEP, key, key_length);

	if (trie->aux_store & M_TRIE_AUX_STORE_VALUES)
		m_list_append(&trie->values, M_LIST_COPY_SHALLOW, node->data, 0);

	return M_TRIE_OK;
}

