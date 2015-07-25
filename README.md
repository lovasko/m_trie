# m_trie
General-purpose trie implementation in the C89 language that runs on all
POSIX-compatible systems.

## Features
### Data storage
In order to store data in the try under a specific key, use the `m_trie_set`
function. The behaviour of the function can be changed by setting the
`M_TRIE_OVERWRITE_*` argument to either `_ALLOW` or `_PREVENT`. See
[m_list](github.com/lovasko/m_list) for more information about the deep and
shadow copy method.

### Data retrieval
To obtain the data stored in the trie, use the `m_trie_get` function.

### Presence test
The `m_trie_get` function can be used as a pure presence test. By calling the
function with the last argument `NULL`, the function still returns either
`M_TRIE_OK` or `M_TRIE_E_NOT_FOUND`.

### Keys and values
To retrieve all keys and/or values stored in the trie, use functions
`m_trie_keys` and `m_trie_value` respectively.

## Time and space complexity

| Operation            | Time     |
|----------------------|----------|
|`m_trie_init`         | `O(h)`   |
|`m_trie_set`          | `O(m*h)` |
|`m_trie_get`          | `O(m*h)` |
|`m_trie_keys`         | `O(1)`   |
|`m_trie_values`       | `O(1)`   |
|`m_trie_error_string` | `O(1)`   |

where:
* `h` is the time of the hashing function
* `m` is the length of the longest key

It is generally advised to keep your hashing function in the `O(1)` class.

## Example
### Hashing function
This function hashes the character set `._/[a-z]`. It is used as the
hashing function in the follow-up example below.
```C
static int16_t
hash(char key)
{
  if (key == '.')
    return 0;

  if (key == '_')
    return 1;

  if (key == '/')
    return 2;

  if (key >= 'a' && key <= 'z')
    return (key - 'a') + 3;

  return -1;
}
```

### Get and set
```C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <m_trie.h>

/* insert hash function here */

int
main(int argc, char* argv[])
{
  struct m_trie trie;
  int i;
  char input[64];

  m_trie_init(&trie, hash);
  for (i = 1; i < argc; i++)
    m_trie_set(&trie,
               argv[i],
               M_TRIE_COPY_SHALLOW,
               M_TRIE_OVERWRITE_PREVENT,
               NULL,
               0);

  while (1) {
    memset(input, '\0', 64);
    if (fgets(input, 64, stdin) == NULL)
      break;
    input[strlen(input)-1] = '\0';

    if (m_trie_get(&trie, input, NULL) == M_TRIE_OK)
      printf("Contains '%s'.\n", input);
  }

  return EXIT_SUCCESS;
}
```

## Supported platforms
 * FreeBSD 10.0 with Clang 3.3

If a platform does not appear to be in the previous list, it does not mean that
`m_trie` will not work in such environment. It only means that nobody tested
it - you are encouraged to do so and report either success or failure.

## Build & install
```
$ ninja
$ sudo ./install.sh
```

## License
2-clause BSD license. For more information please consult the
[LICENSE](LICENSE.md) file. In the case that you need a different license, feel
free to contact me.

## Author
Daniel Lovasko (lovasko@freebsd.org)

