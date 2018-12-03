// Copyright (c) 2015-2018 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#ifndef M_TRIE_H
#define M_TRIE_H

#include <stdlib.h>
#include <stdint.h>


/* Return codes. */
#define M_TRIE_OK          0
#define M_TRIE_E_NULL      1
#define M_TRIE_E_NOT_FOUND 2
#define M_TRIE_E_INVALID   3
#define M_TRIE_E_EXISTS    4
#define M_TRIE_E_PREFIX    5
#define M_TRIE_E_LENGTH    6
#define M_TRIE_E_UNKNOWN   7
#define M_TRIE_E_NO_VALUE  8

/* Behaviour flags. */
#define M_TRIE_OVERWRITE 1
#define M_TRIE_CLEANUP   2
#define M_TRIE_FREE      4

/** Trie. */
typedef struct m_trie {
  void*     tr_root;           /**< Root tree node.                  */
  int16_t (*tr_hash)(uint8_t); /**< Tree-level hash function.        */
  uint64_t  tr_ncnt;           /**< Overall node count.              */
  uint64_t  tr_kcnt;           /**< Number of stored keys.           */
  uint32_t  tr_maxl;           /**< Length of the longest key.       */
  uint16_t  tr_ccnt;           /**< Maximal children count per node. */
  uint8_t   tr_flags;          /**< Behaviour flags.                 */
  uint8_t   tr_pad;            /**< Structure padding.               */
} m_trie;

/* General. */
int m_trie_init(m_trie* tr, int16_t (*hash)(uint8_t), uint8_t flags);
int m_trie_free(m_trie* tr);
int m_trie_count(m_trie* tr, uint64_t* cnt);

/* Access. */
int m_trie_search(m_trie* tr, uint8_t* key, uint32_t len, void** val);
int m_trie_insert(m_trie* tr, uint8_t* key, uint32_t len, void* val);

/* Removal. */
int m_trie_remove(m_trie* tr, uint8_t* key, uint32_t len, uint8_t pfix);
int m_trie_remove_all(m_trie *tr);
int m_trie_trim(m_trie* tr);

/* Hashing. */
int16_t m_trie_hash_identity(uint8_t key);
int16_t m_trie_hash_alphabet(uint8_t key);
int16_t m_trie_hash_digits(uint8_t key);
int16_t m_trie_hash_base64(uint8_t key);
int16_t m_trie_hash_alphanumeric(uint8_t key);
int16_t m_trie_hash_lower_alphabet(uint8_t key);
int16_t m_trie_hash_upper_alphabet(uint8_t key);

#endif
