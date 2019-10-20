// Copyright (c) 2015-2019 Daniel Lovasko
// All Rights Reserved
//
// Distributed under the terms of the 2-clause BSD License. The full
// license is in the file LICENSE, distributed as part of this software.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>

#include "../src/m_trie.h"


static const char* err_msg[] = {
  "M_TRIE_OK",
  "M_TRIE_E_NULL",
  "M_TRIE_E_NOT_FOUND",
  "M_TRIE_E_INVALID",
  "M_TRIE_E_EXISTS",
  "M_TRIE_E_PREFIX",
  "M_TRIE_E_LENGTH",
  "M_TRIE_E_UNKNOWN",
  "M_TRIE_E_NO_VALUE"
};

#define CHECK(fn) {                \
  uint8_t _ret;                    \
  _ret = fn;                       \
  if (_ret != M_TRIE_OK) {         \
    printf("%s\n", err_msg[_ret]); \
  }                                \
}

uint64_t
mono_now(void)
{
  struct timespec ts;

  (void)clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_nsec + (uint64_t)ts.tv_sec * 100000000ULL;
}

int
main(int argc, char* argv[])
{
  struct m_trie tr;
  int opt;
  uint32_t len;
  uint8_t* key;
  uint8_t ret;

  CHECK(m_trie_init(&tr, m_trie_hash_lower_alphabet, M_TRIE_OVERWRITE))

  while ((opt = getopt(argc, argv, "ai:klnp:r:s:t")) != -1) {
    key = (uint8_t*)optarg;
    len = (uint32_t)strlen(optarg);

    start = mono_now();
    switch(opt) {
      case 'a': {
        CHECK(m_trie_remove_all(&tr))
        printf("Removing all");
        break;
      }

      case 'i': {
        CHECK(m_trie_insert(&tr, key, len, NULL))
        printf("Inserting \"%s\"", optarg);
        break;
      }

      case 'k': {
        printf("Cardinality: %" PRIu64, tr.tr_kcnt);
        break;
      }

      case 'l': {
        printf("Maximal length: %" PRIu32, tr.tr_maxl);
        break;
      }

      case 'n': {
        printf("Node count: %" PRIu64, tr.tr_ncnt);
        break;
      }

      case 'p': {
        CHECK(m_trie_remove(&tr, key, len, true))
        printf("Removing prefix \"%s\"", optarg);
        break;
      }

      case 'r': {
        CHECK(m_trie_remove(&tr, key, len, false))
        printf("Removing \"%s\"", optarg);
        break;
      }

      case 't': {
        CHECK(m_trie_trim(&tr))
        printf("Trimming\n");
        break;
      }

      case 's': {
        printf("Searching for \"%s\": ", optarg);
	ret = m_trie_search(&tr, key, len, NULL);
        if (ret == M_TRIE_OK) {
          printf("Found");
	} else {
          printf("Not found");
	}
        break;
      }

      default: {
        fprintf(stderr, "ERROR: invalid option '%c'\n", opt);
        return EXIT_FAILURE;
      }
    }

    end = mono_now();
    printf(" -> %" PRIu64 "\n", end - start);
  }

  CHECK(m_trie_free(&tr))

  return EXIT_SUCCESS;
}
