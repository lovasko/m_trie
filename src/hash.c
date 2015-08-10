#include <limits.h>

#include "m_trie.h"

int16_t
m_trie_generic_byte_hash(char key)
{
	int16_t result;

	result = (int16_t)key;
	result -= (int16_t)CHAR_MIN;

	return result;
}

