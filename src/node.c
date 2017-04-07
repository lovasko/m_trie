#include "m_trie.h"
#include "node.h"

/** Initialise a trie node.
  * NOTE: this function is for internal use only.
  *
  * @param[in]  trie trie
  * @param[out] nd   node
**/
void
node_init(m_trie* trie, node** nd)
{
  trie->tr_ncnt++;

  *nd = malloc(sizeof(node));
  (*nd)->nd_data = NULL;
  (*nd)->nd_type = NODE_REGULAR;
  (*nd)->nd_chld = NULL;
  (*nd)->nd_cidx = 0;
  (*nd)->nd_done = 0;
}

/** Initialise all children of the node.
  * NOTE: this function is for internal use only.
  *
  * @param[in] trie trie
  * @param[in] nd   node
**/
void
node_chld(m_trie* trie, node** nd)
{
  uint8_t i;

  (*nd)->nd_chld = malloc(sizeof(node*) * (size_t)trie->tr_ccnt);
  for (i = 0; i < trie->tr_ccnt; i++)
    (*nd)->nd_chld[i] = NULL;
}

/** Free all memory resources held by the trie node.
  * NOTE: this function is for internal use only.
  *
  * @param[in] trie trie
  * @param[in] nd   node
**/
void
node_free(m_trie* trie, node* nd)
{
  trie->tr_ncnt--;

  free(nd->nd_chld);
  free(nd);
}
