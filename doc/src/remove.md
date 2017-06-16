m_trie_remove(3) -- remove one or more keys from the trie
=========================================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int` <m_trie_remove>(`m_trie*` *tr*, `uint8_t*` <key>, `uint32_t` <len>, uint8_t pfix);
`int` <m_trie_remove_all>(`m_trie*` *tr*);

## DESCRIPTION
The <m_trie_remove> function removes a specified <key> from the <trie>. This
function merely tags the internal tree node as free and does not perform the
actual deallocation of the memory due to performance reasons. To trigger the
resource deallocation process, use the <m_trie_trim> function.

## TIME COMPLEXITY
`O`(<k>), where <k> is the length of the longest key in the *tr*ie.

## SPACE COMPLEXITY
`O`(1).

## TIME COMPLEXITY (PREFIX MODE & ALL)
`O`(<n>), where <n> is the overall number of nodes in the *tr*ie.

## SPACE COMPLEXITY (PREFIX MODE & ALL)
`O`(<k>), where <k> is the length of the longest key in the *tr*ie.

## RETURN VALUES
 * M_TRIE_OK:
   Success.

 * M_TRIE_E_NULL:
   <trie> and/or <key> are `NULL`.

 * M_TRIE_E_INVALID:
   <key> contains invalid characters.

 * M_TRIE_E_LENGTH:
   <len> is zero.

## SEE ALSO
m_trie_insert(3), m_trie_trim(3)
