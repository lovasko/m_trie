#ifndef M_TRIE_H
#define M_TRIE_H

#include <stdlib.h>


#define M_TRIE_OK          0
#define M_TRIE_E_NULL      1
#define M_TRIE_E_NOT_FOUND 2
#define M_TRIE_E_INVALID   3
#define M_TRIE_E_EXISTS    4
#define M_TRIE_E_PREFIX    5
#define M_TRIE_E_LENGTH    6
#define M_TRIE_E_UNKNOWN   7
#define M_TRIE_E_NO_VALUE  8

#define M_TRIE_OVERWRITE 1
#define M_TRIE_CLEANUP   2
#define M_TRIE_FREE      4

/** Main trie object. */
typedef struct m_trie {
  void*   tr_root;        /**< Root tree node.                  */
  short (*tr_hash)(char); /**< Tree-level hash function.        */
  size_t  tr_ncnt;        /**< Overall node count.              */
  int     tr_ccnt;        /**< Maximal children count per node. */
  int     tr_flags;       /**< Behaviour flags.                 */
} m_trie;

/* general */
int m_trie_init(m_trie* trie, short (*hash)(char), int flags);
int m_trie_free(m_trie* trie);

/* access */
int m_trie_search(m_trie* trie, char* key, size_t len, void** val);
int m_trie_insert(m_trie* trie, char* key, size_t len, void* val);

/* remove */
int m_trie_remove(m_trie* trie, char* key, size_t len);
int m_trie_remove_prefix(m_trie *trie, char* key, size_t len);
int m_trie_trim(m_trie* trie);

/* hash */
short m_trie_hash_identity(char key);
short m_trie_hash_alphabet(char key);
short m_trie_hash_digits(char key);
short m_trie_hash_base64(char key);
short m_trie_hash_alphanumeric(char key);
short m_trie_hash_lower_alphabet(char key);
short m_trie_hash_upper_alphabet(char key);

#endif
