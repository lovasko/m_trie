#include <stdlib.h>
#include <stdio.h>

#include "m_trie.h"
#include "common.h"
#include "node.h"

/** Gather all nodes that are located in a specified subtree.
  *
  * @param[in] trie trie
  * @param[in] root root of the subtree
  *
  * @return array of node pointers
**/
static node**
subtree(m_trie* trie, node* root)
{
  node** arr;
  size_t cur;
  int end;
  int i;

  cur = 0;
  end = 1;

  /* Allocate an array of pointers to nodes. */
  arr = malloc(sizeof(node*) * (trie->tr_ncnt + 1));
  arr[0] = root;

  /* Fill the node array with nodes in the BFS-order. */
  for (cur = 0; cur < trie->tr_ncnt; cur++)
    if (arr[cur]->nd_chld != NULL)
      for (i = 0; i < trie->tr_ccnt; i++)
        if (arr[cur]->nd_chld[i] != NULL)
          arr[end++] = arr[cur]->nd_chld[i];

  return arr;
}

/** Check whether all children of the node are NULL.
  * NOTE: This function assumes that the nd_chld array is non-NULL.
  *
  * @param[in] trie trie
  * @param[in] nd   node
  *
  * @return boolean decision
  * @retval 0 the node has some non-NULL children
  * @retval 1 the node has all children NULL
**/
static int
all_null(m_trie* trie, node* nd)
{
  int i;

  for (i = 0; i < trie->tr_ccnt; i++)
    if (nd->nd_chld[i] != NULL)
      return 0;

  return 1;
}

/** Remove a key from the trie.
  *
  * @param[in] trie trie
  * @param[in] key  key
  * @param[in] len  key length
  *
  * @return status code
  * @retval M_TRIE_E_NULL      trie and/or key is NULL
  * @retval M_TRIE_E_LENGTH    key length is zero
  * @retval M_TRIE_E_INVALID   key contains invalid characters
  * @retval M_TRIE_E_NOT_FOUND key is not in tr
  * @retval M_TRIE_E_NO_VALUE  no value is associated with the key
  * @retval M_TRIE_OK          success
**/
int
m_trie_remove(m_trie* trie, char* key, size_t len)
{
  node* nd;
  int ret;

  /* Locate the inner node of the trie. */
  ret = locate(trie, key, len, &nd);
  if (ret != M_TRIE_OK)
    return ret;

  /* Nodes that do not store data can not be directly removed. */
  if (nd->nd_type != NODE_DATA)
    return M_TRIE_E_NO_VALUE;

  /* Mark the node to be up for removal, so that subsequent trim will
  * delete it. */
  nd->nd_type = NODE_TO_FREE;
  nd->nd_data = NULL;

  /* Optionally run the garbage-collection procedure. */
  if (trie->tr_flags & M_TRIE_CLEANUP)
    m_trie_trim(trie);

  return M_TRIE_OK;
}

/** Remove all keys that start with the specified prefix.
  *
  * @param[in] trie trie
  * @param[in] key  key
  * @param[in] len  key length
  *
  * @return status code
  * @retval M_TRIE_E_NULL      trie is NULL
  * @retval M_TRIE_E_LENGTH    key length is zero
  * @retval M_TRIE_E_INVALID   key contains invalid characters
  * @retval M_TRIE_E_NOT_FOUND key is not stored in the trie
  * @retval M_TRIE_OK          success
**/
int
m_trie_remove_prefix(m_trie* trie, char* key, size_t len)
{
  node* root;
  node** arr;
  size_t i;
  int ret;

  if (trie == NULL)
    return M_TRIE_E_NULL;

  /* Select a root of a subtree to remove. */
  if (key == NULL && len == 0)
    root = (node*)trie->tr_root;
  else {
    ret = locate(trie, key, len, &root);
    if (ret != M_TRIE_OK)
      return ret;
  }

  /* Mark all nodes in the subtree for future removal. */
  arr = subtree(trie, root);
  for (i = 0; i < trie->tr_ncnt; i++) {
    arr[i]->nd_type = NODE_TO_FREE;
    arr[i]->nd_data = NULL;
  }
  free(arr);

  /* Optionally run the garbage-collection procedure. */
  if (trie->tr_flags & M_TRIE_CLEANUP)
    m_trie_trim(trie);

  return M_TRIE_OK;
}

/** Garbage-collect nodes that have only regular nodes as children.
  * Such state can arise after one or more calls to one of the
  * m_trie_remove and m_trie_remove_prefix functions.
  *
  * @param[in] trie trie
  *
  * @return status code
  * @retval M_TRIE_E_NULL trie is NULL
  * @retval M_TRIE_OK     success
**/
int
m_trie_trim(m_trie* trie)
{
  node** arr;
  int i;
  int k;

  if (trie == NULL)
    return M_TRIE_E_NULL;

  arr = subtree(trie, (node*)trie->tr_root);

  /* Traverse the nodes in the backwards-DFS order. This will ensure that a
   * node is processed before it's parent node. */
  for (i = trie->tr_ncnt-1; i != -1; i--) {

    /* Free all nodes marked to be freed. Applies to data nodes too. */
    if (arr[i]->nd_chld != NULL)
      for (k = 0; k < trie->tr_ccnt; k++)
        if (arr[i]->nd_chld[k] != NULL)
          if (arr[i]->nd_chld[k]->nd_type == NODE_TO_FREE) {
            node_free(trie, arr[i]->nd_chld[k]);
            arr[i]->nd_chld[k] = NULL;
          }

    /* Nodes that hold data can not be removed. */
    if (arr[i]->nd_type == NODE_DATA)
      continue;

    /* Mark node that has no valuable child nodes for removal. */
    if (arr[i]->nd_chld == NULL || all_null(trie, arr[i]))
      arr[i]->nd_type = NODE_TO_FREE;
  }

  /* Make sure that the root is not marked for removal. */
  ((node*)trie->tr_root)->nd_type = NODE_REGULAR;

  free(arr);

  return M_TRIE_OK;
}
