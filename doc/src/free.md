m_trie_free(3) -- release all resources held by the trie
========================================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int`
<m_trie_free>(`m_trie*` <trie>)

## DESCRIPTION
The <m_trie_free> function releases all memory resources held by the <trie>.
It is guaranteed that the instance can be used afterwards, once initialised
again with a call to <m_trie_init>.

## TIME COMPLEXITY
`O`(<n><k>), where <n> is the number of inserted elements and <k> is the
mapping domain of the hashing function.

## SPACE COMPLEXITY
TODO.

## RETURN VALUES
 * M_TRIE_OK:
   success

 * M_TRIE_E_NULL:
   <trie> is NULL

## SEE ALSO
m_trie_init(3), m_trie_remove(3)
