#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


node_t    *allocnode()
{
  node_t *current;
 
  current = (node_t *)malloc(sizeof(node_t));
  current -> left = current -> right = NULL;
  return current;
}


node_t    *insert(node_t *root, char *key, void *data)
{
  if(root == NULL)
  {
    root = allocnode();
    root -> key = key;
    root -> data = data;
  }

  if(key > root -> key) 
    root -> left =  insert(root -> left, key, data);
  
  else if(key < root -> key)  
    root -> right = insert(root -> right, key, data);
return root;
}

void    print_node(node_t *node)
{
  if(!node) 
    return;
  else 
    printf(node -> data);

}
void    visit_tree(node_t *node, void (*fp)(node_t *root))
{
  fp(node);

  if(node->right) 
    visit_tree(node->right, fp);

  else if(node->left)  
    visit_tree(node->left, fp);
}

void    destroy_tree(node_t *node, void (*fdestroy)(node_t *root))
{
  if(node->right) 
    destroy_tree(node->right, fdestroy);

  else if(node->left) 
    destroy_tree(node->left, fdestroy);

  fdestroy(node);
  free(node);
  node = NULL;
}


