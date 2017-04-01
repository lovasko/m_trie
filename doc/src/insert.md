m_trie_insert(3) -- insert a key/value pair into the trie 
=========================================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int`   
<m_trie_insert>(`m_trie*` <trie>, `char*` <key>, `size_t` <len>, `void*` <val>)

## DESCRIPTION
The <m_trie_insert> function inserts a specified <key>/<val>ue pair into the 
<trie>. It is allowed for the <key> to contain NUL bytes and for the <val> to
be `NULL`.

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
m_trie_remove(3), m_trie_search(3)
