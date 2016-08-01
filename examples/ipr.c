#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <m_trie.h>

int
main(int argc, char* argv[])
{
	m_trie trie;
	int option;
	char input[255];

	m_trie_init(&trie, m_trie_hash_lower_alphabet, M_TRIE_OVERWRITE_ALLOW);

	while ((option = getopt(argc, argv, "i:p:r:")) != -1) {
		switch(option) {
			case 'i':
				m_trie_insert(&trie, optarg, strlen(optarg), NULL);
				printf ("Inserting \"%s\"\n", optarg);
			break;

			case 'p':
				m_trie_remove_prefix(&trie, optarg, strlen(optarg));
				printf("Removing prefix \"%s\"\n", optarg);
			break;

			case 'r':
				m_trie_remove(&trie, optarg, strlen(optarg));
				printf ("Removing \"%s\"\n", optarg);
			break;

			default: 
				fprintf(stderr, "ERROR: invalid arguments\n");
			return EXIT_FAILURE;
		}
	}

	while (1) {
		memset(input, '\0', 255);
		scanf("%s", input);
		if (m_trie_search(&trie, input, strlen(input), NULL) == M_TRIE_OK)
			printf("Yes!\n");
	}

	return EXIT_SUCCESS;
}

