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
#include <m_trie.h>

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

#define CHECK(fn) {               \
  int ret;                        \
  ret = fn;                       \
  if (ret != M_TRIE_OK)           \
    printf("%s\n", err_msg[ret]); \
}

int
main(int argc, char* argv[])
{
  struct m_trie tr;
  int opt;

  CHECK(m_trie_init(&tr, m_trie_hash_lower_alphabet, M_TRIE_OVERWRITE))

  while ((opt = getopt(argc, argv, "ai:klnp:r:s:t")) != -1) {
    switch(opt) {
      case 'a':
        CHECK(m_trie_remove_all(&tr))
        printf("Removing all\n");
        break;

      case 'i':
        CHECK(m_trie_insert(&tr,
                            (uint8_t*)optarg,
                            (uint32_t)strlen(optarg),
                            NULL))
        printf ("Inserting \"%s\"\n", optarg);
        break;

      case 'k':
        printf("Number of keys: %" PRIu64 "\n", tr.tr_kcnt);
        break;

      case 'l':
        printf("Maximal length: %" PRIu32 "\n", tr.tr_maxl);
        break;

      case 'n':
        printf("Node count: %" PRIu64 "\n", tr.tr_ncnt);
        break;

      case 'p':
        CHECK(m_trie_remove(&tr,
                            (uint8_t*)optarg,
                            (uint32_t)strlen(optarg),
                            1))
        printf("Removing prefix \"%s\"\n", optarg);
        break;

      case 'r':
        CHECK(m_trie_remove(&tr,
                            (uint8_t*)optarg,
                            (uint32_t)strlen(optarg),
                            0))
        printf("Removing \"%s\"\n", optarg);
        break;

      case 't':
        CHECK(m_trie_trim(&tr))
        printf("Trimming\n");
        break;

      case 's':
        printf("Searching for \"%s\": ", optarg);
        if (m_trie_search(&tr,
                          (uint8_t*)optarg,
                          (uint32_t)strlen(optarg),
                          NULL) == M_TRIE_OK)
          printf("Found\n");
        else
          printf("Not found\n");
        break;

      default: 
        fprintf(stderr, "ERROR: invalid arguments\n");
        return EXIT_FAILURE;
    }
  }

  CHECK(m_trie_free(&tr))

  return EXIT_SUCCESS;
}
