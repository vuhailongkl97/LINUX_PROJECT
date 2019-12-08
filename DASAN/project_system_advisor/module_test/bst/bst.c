#include "bst.h"

node* create_node(type_data data)
{
    node *new_node = (node*)malloc(sizeof(node));
    if(new_node == NULL)
    {
        fprintf (stderr, "Out of memory!!! (create_node)\n");
        exit(1);
    }
    enter_data(&(new_node->data), data);
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node* insert_node(node *root, comparer compare, type_data data)
{
 
    if(root == NULL)
    {
        root = create_node(data);
    }
    else
    {
        int is_left  = 0;
        int r        = 0;
        node* cursor = root;
        node* prev   = NULL;
 
        while(cursor != NULL)
        {
            r = compare(data,cursor->data);
            prev = cursor;
            if(r < 0)
            {
                is_left = 1;
                cursor = cursor->left;
            }
            else if(r > 0)
            {
                is_left = 0;
                cursor = cursor->right;
            }
 
        }
        if(is_left)
            prev->left = create_node(data);
        else
            prev->right = create_node(data);
 
    }
    return root;
}

node* delete_node(node* root, type_data data,comparer compare)
{
    if(root == NULL)
        return NULL;
 
    node *cursor;
    int r = compare(data,root->data);
    if( r < 0)
        root->left = delete_node( root->left, data,compare);
    else if( r > 0 )
        root->right = delete_node(root->right,data,compare);
    else
    {
        if (root->left == NULL)
        {
            cursor = root->right;
            free(root);
            root = cursor;
        }
        else if (root->right == NULL)
        {
            cursor = root->left;
            free(root);
            root = cursor;
        }
        else    //2 children
        {
            cursor = root->right;
            node *parent = NULL;
 
            while(cursor->left != NULL)
            {
                parent = cursor;
                cursor = cursor->left;
            }
            root->data = cursor->data;
            if (parent != NULL)
                parent->left = delete_node(parent->left, parent->left->data,compare);
            else
                root->right = delete_node(root->right, root->right->data,compare);
        }
    }
    return root;
}
node* search(node *root,type_data  data,comparer compare)
{
    if(root == NULL)
        return NULL;
 
    int r;
    node* cursor = root;
    while(cursor != NULL)
    {
        r = compare(data,cursor->data);
        if(r < 0)
            cursor = cursor->left;
        else if(r > 0)
            cursor = cursor->right;
        else
            return cursor;
    }
    return cursor;
 
}

void traverse(node *root,callback cb)
{
    node *cursor, *pre;
 
    if(root == NULL)
        return;
 
    cursor = root;
 
    while(cursor != NULL)
    {
        if(cursor->left != NULL)
        {
            cb(cursor);
            cursor = cursor->right;
        }
        else
        {
            pre = cursor->left;
 
            while(pre->right != NULL && pre->right != cursor)
                pre = pre->right;
 
            if (pre->right != NULL)
            {
                pre->right = cursor;
                cursor = cursor->left;
            }
            else
            {
                pre->right = NULL;
                cb(cursor);
                cursor = cursor->right;
            }
        }
    }
}
void dispose(node* root)
{
    if(root != NULL)
    {
        dispose(root->left);
        dispose(root->right);
        free(root);
    }
}



void display_tree(node* nd)
{
    if (nd == NULL)
        return;
    display(nd);
    display_tree(nd->left);
    display_tree(nd->right);

}
