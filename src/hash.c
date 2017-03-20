#include <limits.h>

#include "m_trie.h"


/** Identity hash function.
  *
  * @param[in] key key
  * @return type-adjusted key
**/
short
m_trie_hash_identity(char key)
{
  short result;

  result = (short)key;
  result -= (short)CHAR_MIN;

  return result;
}

/** Hash function that accepts both upper and lower alphabet characters.
  *
  * @param[in] key key
  * @return hashed letter
**/
short
m_trie_hash_alphabet(char key)
{
  if (key >= 'A' && key <= 'Z')
    return key - 'A';

  if (key >= 'a' && key <= 'z')
    return 26 + key - 'a';

  return -1;
}

/** Hash function that accepts only decimal digits.
  *
  * @param[in] key key
  * @return hashed digit
**/
short
m_trie_hash_digits(char key)
{
  if (key >= '0' && key <= '9')
    return key - '0';

  return -1;
}

/** Hash function that accepts only characters used in the Base64 encoding.
  *
  * @param[in] key key
  * @return hashed Base64 character
**/
short
m_trie_hash_base64(char key)
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

/** Hash function that accepts both decimal digits and lower/upper alphabet.
  *
  * @param[in] key key
  * @return hashed alphanumeric character
**/
short
m_trie_hash_alphanumeric(char key)
{
  if (key >= 'A' && key <= 'Z')
    return key - 'A';

  if (key >= 'a' && key <= 'z')
    return 26 + key - 'a';

  if (key >= '0' && key <= '9')
    return 52 + key - '0';

  return -1;
}

/** Hash function that accepts only lower-case alphabet letters.
  *
  * @param[in] key key
  * @return hashed lower letter
**/
short
m_trie_hash_lower_alphabet(char key)
{
  if (key >= 'a' && key <= 'z')
    return key - 'a';

  return -1;
}

/** Hash function that accepts only upper-case alphabet letters.
  *
  * @param[in] key key
  * @return hashed upper letter
**/
short
m_trie_hash_upper_alphabet(char key)
{
  if (key >= 'A' && key <= 'Z')
    return key - 'A';

  return -1;
}
