m_trie_insert(3) -- insert a key/value pair into the trie 
=========================================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int` <m_trie_insert>(`m_trie*` *tr*, `uint8_t*` <key>, `uint32_t` <len>, `void*` <val>)

## DESCRIPTION
The <m_trie_insert> function inserts a specified <key>/<val>ue pair into the 
*tr*ie. It is allowed for the <key> to contain NUL bytes and for the <val> to
be `NULL`.

## TIME COMPLEXITY
`O`(<k>), where <k> is the length of the longest key in the *tr*ie.

## SPACE COMPLEXITY
`O`(<k>), where <k> is the length of the longest key in the *tr*ie.

## RETURN VALUES
 * M_TRIE_OK:
   Success.

 * M_TRIE_E_NULL:
   *tr*ie and/or <key> are `NULL`.

 * M_TRIE_E_INVALID:
   <key> contains invalid characters.

 * M_TRIE_E_LENGTH:
   <len> is zero.

## SEE ALSO
m_trie_remove(3), m_trie_search(3)
