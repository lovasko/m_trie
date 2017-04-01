#ifndef M_TRIE_NODE_H
#define M_TRIE_NODE_H

/* Node type identifiers. */
#define NODE_DATA    0
#define NODE_REGULAR 1
#define NODE_TO_FREE 2

/** Trie internal node. */
typedef struct node {
  void*         nd_data; /**< Stored value.                    */
  struct node** nd_chld; /**< Children nodes.                  */
  char          nd_key;  /**< Hash function key.               */
  unsigned char nd_type; /**< One of the NODE_* values.        */
  unsigned char nd_cidx; /**< Index into array of children.    */
  unsigned char nd_done; /**< Indicator of finished traversal. */
  char          nd_pad[sizeof(int)];
} node;

void node_init(m_trie* trie, node** nd);
void node_chld(m_trie* trie, node** nd);
void node_free(m_trie* trie, node*  nd);

#endif
