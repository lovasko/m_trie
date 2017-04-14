m_trie_search(3) -- search for a key in the trie
================================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int` <m_trie_search>(`m_trie*` *tr*, `uint8_t*` <key>, `uint32_t` <len>, `void**` <val>);

## DESCRIPTION
The <m_trie_search> function performs a lookup for the specified <key> in the
*tr*ie and returns the associated *val*ue.

## TIME COMPLEXITY
`O`(<k>), where <k> is the length of the longest key in the *tr*ie.

## SPACE COMPLEXITY
`O`(<1>).

## RETURN VALUES
 * M_TRIE_OK:
   Success.

 * M_TRIE_E_NULL:
   *tr*ie and/or <key> are `NULL`.

 * M_TRIE_E_INVALID:
   <key> contains one or more invalid characters.

 * M_TRIE_E_NOT_FOUND:
   <key> was not found in the *tr*ie.

 * M_TRIE_E_LENGTH:
   <len> is zero.

## SEE ALSO
m_trie_insert(3), m_trie_hash(3)
