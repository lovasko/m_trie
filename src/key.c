#include "key.h"

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
int
key_valid(m_trie* trie, char* key, size_t len)
{
	size_t i;

	for (i = 0; i < len; i++)
		if (trie->hash(key[i]) < 0)
			return 0;

	return 1;
}

