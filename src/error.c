#include "m_trie.h"

const char*
m_trie_error_string(int error)
{
	static const char* messages[] = {
		"OK",
		"Argument was NULL",
		"Not found",
		"Invalid key",
		"Entry exists",
		"Invalid copy method",
		"Invalid overwrite policy"
	};

	if (error < 0 || error > M_TRIE_E_MAX)
		return NULL;
	else
		return messages[error];
}

