#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
  m_trie trie;
  int opt;
  uint8_t* key;
  uint32_t len;

  CHECK(m_trie_init(&trie, m_trie_hash_lower_alphabet, M_TRIE_OVERWRITE))

  while ((opt = getopt(argc, argv, "ai:lnp:r:s:t")) != -1) {
    key = (uint8_t*)optarg;
    len = (uint32_t)strlen(optarg);

    switch(opt) {
      case 'a':
        CHECK(m_trie_remove_all(&trie))
        printf("Removing all\n");
        break;

      case 'i':
        CHECK(m_trie_insert(&trie, key, len, NULL))
        printf ("Inserting \"%s\"\n", optarg);
        break;

      case 'l':
        printf("Maximal length: %u\n", trie.tr_maxl);
        break;

      case 'n':
        printf("Node count: %llu\n", trie.tr_ncnt);
        break;

      case 'p':
        CHECK(m_trie_remove(&trie, key, len, 1))
        printf("Removing prefix \"%s\"\n", optarg);
        break;

      case 'r':
        CHECK(m_trie_remove(&trie, key, len, 0))
        printf("Removing \"%s\"\n", optarg);
        break;

      case 't':
        CHECK(m_trie_trim(&trie))
        printf("Trimming \n");
        break;

      case 's':
        printf("Searching for \"%s\": ", optarg);
        if (m_trie_search(&trie, key, len, NULL) == M_TRIE_OK)
          printf("Found\n");
        else
          printf("Not found\n");
        break;

      default:
        fprintf(stderr, "ERROR: invalid arguments\n");
        return EXIT_FAILURE;
    }
  }

  CHECK(m_trie_free(&trie))

  return EXIT_SUCCESS;
}
