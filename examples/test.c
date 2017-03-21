#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <m_trie.h>


int
main(int argc, char* argv[])
{
  m_trie trie;
  int opt;

  m_trie_init(&trie, m_trie_hash_lower_alphabet, M_TRIE_OVERWRITE);

  while ((opt = getopt(argc, argv, "ai:np:r:s:t")) != -1) {
    switch(opt) {
      case 'a':
        m_trie_remove_prefix(&trie, NULL, 0);
        printf("Removing all\n");
        break;

      case 'i':
        m_trie_insert(&trie, optarg, strlen(optarg), NULL);
        printf ("Inserting \"%s\"\n", optarg);
        break;

      case 'n':
        printf("Node count: %zu\n", trie.tr_ncnt);
        break;

      case 'p':
        m_trie_remove_prefix(&trie, optarg, strlen(optarg));
        printf("Removing prefix \"%s\"\n", optarg);
        break;

      case 'r':
        m_trie_remove(&trie, optarg, strlen(optarg));
        printf("Removing \"%s\"\n", optarg);
        break;

      case 't':
        m_trie_trim(&trie);
        printf("Trimming \n");
        break;

      case 's':
        printf("Searching for \"%s\": ", optarg);
        if (m_trie_search(&trie, optarg, strlen(optarg), NULL) == M_TRIE_OK)
          printf("Found\n");
        else
          printf("Not found\n");
        break;

      default: 
        fprintf(stderr, "ERROR: invalid arguments\n");
        return EXIT_FAILURE;
    }
  }

  m_trie_free(&trie);

  return EXIT_SUCCESS;
}
