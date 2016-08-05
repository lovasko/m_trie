#ifndef M_TRIE_NODE_H
#define M_TRIE_NODE_H

#define M_TRIE_NODE_TYPE_DATA 0
#define M_TRIE_NODE_TYPE_REGULAR 1

#include <stdint.h>

struct _node {
  void* data;
  struct _node** chld;
  char key;
  uint8_t type;
  char pad[sizeof(void*) - 2];
};

void node_init(struct _node** node);
void node_init_children(struct _node** node, uint8_t ccnt);
void node_free(struct _node** node);

#endif

