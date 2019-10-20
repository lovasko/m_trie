// Copyright (c) 2015-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#ifndef M_TRIE_H
#define M_TRIE_H

#include <stdint.h>
#include <stdbool.h>


// Semantic version.
#define M_TRIE_VERSION_MAJOR 1
#define M_TRIE_VERSION_MINOR 0
#define M_TRIE_VERSION_PATCH 0

// Return codes.
#define M_TRIE_OK          0
#define M_TRIE_E_NULL      1
#define M_TRIE_E_NOT_FOUND 2
#define M_TRIE_E_INVALID   3
#define M_TRIE_E_EXISTS    4
#define M_TRIE_E_PREFIX    5
#define M_TRIE_E_LENGTH    6
#define M_TRIE_E_UNKNOWN   7
#define M_TRIE_E_NO_VALUE  8

// Behaviour flags.
#define M_TRIE_OVERWRITE 1
#define M_TRIE_CLEANUP   2
#define M_TRIE_FREE      4

/// Prefix tree.
struct m_trie {
  void*     tr_root;                 ///< Root tree node.
  int16_t (*tr_hash)(const uint8_t); ///< Tree-level hash function.
  uint64_t  tr_ncnt;                 ///< Overall node count.
  uint64_t  tr_kcnt;                 ///< Number of stored keys.
  uint32_t  tr_maxl;                 ///< Length of the longest key.
  uint16_t  tr_ccnt;                 ///< Maximal children count per node.
  uint8_t   tr_flags;                ///< Behaviour flags.
  uint8_t   tr_pad;                  ///< Structure padding.
};

// General.
uint8_t m_trie_init(struct m_trie* tr,
                    int16_t (*hash)(const uint8_t),
                    const uint8_t flags);
uint8_t m_trie_free(struct m_trie* tr);
uint8_t m_trie_count(const struct m_trie* tr, uint64_t* cnt);
uint8_t m_trie_walk(struct m_trie* tr,
                    void* ptr,
                    bool (*func)(void*,const uint8_t*,const uint32_t,void*));

// Access.
uint8_t m_trie_search(const struct m_trie* tr,
                      const uint8_t* key,
                      const uint32_t len,
                      void** val);
uint8_t m_trie_insert(struct m_trie* tr,
                      const uint8_t* key,
                      const uint32_t len,
                      void* val);
uint8_t m_trie_min(struct m_trie* tr,
                   uint8_t* key,
                   const uint32_t* len,
                   void** val);
uint8_t m_trie_max(struct m_trie* tr,
                   uint8_t* key,
                   const uint32_t* len,
                   void** val);

// Set Operations.
uint8_t m_trie_union(struct m_trie* tr1, struct m_trie* tr2);
uint8_t m_trie_intersect(struct m_trie* tr1, struct m_trie* tr2);
uint8_t m_trie_subtract(struct m_trie* tr1, struct m_trie* tr2);

// Removal.
uint8_t m_trie_remove(struct m_trie* tr,
                      const uint8_t* key,
                      const uint32_t len,
                      const bool pfix);
uint8_t m_trie_remove_all(struct m_trie *tr);
uint8_t m_trie_trim(struct m_trie* tr);

// Hashing.
int16_t m_trie_hash_identity(const uint8_t key);
int16_t m_trie_hash_alphabet(const uint8_t key);
int16_t m_trie_hash_digits(const uint8_t key);
int16_t m_trie_hash_base64(const uint8_t key);
int16_t m_trie_hash_alphanumeric(const uint8_t key);
int16_t m_trie_hash_lower_alphabet(const uint8_t key);
int16_t m_trie_hash_upper_alphabet(const uint8_t key);

#endif
