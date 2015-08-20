#ifndef M_TRIE_NODE_H
#define M_TRIE_NODE_H

#define M_TRIE_NODE_TYPE_DATA 0
#define M_TRIE_NODE_TYPE_REGULAR 1

#define M_TRIE_NODE_COPY_NULL    0
#define M_TRIE_NODE_COPY_SHALLOW 1
#define M_TRIE_NODE_COPY_DEEP    2

#include <stdint.h>

struct __m_node {
	void* data;
	struct __m_node** children;
	char key;
	uint8_t type;
	uint8_t copy;
	char padding[5];
};

int node_init(struct __m_node** node, uint8_t children_count);
int node_free(struct __m_node** node);

#endif

