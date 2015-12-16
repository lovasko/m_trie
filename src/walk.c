#ifdef M_TRIE_DEBUG

#include <stdio.h>
#include <string.h>

#include "m_trie.h"
#include "node.h"

static void
print_children(struct __m_node* node, uint8_t children_count)
{
	uint8_t i;
	int first;

	first = 0;

	for (i = 0; i < children_count; i++)
		if (node->children[i] != NULL)
			printf("%s%d", first++ ? ", " : "", node->children[i]->key);
}

static char*
node_type(uint8_t type)
{
	if (type == M_TRIE_NODE_TYPE_DATA)
		return "data";

	if (type == M_TRIE_NODE_TYPE_REGULAR)
		return "regular";

	return "unknown";
}

int
m_trie_interactive_walk(struct m_trie* trie, void(*print_fn)(void*))
{
	struct __m_node* node;
	unsigned int choice;
	int16_t h;
	char command[32];

	if (trie == NULL)
		return M_TRIE_E_NULL;

	node = trie->root;

	while (1) {
		printf("type: %s\n", node_type(node->type));
		printf("children: ");
		if (node->children == NULL)
			printf("none");
		else
			print_children(node, trie->children_count);
		printf("\n");

		if (node->type == M_TRIE_NODE_TYPE_DATA) {
			printf("data: ");
			print_fn(node->data);
			printf("\n");
		}

		printf("> ");	
		fflush(stdout);
		fgets(command, 32, stdin);

		if (sscanf(command, "go %u \n", &choice) == 1) {
			if (choice > 255) {
				printf("Index out of bounds.\n");
				continue;
			}

			h = trie->hash((char)choice);

			if (h < 0) {
				printf("Invalid hash function input.\n");
				continue;
			}

			if (node->children == NULL) {
				printf("The node does not have children.\n");
				continue;
			}

			if (node->children[h] == NULL) {
				printf("The node does not have a child at index '%d'.\n", h);
				continue;
			}
				
			node = node->children[h];
		}

		if (strncmp(command, "quit", 4) == 0
		 || strncmp(command, "exit", 4) == 0)
			break;

		if (strncmp(command, "restart", 7) == 0)
			node = trie->root;

		printf("Unknown command.\n");
	}

	return M_TRIE_OK;
}

#else

typedef int no_debug_dummy;

#endif

