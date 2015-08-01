#include <string.h>

#include "m_trie.h"
#include "node.h"

static int
key_valid(struct m_trie* trie, char* key, uint32_t key_length)
{
	uint32_t i;

	for (i = 0; i < key_length; i++)
		if (trie->hash(key[i]) < 0)
			return 0;
			
	return 1;
}

int
m_trie_get(struct m_trie* trie,
           char* key,
					 uint32_t key_length,
					 void** data)
{
	uint32_t i;
	struct __m_node* node;

	if (trie == NULL || key == NULL)
		return M_TRIE_E_NULL;

	if (!key_valid(trie, key, key_length))
		return M_TRIE_E_KEY_INVALID;

	node = trie->root;

	for (i = 0; i < key_length; i++)
		if ((node = node->children[trie->hash(key[i])]) == NULL)
			return M_TRIE_E_NOT_FOUND;

	if (node->type == M_TRIE_NODE_TYPE_DATA) {
		if (data != NULL)
			*data = node->data;
		return M_TRIE_OK;
	}
	else {
		return M_TRIE_E_NOT_FOUND;
	}
}

int
m_trie_set(struct m_trie* trie,
           char* key,
           uint32_t key_length,
           uint8_t copy,
           uint8_t overwrite,
           void* data,
           size_t size)
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

		if (node->children[h] == NULL) {
			node_init(&node->children[h], trie->children_count);
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
		if (data == NULL || size == 0) {
			node->data = NULL;
		} else {
			node->data = malloc(size);
			memcpy(node->data, data, size);
		}
	} else if (copy == M_TRIE_COPY_SHALLOW) {
		node->data = data;
	} else {
		return M_TRIE_E_COPY_INVALID;	
	}

	m_list_append(&trie->keys, M_LIST_COPY_DEEP, key, key_length);
	m_list_append(&trie->values, M_LIST_COPY_SHALLOW, node->data, 0);

	return M_TRIE_OK;
}

