m_trie_remove(3) -- remove a key from the trie 
==============================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int`   
<m_trie_remove>(`m_trie*` <trie>, `char*` <key>, `size_t` <len>)

## DESCRIPTION
The <m_trie_remove> function removes a specified <key> from the <trie>. This
function merely tags the internal tree node as free and does not perform the
actual deallocation of the memory due to performance reasons. To trigger the
resource deallocation process, use the <m_trie_trim> function.

## TIME COMPLEXITY
`O`(<k>), where <k> is the <len>gth of the <key>.

## RETURN VALUES
 * M_TRIE_OK:
   success

 * M_TRIE_E_NULL:
   <trie> and/or <key> are `NULL`

 * M_TRIE_E_INVALID:
   <key> contains invalid characters (as specified by the hashing function)

 * M_TRIE_E_LENGTH:
   <len> is zero

## SEE ALSO
m_trie_insert(3), m_trie_trim(3)
