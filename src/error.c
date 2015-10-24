#include "m_trie.h"

int
m_trie_error_string(int code, char** out_error_string)
{
	static const char* strings[] = {
		"OK",
		"Argument was NULL",
		"Not found",
		"Invalid key",
		"Entry exists",
		"Invalid copy method",
		"Invalid overwrite policy",
		"Invalid return code"
	};

	if (out_error_string == NULL)
		return M_TRIE_E_NULL;

	if (code < 0 || code > M_TRIE_E_MAX)
		return M_TRIE_E_INVALID_CODE;

	*out_error_string = (char*)strings[code];
	return M_TRIE_OK;
}

