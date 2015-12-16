#include <limits.h>

#include "m_trie.h"

int16_t
m_trie_hash_generic_byte(char key)
{
	int16_t result;

	result = (int16_t)key;
	result -= (int16_t)CHAR_MIN;

	return result;
}

int16_t
m_trie_hash_alphabet(char key)
{
	if (key >= 'A' && key <= 'Z')
		return key - 'A';

	if (key >= 'a' && key <= 'z')
		return 26 + key - 'a';

	return -1;
}

