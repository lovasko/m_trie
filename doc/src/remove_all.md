m_trie_remove_all(3) -- remove all keys from the trie 
=====================================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int`   
<m_trie_remove_all>(`m_trie*` <trie>)

## DESCRIPTION
The <m_trie_remove_all> function removes all keys from the <trie>. This
function merely tags the internal tree node as free and does not perform the
actual deallocation of the memory due to performance reasons. To trigger the
resource deallocation process, use the <m_trie_trim> function.

## TIME COMPLEXITY
`O`(<lh>), where <l> is the length of the longest key that was inserted in the
<trie> and <h> is the number of accepted bytes by the hash function.

## RETURN VALUES
 * M_TRIE_OK:
   success

 * M_TRIE_E_NULL:
   <trie> is `NULL`

## SEE ALSO
m_trie_remove(3), m_trie_trim(3)
