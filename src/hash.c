// Copyright (c) 2015-2018 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stdint.h>

#include "m_trie.h"


/// Identity hash function.
/// @return type-adjusted key
///
/// @param[in] key key
int16_t
m_trie_hash_identity(uint8_t key)
{
  return (int16_t)key;
}

/// Hash function that accepts both upper and lower alphabet characters.
/// @return hashed letter
///
/// @param[in] key key
int16_t
m_trie_hash_alphabet(uint8_t key)
{
  if (key >= 'A' && key <= 'Z')
    return key - 'A';

  if (key >= 'a' && key <= 'z')
    return 26 + key - 'a';

  return -1;
}

/// Hash function that accepts only decimal digits.
/// @return hashed digit
///
/// @param[in] key key
int16_t
m_trie_hash_digits(uint8_t key)
{
  if (key >= '0' && key <= '9')
    return key - '0';

  return -1;
}

/// Hash function that accepts only characters used in the Base64 encoding.
/// @return hashed Base64 character
///
/// @param[in] key key
int16_t
m_trie_hash_base64(uint8_t key)
{
  if (key >= 'A' && key <= 'Z')
    return key - 'A';

  if (key >= 'a' && key <= 'z')
    return 26 + key - 'a';

  if (key >= '0' && key <= '9')
    return 52 + key - '0';

  if (key == '/') return 62;
  if (key == '+') return 63;

  return -1;
}

/// Hash function that accepts both decimal digits and lower/upper alphabet.
/// @return hashed alphanumeric character
///
/// @param[in] key key
int16_t
m_trie_hash_alphanumeric(uint8_t key)
{
  if (key >= 'A' && key <= 'Z')
    return key - 'A';

  if (key >= 'a' && key <= 'z')
    return 26 + key - 'a';

  if (key >= '0' && key <= '9')
    return 52 + key - '0';

  return -1;
}

/// Hash function that accepts only lower-case alphabet letters.
/// @return hashed lower letter
///
/// @param[in] key key
int16_t
m_trie_hash_lower_alphabet(uint8_t key)
{
  if (key >= 'a' && key <= 'z')
    return key - 'a';

  return -1;
}

/// Hash function that accepts only upper-case alphabet letters.
/// @return hashed upper letter
///
/// @param[in] key key
int16_t
m_trie_hash_upper_alphabet(uint8_t key)
{
  if (key >= 'A' && key <= 'Z')
    return key - 'A';

  return -1;
}
