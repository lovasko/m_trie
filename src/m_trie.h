#ifndef M_TRIE_H
#define M_TRIE_H

#include <stdlib.h>
#include <stdint.h>

#define M_TRIE_OK          0
#define M_TRIE_E_NULL      1
#define M_TRIE_E_NOT_FOUND 2
#define M_TRIE_E_INVALID   3
#define M_TRIE_E_EXISTS    4
#define M_TRIE_E_PREFIX    5
#define M_TRIE_E_LENGTH    6
#define M_TRIE_E_UNKNOWN   7
#define M_TRIE_E_NO_VALUE  8

#define M_TRIE_OVERWRITE_ALLOW   0
#define M_TRIE_OVERWRITE_PREVENT 1

/** Opaque main trie object. */
typedef struct m_trie {
  void* root;            /**< Root node.                  */
  int16_t (*hash)(char); /**< Tree-level hash function.   */
  size_t ncnt;           /**< Overall node count.         */
  uint8_t ccnt;          /**< Each node's children count. */
  uint8_t owrt;          /**< Overwrite policy.           */
  char pad[sizeof(void*)-2];
} m_trie;

/* general */
int m_trie_init(m_trie* trie, int16_t (*hash)(char), uint8_t owrt);
int m_trie_free(m_trie* trie);

/* access */
int m_trie_search(m_trie* trie, char* key, size_t len, void** val);
int m_trie_insert(m_trie* trie, char* key, size_t len, void* val);

/* remove */
int m_trie_remove(m_trie* trie, char* key, size_t len);
int m_trie_remove_prefix(m_trie *trie, char* key, size_t len);
int m_trie_remove_all(m_trie* trie);

/* hash */
int16_t m_trie_hash_identity(char key);
int16_t m_trie_hash_alphabet(char key);
int16_t m_trie_hash_digits(char key);
int16_t m_trie_hash_base64(char key);
int16_t m_trie_hash_alphanumeric(char key);
int16_t m_trie_hash_lower_alphabet(char key);
int16_t m_trie_hash_upper_alphabet(char key);

#endif

