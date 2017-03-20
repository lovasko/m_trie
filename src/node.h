#ifndef M_TRIE_NODE_H
#define M_TRIE_NODE_H

#define NODE_DATA    0
#define NODE_REGULAR 1
#define NODE_TO_FREE 2

/** Trie internal node. */
typedef struct node {
  void*         nd_data; /**< Stored value.             */
  struct node** nd_chld; /**< Children nodes.           */
  char          nd_key;  /**< Hash function key.        */
  unsigned char nd_type; /**< One of the NODE_* values. */
  char          nd_pad[sizeof(void*) - 2];
} node;

void node_init(m_trie* trie, node** nd);
void node_chld(m_trie* trie, node** nd);
void node_free(m_trie* trie, node*  nd);

#endif
