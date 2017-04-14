m_trie_trim(3) -- deallocate unused resources
=============================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int` <m_trie_trim>(`m_trie*` *tr*);

## DESCRIPTION
The <m_trie_trim> function deallocates all resources that are no longer needed
by the *tr*ie. Such situation can arise after one or more calls to one of the
<m_trie_remove*> functions.

## TIME COMPLEXITY
`O`(<n>), where <n> is the overall number of allocated *tr*ie nodes.

## SPACE COMPLEXITY
`O`(<k>), where <k> is the length of the longest key in the *tr*ie.

## RETURN VALUES
 * M_TRIE_OK:
   Success.

 * M_TRIE_E_NULL:
   *tr* is `NULL`.

## SEE ALSO
m_trie_remove(3), m_trie_free(3)
