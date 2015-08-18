#ifndef M_TRIE_NODE_H
#define M_TRIE_NODE_H

#define M_TRIE_NODE_TYPE_DATA 0
#define M_TRIE_NODE_TYPE_REGULAR 1

#include <stdint.h>

struct __m_node {
	void* data;
	struct __m_node** children;
	char key;
	uint8_t type;
	char padding[6];
};

int node_init(struct __m_node** node, uint8_t children_count);

#endif

