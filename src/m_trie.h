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

#define M_TRIE_OVERWRITE 1
#define M_TRIE_CLEANUP   2
#define M_TRIE_FREE      4

/** Main trie object. */
typedef struct m_trie {
  void*     tr_root;           /**< Root tree node.                  */
  int16_t (*tr_hash)(uint8_t); /**< Tree-level hash function.        */
  uint64_t  tr_ncnt;           /**< Overall node count.              */
  uint32_t  tr_maxl;           /**< Length of the longest key.       */
  uint8_t   tr_ccnt;           /**< Maximal children count per node. */
  uint8_t   tr_flags;          /**< Behaviour flags.                 */
  uint8_t   tr_pad[2];         /**< Structure padding.               */
} m_trie;

/* general */
int m_trie_init(m_trie* trie, int16_t (*hash)(uint8_t), uint8_t flags);
int m_trie_free(m_trie* trie);

/* access */
int m_trie_search(m_trie* trie, uint8_t* key, uint32_t len, void** val);
int m_trie_insert(m_trie* trie, uint8_t* key, uint32_t len, void* val);

/* remove */
int m_trie_remove(m_trie* trie, uint8_t* key, uint32_t len, uint8_t pfix);
int m_trie_remove_all(m_trie *trie);
int m_trie_trim(m_trie* trie);

/* hash */
int16_t m_trie_hash_identity(uint8_t key);
int16_t m_trie_hash_alphabet(uint8_t key);
int16_t m_trie_hash_digits(uint8_t key);
int16_t m_trie_hash_base64(uint8_t key);
int16_t m_trie_hash_alphanumeric(uint8_t key);
int16_t m_trie_hash_lower_alphabet(uint8_t key);
int16_t m_trie_hash_upper_alphabet(uint8_t key);

#endif
