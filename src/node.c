#include <stdint.h>
#include <stdlib.h>

#include "m_trie.h"
#include "node.h"

/**
  * Initialise a trie node.
  * NOTE: this function is for internal use only.
  *
  * @param[in] node node
**/
void
node_init(struct _node** node)
{
  *node = malloc(sizeof(struct _node));
  (*node)->data = NULL;
  (*node)->type = M_TRIE_NODE_TYPE_REGULAR;
  (*node)->chld = NULL;
}

/**
  * Initialise all children of the node.
  * NOTE: this function is for internal use only.
  *
  * @param[in] node node
  * @param[in] ccnt children count
**/
void
node_init_children(struct _node** node, uint8_t ccnt)
{
  uint8_t i;

  (*node)->chld = malloc(sizeof(struct _node*) * ccnt);

  for (i = 0; i < ccnt; i++)
    (*node)->chld[i] = NULL;
}

/**
  * Free all memory resources held by the trie node.
  * NOTE: this function is for internal use only.
  *
  * @param[in] node node
**/
void
node_free(struct _node** node)
{
  free((*node)->chld);
  free(*node);
}

