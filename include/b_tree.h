/*
 * B Tree Operations
 * By: Liam P. Walsh
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct tree_node_ tree_node;
typedef struct tree_node_group_ tree_node_group;
typedef struct tree_ tree;

// Declares tree node struct.
struct tree_node_ {
  // Data of tree node
  int number;
  // Pointer to nodes
  tree_node_group * group;
};

// Declares tree struct. (hold root)
struct tree_node_group_ {
  // The root node of the tree
  tree_node * left;
  tree_node * right;
  tree_node_group * left_child;
  tree_node_group * middle_child;
  tree_node_group * right_child;
  tree_node_group * parent_group;
};

// Declares tree struct. (hold root)
struct tree_ {
  // The root node of the tree
  tree_node_group * root;
};

// Allocates node with the given data, and returns address.
tree_node * create_node(int number);

// Allocates node with the given data, and returns address.
tree_node_group * create_node_group();

// Allocates tree with the given root, and returns address.
tree * create_list();

// Recursively frees nodes called by the node pointer.
void free_node(tree_node * node);

// Recursively frees nodes called by the node pointer.
void free_node_group(tree_node_group * group);

// Frees nodes and sets head to NULL.
int empty_list(tree * list);

// Finds and returns first instance of a node with given key.
tree_node * search_tree(tree * list, int key);

// Parses tree for largest and smallest nodes
void print_small_large_tree(tree * list);

// Parses list and prints node data.
void print_sub_tree(tree_node_group * group);

// Parses list and prints node data.
void print_tree(tree * list);

// Counts the furthest level of child nodes.
int count_level(tree_node_group * root);

// Append node to front of list. (Replaces head node)
int append_node(tree_node * new_node, tree * list);

/* Balance not implemented yet.
// Swap/Rotate nodes
tree_node * swap_node(tree_node * root, int left);

// Recursively balances nodes by checking the node's left and right levels.
void balance_sub_tree(tree_node * parent, tree_node * node, int left_node);

// Balances tree by calling balance_sub_tree, and swap_node.
void balance_tree(tree * list);
*/

/* Remove node (Similar to swap/rotate)
void remove_node(tree * list, tree_node * root);
*/