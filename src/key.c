#include "key.h"

int
key_valid(struct m_trie* trie, char* key, uint32_t key_length)
{
	uint32_t i;

	for (i = 0; i < key_length; i++)
		if (trie->hash(key[i]) < 0)
			return 0;
			
	return 1;
}

