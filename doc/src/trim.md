m_trie_trim(3) -- deallocate unused resources
=============================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int`   
<m_trie_trim>(`m_trie*` <trie>)

## DESCRIPTION
The <m_trie_trim> function deallocates all resources that are no longer needed
by the <trie>. 

## TIME COMPLEXITY
`O`(<lh>), where <l> is the length of the longest key that was inserted in the
<trie> and <h> is the number of accepted bytes by the hash function.

## SPACE COMPLEXITY
TODO.

## RETURN VALUES
 * M_TRIE_OK:
   success

 * M_TRIE_E_NULL:
   <trie> is `NULL`

## SEE ALSO
m_trie_remove(3), m_trie_free(3)
