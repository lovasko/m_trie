# m_trie
General-purpose implementation of the prefix tree data structure for the
C89 language.

## Introduction
The data structure is able to store key/value pairs, where *key* is an
array of bytes and *value* is an arbitrary pointer. Even though the key
type is `char*` due to convenience reasons regarding C string constants,
it can contain all possible byte values. The zero byte is not treated as
the end of the key (and therefore valid as one of the key's bytes), as the
length of the key is determined by a separate argument.

The keys are expected to be reasonably small (tens of bytes) and values
are allowed to be `NULL`.

## API
### General
Before calling any other function, the `m_trie` object needs to be
initialised via the `m_trie_init` function. This function does not
allocate the `m_trie` object  on behalf of the user, therefore it needs to
be allocated beforehand, either on the stack or on the heap.

The initialisation function expects three arguments: a pointer to a
`m_trie` instance, pointer to a hash function (see below) and a behavioral
decision in case of inserting the same key twice: `M_TRIE_OVERWRITE_ALLOW`
and `M_TRIE_OVERWRITE_PREVENT`.

To free all resources held by the data structure, call the `m_trie_free`
function.

Prototypes:
```c
int m_trie_init(m_trie* trie, int16_t(*hash)(char), uint8_t owrt);
int m_trie_free(m_trie* trie);
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
int m_trie_insert(m_trie* trie, char* key, size_t len, void* val);
int m_trie_search(m_trie* trie, char* key, size_t len, void** val);
```

### Removing
The library offers three function to remove keys (an their associated
values): `m_trie_remove` is a direct counterpart to the `m_trie_insert`
function. It is important to note that the `m_trie_remove` function does
no deallocations of memory and simply marks node as if it did not contain
any data. This decision was taken due to performance reasons, where
cascading freeing of memory could pose significant memory delays and
therefore uncontrollable jitter in certain scenarios.

The second function, `m_trie_remove_prefix`, remove all keys that start
with the specified key. The key itself might not indicate a previously
inserted key, e.g. it is possible to call the `m_trie_remove_prefix`
function with key `"ca"` and it would delete both `"california"` and
`"carpool"`, even though `"ca"` itself was not in the trie. Contrary to
the previous remove function, `m_trie_remove_prefix` performs all
necessary deallocations and can therefore be considered as a possible
cause of occasional small slowdowns.

The last removal function, `m_trie_remove_all` simply removes and
deallocates all key stored in the trie. It is still possibe to use the
`m_trie` instance anfterwards, without a need to call `m_trie_init`.

Prototypes:
```c
int m_trie_remove(m_trie* trie, char* key, size_t len);
int m_trie_remove_prefix(m_trie* trie, char* key, size_t len);
int m_trie_remove_all(m_trie* trie);
```

### Hash functions
The `m_trie` data structure needs a user-supplied hash function to
navigate the levels of the tree. Each `m_trie` hash function takes a
`char` value as input and produces a `int16_t` value. In case that the
character on input is not valid, a proper `m_trie` hash function must
return `-1`. Otherwise, the function must uniquely map all the supported
characters onto the interval `0..n`. Each `m_trie` hash function therefore
must be a *minimal perfect* hash function.

#### Predefined
The library identifies certain common hash functions that are ubiquitous
and general enough to be included, such as the identity function
`m_trie_hash_identity` or a hash function that supports only the letters
of English alphabet `m_trie_hash_alphabet`.

Prototypes:
 ```c
int16_t m_trie_hash_identity(char key);
int16_t m_trie_hash_alphabet(char key);
int16_t m_trie_hash_digits(char key);
int16_t m_trie_hash_base64(char key);
int16_t m_trie_hash_alphanumeric(char key);
int16_t m_trie_hash_lower_alphabet(char key);
int16_t m_trie_hash_upper_alphabet(char key);
 ```

#### Custom
Users of the library are welcomed to create custom hash functions that
obey the rules described above. An example of a hash function that accepts
only characters `'0'` and `'1'`:

```c
int16_t
hash_01(char c)
{
	if (c == '0') return 0;
	if (c == '1') return 1;

	return -1;
}
```

## Complexity
The table below makes an assumption that the hashing function operates in
both constant time and constant space.

| Function              | Time     | Space    |
|-----------------------|----------|----------|
|`m_trie_init`          | `O(1)`   | `O(1)`   |
|`m_trie_free`          | `O(k*a)` | `O(k*a)` |
|`m_trie_insert`        | `O(k)`   | `O(k)`   |
|`m_trie_search`        | `O(k)`   | `O(1)`   |
|`m_trie_remove`        | `O(k)`   | `O(1)`   |
|`m_trie_remove_prefix` | `O(k*a)` | `O(k*a)` |
|`m_trie_remove_all`    | `O(k*a)` | `O(k*a)` |
|`m_trie_hash_*`        | `O(1)`   | `O(1)`   |

Where:
* `k` is the length of the longest key
* `a` is the number of accepted inputs by the hash function

Note that none of time nor space function classes depend on the variable
`n`, which is the number of inserted key/value pairs. This is a crucial
feature of the prefix tree.

## Examples
 * [List of users](examples/passwd.c)
 * [Insert & Remove & Remove prefix](examples/ipr.c)

## Supported platforms
 * FreeBSD 10.0 with Clang 3.3
 * OS X 10.9.2 with Clang 3.5

If a platform does not appear to be in the previous list, it does not mean
that `m_trie` will not work in such environment. It only means that nobody
tested it - you are encouraged to do so and report either success or
failure.

## Build & install
```
$ ninja
$ sudo ./install.sh
```

## License
2-clause BSD license. For more information please consult the
[LICENSE](LICENSE.md) file. In the case that you need a different license,
feel free to contact me.

## Author
Daniel Lovasko (daniel.lovasko@gmail.com)

