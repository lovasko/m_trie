# m_trie

## Introduction
The `m_trie` library is a general-purpose implementation of the prefix
tree data structure for the C89 language. The data structure stores
key/value pairs, where *key* is an array of bytes and *value* is an
arbitrary pointer to the associated data.

## Example
The following example inserts all command-line arguments into the
trie and lets the user search for their presence:
```c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <m_trie.h>

int
main(int argc, char* argv[])
{
  m_trie tr;
  char inp[256];
  int i;
  int ret;

  m_trie_init(&tr, m_trie_hash_alphabet, 0);
  for (i = 1; i < argc; i++)
    m_trie_insert(&tr, (uint8_t*)argv[i], (uint32_t)strlen(argv[i]), NULL);

  while (1) {
    scanf("%s", inp);
    if (strcmp(inp, "!") == 0)
      break;

    ret = m_trie_search(&tr, (uint8_t*)inp, (uint32_t)strlen(inp), NULL);
    printf("%s\n", ret == M_TRIE_OK ? "yes" : "no");
  }

  return EXIT_SUCCESS;
}
```

Compile with:
`clang -Wall -Wextra -Weverything -ansi -pedantic example.c -lmtrie`

Please note that this example lacks error-checking for the sake of
brevity. All production code _should_ check for return values of all
`m_trie` functions.

More examples can be found in the `examples/` folder.

## API
### General
Before calling any other function, the `m_trie` object needs to be
initialised via the `m_trie_init` function. This function does not
allocate the `m_trie` object itself, which is left to the user of the
library.

The initialisation function expects three arguments: a pointer to a
`m_trie` instance, pointer to a hash function (see below) and a flags
field that is an ORed combination of the following constants:

#### M_TRIE_OVERWRITE
Inserting an identical key twice will result in the previously associated
data to be overwritten. Such behaviour is prevented by default.

#### M_TRIE_CLEANUP
Trigger the garbage-collecting procedure after each removal request - no
that this can have a significant impact on the performance of the data
structure.

#### M_TRIE_FREE
Call the `free(3)` function on all value data pointers once the associated
key's removal is requested.

To free _all_ resources held by the data structure, call the `m_trie_free`
function.

Prototypes:
```c
int m_trie_init(m_trie* tr, int16_t (*hash)(uint8_t), uint8_t flags);
int m_trie_free(m_trie* tr);
```

### Access
In order to insert a new key/value pair into the prefix tree, the
`m_trie_insert` function can be used.  Once key/value pairs are inserted
into the data structure, it is possible to query the `m_trie` for presence
of certain key with the `m_trie_search` function. The stored value is
returned via the last argument of the function, while the return value of
the function is used to report potential errors.

Prototypes:
```c
int m_trie_insert(m_trie* tr, uint8_t* key, uint32_t len, void* val);
int m_trie_search(m_trie* tr, uint8_t* key, uint32_t len, void** val);
```

### Removing
The library offers two functions to remove keys (an their associated
values): `m_trie_remove`, a direct counterpart to the `m_trie_insert`
function. It accepts a key and it's length and marks the corresponding
data node for future removal. It is important to note that the
`m_trie_remove` function *does not* perform deallocation of memory and
simply marks node as if it did not contain any data. This decision was
taken due to performance reasons, where cascading freeing of memory could
pose significant memory delays and therefore uncontrollable jitter in
certain scenarios.

The last argument of the `m_trie_remove` function is it's mode: either `0`
for normal or `1` for prefix. If the prefix mode is selected, the function
removes all keys that start with the specified key. The key itself might
not indicate a previously inserted key, e.g. it is possible to call the
`m_trie_remove` function in the prefix mode with key `"ca"` and it would
delete keys such as `"california"` and `"carpool"`, even though `"ca"`
itself was not in the trie.

The second removal function, `m_trie_remove_all`, simply marks all already
inserted keys to be non-existent, so that an immediate call to the
`m_trie_search` function with any argument would not succeed. It is still
possible to use the `m_trie` instance afterwards, without needing to call
`m_trie_init`. All internal structures remain allocated, which can serve
as a performance feature in certain scenarios.

Prototypes:
```c
int m_trie_remove(m_trie* tr, uint8_t* key, uint32_t len, uint8_t pfix);
int m_trie_remove_all(m_trie* tr);
```

