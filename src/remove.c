#include <stdlib.h>

#include "m_trie.h"
#include "common.h"
#include "node.h"

/**
  * Free all resources help by a particular subtree of the trie.
  *
  * @param[in] start subtree root node
  * @param[in] maxl  maximal key length
  * @param[in] ccnt  children count
**/
static void
free_dfs(struct _node* start, size_t maxl, uint8_t ccnt)
{
	struct _node** stack;
	struct _node* node;
	int top; 
	uint8_t i;

	top = -1;
	stack = malloc(sizeof(struct _node*) * maxl * ccnt);

	stack[++top] = start;
	while (top != 0) {
		node = stack[--top];

		for (i = 0; i < ccnt; i++)
			if (node->chld != NULL && node->chld[i] != NULL)
				stack[++top] = node->chld[i];

		node_free(&node);
	}

	free(stack);
}

/**
  * Free all children subtrees.
  * NOTE: this function is for internal use only.
  *
  * @param[in] trie trie
  * @param[in] node node
**/
static void
free_children(m_trie* trie, struct _node* node)
{
	uint8_t i;

	for (i = 0; i < trie->ccnt; i++) {
		if (node->chld[i] != NULL) {
			free_dfs(node->chld[i], trie->maxl, trie->ccnt);
			node->chld[i] = NULL;
		}
	}
}

/**
  * Remove a key from the trie.
  *
  * @param[in] trie trie
  * @param[in] key  key
  * @param[in] len  key length
  *
  * @return status code
  * @retval M_TRIE_E_NULL      trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH    key length is zero
  * @retval M_TRIE_E_INVALID   key contains invalid characters
  * @retval M_TRIE_E_NOT_FOUND key is not in trie
  * @retval M_TRIE_E_NO_VALUE  no value is associated with the key
  * @retval M_TRIE_OK          success
**/
int
m_trie_remove(m_trie* trie, char* key, size_t len)
{
	struct _node* node;
	int ret;

	ret = locate(trie, key, len, &node);
	if (ret != M_TRIE_OK)
		return ret;

	if (node->type == M_TRIE_NODE_TYPE_REGULAR)
		return M_TRIE_E_NO_VALUE;

	node->type = M_TRIE_NODE_TYPE_REGULAR;
	node->data = NULL;

	return M_TRIE_OK;
}

/**
  * Remove all keys that share the specified prefix.
  *
  * @param[in] trie trie
  * @param[in] key  key
  * @param[in] len  key length
  *
  * @return status code
  * @retval M_TRIE_E_NULL      trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH    key length is zero
  * @retval M_TRIE_E_INVALID   key contains invalid characters
  * @retval M_TRIE_E_NOT_FOUND key is not stored in the trie
  * @retval M_TRIE_OK          success
**/
int
m_trie_remove_prefix(m_trie *trie, char* key, size_t len)
{
	struct _node* node;
	int ret;

	ret = locate(trie, key, len, &node);
	if (ret != M_TRIE_OK)
		return ret;

	free_children(trie, node);

	return M_TRIE_OK;
}

/**
  * Remove all keys from the trie.
  * 
  * @param[in] trie trie
  *
  * @return status code
  * @retval M_TRIE_E_NULL trie is NULL
  * @retval M_TRIE_OK     success
**/
int
m_trie_remove_all(m_trie* trie)
{
	if (trie == NULL)
		return M_TRIE_E_NULL;

	free_children(trie, trie->root);
	trie->maxl = 0;

	return M_TRIE_OK;
}

