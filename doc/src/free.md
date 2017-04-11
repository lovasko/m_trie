m_trie_free(3) -- release all resources held by the trie
========================================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int` <m_trie_free>(`m_trie*` *tr*);

## DESCRIPTION
The <m_trie_free> function releases all memory resources held by the *tr*ie.
It is guaranteed that the instance can be used afterwards, once initialised
again with a call to <m_trie_init>.

## TIME COMPLEXITY
`O`(<n>), where <n> is the overall number of nodes in the *tr*ie.

## SPACE COMPLEXITY
`O`(<k>), where <k> is the length of the longest key in the *tr*ie.

## RETURN VALUES
 * M_TRIE_OK:
   Success.

 * M_TRIE_E_NULL:
   *tr*ie is NULL.

## SEE ALSO
m_trie_init(3), m_trie_remove(3)