## Garbage-collection
As mentioned above, none of the removal functions actually deallocate
resources, in order to have a more predictable run-time. The
garbage-collection can be performed by the `m_trie_trim` function that
traverses the data structure and frees the unused memory blocks. The
performance aspect of this procedure depends on how often this function is
called and may be significant.

Prototype:
```c
int m_trie_trim(m_trie* tr);
```

### Hash functions
The `m_trie` data structure needs a user-supplied hash function to
navigate the levels of the tree. Each `m_trie` hash function takes a
`char` value as input and produces a `short` value. In case that the byte
on the input is not valid, a correct `m_trie` hash function must return
`-1`. The function must uniquely map all valid byte inputs onto the
interval `0 .. (n-1)`, where `n` is the number of valid input bytes.  Each
`m_trie` hash function therefore must be a *minimal perfect* hash
function.

#### Predefined hash functions
The library identifies a list hash functions that are ubiquitous
and general enough to be included in the library, such as the identity
function `m_trie_hash_identity` or a hash function that supports only the
lower-case letters of English alphabet `m_trie_hash_lower_alphabet`.

Prototypes:
 ```c
int16_t m_trie_hash_identity(uint8_t key);
int16_t m_trie_hash_alphabet(uint8_t key);
int16_t m_trie_hash_digits(uint8_t key);
int16_t m_trie_hash_base64(uint8_t key);
int16_t m_trie_hash_alphanumeric(uint8_t key);
int16_t m_trie_hash_lower_alphabet(uint8_t key);
int16_t m_trie_hash_upper_alphabet(uint8_t key);
 ```

#### User-supplied hash functions
Users of the library are welcomed to create custom hash functions that
obey the rules described above. An example of a hash function that accepts
only characters `'0'` and `'1'`:

```c
int16_t
hash_01(uint8_t c)
{
  if (c == 48) return 0;
  if (c == 49) return 1;

  return -1;
}
```

## Time & space complexity
The table below makes an assumption that the hashing function operates in
both constant time and constant space.

| Function              | Time   | Space  |
|-----------------------|--------|--------|
|`m_trie_init`          | `O(1)` | `O(1)` |
|`m_trie_free`          | `O(n)` | `O(k)` |
|`m_trie_insert`        | `O(k)` | `O(k)` |
|`m_trie_search`        | `O(k)` | `O(1)` |
|`m_trie_remove`        | `O(k)` | `O(1)` |
|`m_trie_remove` (pfix) | `O(n)` | `O(k)` |
|`m_trie_remove_all`    | `O(n)` | `O(k)` |
|`m_trie_trim`          | `O(n)` | `O(k)` |
|`m_trie_hash_*`        | `O(1)` | `O(1)` |

Where:
* `k` is the length of the longest key
* `n` is the overall number of allocated trie nodes

## Documentation
Each function that is part of the public API of the library has its own
UNIX manual page. All pages belong to the section 3 of the manual
catalogue and are automatically installed with the library.

## Testing
The implementation is verified by a set of tests that each performs a list
of operations - insertion, removal and search of keys - combined in ways
that covers aim to cover all edge cases. The testing framework consists of
two files: `test.c` that implements the data structure operations and
`test.sh` that serves as orchestration and verification of test results.
The process can be invoked by triggering the `test` target of the
library's `Makefile`.

## Supported platforms
 * FreeBSD 10.0 with Clang 3.3
 * OS X 10.9.2 with Clang 3.5

If a platform does not appear to be in the previous list, it does not mean
that `m_trie` will not work in such environment. In fact the opposite is
probably true - the library was written with absolute portability in mind
and closely adheres to language and operating system environment
standards.

It only means that nobody tested it - you are encouraged to do so and
report either success or failure to the author.

## Build & install
The `m_trie` library has zero dependencies and requires only a
C89-compatible compiler.

In order to compile, test and install the library run the following 4
steps (some of which may require superuser privileges):
```
$ make
$ make test
$ make install
$ make clean
```

## License
The `m_trie` library is licensed under the terms of the 2-clause BSD
license.  For more information please consult the [LICENSE](LICENSE.md)
file. In case you need a different license, feel free to contact the
author.

## Author
Daniel Lovasko (daniel.lovasko@gmail.com)
