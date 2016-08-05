#ifndef M_TRIE_NODE_H
#define M_TRIE_NODE_H

#include <stdint.h>

#define M_TRIE_NODE_TYPE_DATA 0
#define M_TRIE_NODE_TYPE_REGULAR 1

/** Trie internal node. */
struct _node {
  void* data;          /**< Pointer to stored value. */
  struct _node** chld; /**< Children nodes. */
  char key;            /**< Node key. */
  uint8_t type;        /**< DATA or REGULAR. */
  char pad[sizeof(void*) - 2];
};

void node_init(struct _node** node);
void node_init_children(struct _node** node, uint8_t ccnt);
void node_free(struct _node** node);

#endif

