#include "m_trie.h"
#include "common.h"
#include "node.h"

/**
  * Search for a key in the trie.
  *
  * @param[in]  trie  trie
  * @param[in]  key   key
  * @param[in]  len   key length
  * @param[out] val   data associated with they key
  *
  * @returns status code
  * @retval M_TRIE_E_NULL      trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH    length is zero
  * @retval M_TRIE_E_INVALID   key contains invalid characters
  * @retval M_TRIE_E_NOT_FOUND key is not in the trie
  * @retval M_TRIE_OK          success
**/
int
m_trie_search(m_trie* trie, char* key, size_t len, void** val)
{
	struct _node* node;
	int ret;

	ret = locate(trie, key, len, &node);
	if (ret != M_TRIE_OK)
		return ret;

	if (node->type != M_TRIE_NODE_TYPE_DATA)
		return M_TRIE_E_NOT_FOUND;

	if (val != NULL)
		*val = node->data;

	return M_TRIE_OK;
}

/**
  * Insert a value into the trie.
  *
  * @param[in] trie trie
  * @param[in] key  key
  * @param[in] len  key length
  * @param[in] val  value
  *
  * @return status code
  * @retval M_TRIE_E_NULL    trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH  key length is zero
  * @retval M_TRIE_E_INVALID key contains an invalid character
  * @retval M_TRIE_E_EXISTS  key exists (only when overwriting is not allowed)
  * @retval M_TRIE_OK        success
**/
int
m_trie_insert(m_trie* trie, char* key, size_t len, void* val)
{
	size_t i;
	int16_t h;
	int ret;
	struct _node* node;

	ret = check(trie, key, len);
	if (ret != M_TRIE_OK)
		return ret;

	node = trie->root;

	for (i = 0; i < len; i++) {
		h = trie->hash(key[i]);

		if (node->chld == NULL)
			node_init_children(&node, trie->ccnt);

		if (node->chld[h] == NULL) {
			node_init(&node->chld[h]);
			node->chld[h]->key = key[i];
		}

		node = node->chld[h];
	}

	if (node->type == M_TRIE_NODE_TYPE_DATA
	 && trie->owrt == M_TRIE_OVERWRITE_PREVENT)
		return M_TRIE_E_EXISTS;

	node->type = M_TRIE_NODE_TYPE_DATA;
	node->data = val;

	if (trie->maxl < len)
		trie->maxl = len;

	return M_TRIE_OK;
}

