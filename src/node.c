#include <stdint.h>
#include <stdlib.h>

#include "m_trie.h"
#include "node.h"

int
node_init(struct __m_node** node, uint8_t children_count)
{
	uint8_t i;

	*node = malloc(sizeof(struct __m_node));
	(*node)->data = NULL;
	(*node)->type = M_TRIE_NODE_TYPE_REGULAR;
	(*node)->children = malloc(sizeof(struct __m_node*) * children_count);

	for (i = 0; i < children_count; i++)
		(*node)->children[i] = NULL;

	return M_TRIE_OK;
}

int
node_free(struct __m_node** node)
{
	free((*node)->children);
	if ((*node)->type == M_TRIE_NODE_COPY_DEEP)
		free((*node)->data);
	free(*node);

	return M_TRIE_OK;
}

