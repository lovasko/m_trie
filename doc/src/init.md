m_trie_init(3) -- initialise the trie 
=====================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int`
<m_trie_init>(`m_trie*` <trie>, `short` (<*hash>)(`char`), `int` <flags>);

## DESCRIPTION
The <m_trie_init> function initialises the <trie> data structure. This
function does not perform the actual allocation of the structure, which has
to be done by the user. 

The <hash> argument is a pointer to a hashing function. The <m_trie_init>
function does not need any other information about the hashing function, as it
tests it on every possible input and performs internal computations on the set
of results.

The <flags> argument specifies the behaviour of the data structure. As of now,
there are three supported flags:
 * M_TRIE_OVERWRITE:

 * M_TRIE_CLEANUP:

 * M_TRIE_FREE:


## TIME COMPLEXITY
`O`(<1>).

## SPACE COMPLEXITY
`O`(<1>).

## RETURN VALUES
 * M_TRIE_OK:
   success

 * M_TRIE_E_NULL:
   <trie> and/or <hash> were NULL

 * M_TRIE_E_INVALID:
   <hash> function is valid for zero bytes

## SEE ALSO
m_trie_insert(3), m_trie_free(3), m_trie_hash(3)
