// CS2211b 2023
// Assignment number 5
// Oren Arbel-Wood
// 251251876
// oarbelwo
// April 5, 2023

#include "headers.h"

// Allocate memory of type BStree node*, set the value to NULL, and return a pointer to the allocated memory.
BStree bstree_ini(void) {
    BStree bst;
    bst = (BStree) malloc(sizeof(BStree_node));
    *bst = NULL;
    return bst;
}

// Insert data with key into bst. If key is in bst, then do nothing
void bstree_insert(BStree bst, Key key, Data data) {
    if (*bst == NULL) {
        *bst = new_node(key, data); //we call helper function new_node to create a new node if bst pointer isnt pointing to any nodes
    } else {
        int cmp = key_comp(key, (*bst)->key); 
        if (cmp < 0) { //if it is less than 0, we travel into the left node
            bstree_insert(&(*bst)->left, key, data);
        } else if (cmp > 0) { //if it is more than 0, we travel into the right node
            bstree_insert(&(*bst)->right, key, data);
        } else { //cmp==0, so if it is already in bstree
            (*bst)->data = data; //then we reaffirm that the data is set the same, this doesnt really do anything
        }
    }
}

// Helper function for insertion to create a pointer to a tree node from key and data.
BStree_node *new_node(Key key, Data data){
    BStree_node *node = (BStree_node *) malloc(sizeof(BStree_node));
    node->key = key;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// If key is in bst, return key’s associated data. If key is not in bst, return NULL.
Data bstree_search(BStree bst, Key key) {
    if ((*bst) == NULL) return NULL; //if the bst is null return null
    int cmp = key_comp(key, (*bst)->key);
    if (cmp == 0) {
        return (*bst)->data; //if it is in data, return the data
    } else if (cmp < 0) {
        return bstree_search(&(*bst)->left, key); //traverse left side until it is found
    } else if (cmp > 0) {
        return bstree_search(&(*bst)->right, key); //traverse right side until it is found
    } else {
        return NULL; //if it is not in bst, return null
    }
}

// In order traversal of bst and print each node’s key and data.
void bstree_traverse(BStree bst) {
    if (*bst != NULL) {
        bstree_traverse(&(*bst)->left); //inorder traversal starts looking at left
        key_print((*bst)->key);
        printf(" "); //need this to align data with keys
        data_print((*bst)->data);
        printf("\n");
        bstree_traverse(&(*bst)->right); //inorder lastly checks right last
    }
}

// Free all the dynamically allocated memory of bst.
void bstree_free(BStree bst){
    if (*bst != NULL) {
        bstree_free(&(*bst)->left);
        bstree_free(&(*bst)->right);
        free(*bst);
        *bst = NULL;
    }
}