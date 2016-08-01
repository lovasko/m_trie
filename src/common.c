#include "m_trie.h"
#include "common.h"

/**
  * Check whether a key is valid.
  * NOTE: this function is for internal use only.
  *
  * @param trie trie
  * @param key  key
  * @param len  key length
  *
  * @return key validity
  * @retval 0 key is invalid
  * @retval 1 key is valid
**/
static int
key_valid(m_trie* trie, char* key, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		if (trie->hash(key[i]) < 0)
			return 0;

	return 1;
}

/**
  * Check the sanity of the user input.
  * NOTE: this function is for internal use only.
  *
  * @param trie trie
  * @param key  key
  * @param len  key length
  *
  * @return status code
  * @retval M_TRIE_E_NULL    trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH  key length is zero
  * @retval M_TRIE_E_INVALID key contains invalid characters
  * @retval M_TRIE_OK        success
**/
int
check(m_trie* trie, char* key, size_t len)
{
	if (trie == NULL || key == NULL)
		return M_TRIE_E_NULL;

	if (len == 0)
		return M_TRIE_E_LENGTH;

	if (!key_valid(trie, key, len))
		return M_TRIE_E_INVALID;

	return M_TRIE_OK;
}

/**
  * Locate a node within the trie based on a key.
  * NOTE: this function is for internal use only.
  *
  * @param trie trie
  * @param key  key
  * @param len  key length
  * @param out  found node
  *
  * @retval M_TRIE_E_NULL      trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH    key length is zero
  * @retval M_TRIE_E_INVALID   key contains invalid characters
  * @retval M_TRIE_E_NOT_FOUND key is not stored in the trie
  * @retval M_TRIE_OK          success
**/
int
locate(m_trie* trie, char* key, size_t len, struct _node** out)
{
	size_t i;
	struct _node* node;
	int ret;

	ret = check(trie, key, len);
	if (ret != M_TRIE_OK)
		return ret;

	node = trie->root;

	for (i = 0; i < len; i++)
		if (node->chld == NULL || (node = node->chld[trie->hash(key[i])]) == NULL)
			return M_TRIE_E_NOT_FOUND;

	*out = node;
	return M_TRIE_OK;
}

