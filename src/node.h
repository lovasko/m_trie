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
  uint8_t       nd_key;  /**< Hash function key.               */
  uint8_t       nd_type; /**< One of the NODE_* values.        */
  uint8_t       nd_cidx; /**< Index into array of children.    */
  uint8_t       nd_done; /**< Indicator of finished traversal. */
  uint32_t      nd_pad;  /**< Structure padding.               */
} node;

void node_init(m_trie* trie, node** nd);
void node_chld(m_trie* trie, node** nd);
void node_free(m_trie* trie, node*  nd);

#endif
