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
node_init(m_trie* trie, struct _node** node)
{
  trie->ncnt++;

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
node_chld(m_trie* trie, struct _node** node)
{
  uint8_t i;

  (*node)->chld = malloc(sizeof(struct _node*) * trie->ccnt);
  for (i = 0; i < trie->ccnt; i++)
    (*node)->chld[i] = NULL;
}

/**
  * Free all memory resources held by the trie node.
  * NOTE: this function is for internal use only.
  *
  * @param[in] node node
**/
void
node_free(m_trie* trie, struct _node** node)
{
  trie->ncnt--;

  free((*node)->chld);
  free(*node);
}

