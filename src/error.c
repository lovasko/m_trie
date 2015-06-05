#include <stdlib.h>

char*
m_trie_error_string(int error)
{
	char* messages[] = {
		"OK",
		"Argument was NULL",
		"Not found",
		"Invalid key",
		"Entry exists",
		"Invalid copy method",
		"Invalid overwrite policy"
	};

	if (error < 0 || error > 6)
		return NULL;
	else
		return messages[error];
}
