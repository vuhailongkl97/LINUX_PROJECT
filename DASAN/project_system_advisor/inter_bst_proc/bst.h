#ifndef _BST_H_
#define _BST_H_

#include "my_data.h"

node* create_node(type_data );
/*
    insert a new node into the BST
*/
node* insert_node(node *, comparer , type_data );
/*
    delete a node in the binary search tree
*/
node* delete_node(node* , type_data ,comparer );
/*
    search for a specific key
*/
node* search(node *, type_data ,comparer );
/*
    in order traversal the binary search tree
*/
void traverse(node *root,callback cb);
/*
    recursively remove all nodes of the tree
*/
void dispose(node* );
/*
    Recursively display tree or subtree
*/
void display_tree(node* nd);

void traverse_tree(node *root, int *n, int *arr);

#endif


