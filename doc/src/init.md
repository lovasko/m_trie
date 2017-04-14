m_trie_init(3M) -- initialise the trie
======================================

## LIBRARY
m_trie (-lmtrie)

## SYNOPSIS
`#include <m_trie.h>`

`int`
<m_trie_init>(`m_trie*` *tr*, `int16_t` (_*hash_)(`uint8_t`), `uint8_t` _flags_);

## DESCRIPTION
The <m_trie_init> function initialises the *tr*ie data structure. This
function does not perform the actual allocation of the *tr*ie variable itself,
which has to be done by the user.

The *hash* argument is a pointer to a hashing function. The <m_trie_init>
function does not need any other information about the hashing function, as it
tests it on every possible input and performs internal computations on the set
of results.

The *flags* argument specifies the behaviour of the data structure. As of now,
there are three supported flags:

 * M_TRIE_OVERWRITE:
   Inserting an identical key twice will result in the previously associated
   data to be overwritten. Such behaviour is prevented by default.

 * M_TRIE_CLEANUP:
   Ensure that the garbage-collection procedure is run every time when a node
   is removed. Note that this might have a significant performance impact.

 * M_TRIE_FREE:
   Call the <free(3)> function on all associated values with removed nodes.


## TIME COMPLEXITY
`O`(1).

## SPACE COMPLEXITY
`O`(1).

## RETURN VALUES
 * M_TRIE_OK:
   Success.

 * M_TRIE_E_NULL:
   *tr* and/or *hash* are NULL.

 * M_TRIE_E_INVALID:
   *hash* function is valid for zero bytes.

## AUTHOR
Daniel Lovasko <daniel.lovasko@gmail.com>

## SEE ALSO
m_trie_insert(3), m_trie_free(3), m_trie_hash(3)
