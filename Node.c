//
// Created by evy18 on 22/11/2021.
//

#include <stdlib.h>
#include "Node.h"
#define NEW_NODE 1
#define SUCCESS 1
#define FAIL 0
#define ERROR_EXIT -1

/**
 * Allocates dynamically new Node element.
 * @param elem_copy_func func which copies the element stored in the Node
 * (returns dynamically allocated copy).
 * @param elem_cmp_func func which is used to compare elements stored in the
 * Node.
 * @param elem_free_func func which frees elements stored in the Node.
 * @return pointer to dynamically allocated Node.
 * @if_fail return NULL (it returns null also if one of the
 * function pointers is null).
 * You can assume memory allocation success
 */
Node *node_alloc(NodeElemCpy elem_copy_func, NodeElemCmp elem_cmp_func,
                 NodeElemFree elem_free_func){
    if (elem_copy_func == NULL || elem_cmp_func == NULL || elem_free_func ==
            NULL){
        return NULL;
    }
    Node * my_node = calloc(NEW_NODE,sizeof(Node));
    my_node->elem_copy_func = elem_copy_func;
    my_node->elem_cmp_func = elem_cmp_func;
    my_node->elem_free_func = elem_free_func;
    return my_node;
}

/**
 * Frees a Node and the elements the Node itself allocated.
 * @param p_Node pointer to dynamically allocated pointer to Node.
 */
void node_free(Node **p_Node){
    if (p_Node == NULL || (*p_Node) == NULL || (*p_Node)->elem_free_func ==
    NULL){
        return;
    }
    if (((*p_Node)->data) != NULL){
        (*p_Node)->elem_free_func(&((*p_Node)->data));
    }
    free(*p_Node);
    (*p_Node) = NULL;
}

/**
 * Gets a value and checks if the value is in the Node.
 * @param Node a pointer to Node.
 * @param value the value to look for.
 * @return 1 if the value is in the Node, 0 if no such value in the Node.
 * Returns -1  if something went wrong during the check
 * You cannot assume anything about the input.
 */
int check_node(Node *node, void *value){
    if (node == NULL || value == NULL || node->elem_cmp_func == NULL){
        return ERROR_EXIT;
    }
    if (node->data == NULL || node->elem_cmp_func(node->data,value) == 0){
        return FAIL;
    }
    return SUCCESS;
}

/**
 * Adds a new value to the data of the Node.
 * @param Node a pointer to Node.
 * @param value the value to be added to the Node.
 * @return 1 if the adding has been done successfully, 0 otherwise.
 */
int set_node_data(Node *node, void *value){
    if (node == NULL  || value == NULL || node->elem_copy_func == NULL ||
    node->elem_free_func == NULL){
        return FAIL;
    }
    if (node->data != NULL){
        clear_node(node);
    }
    void * my_value = node->elem_copy_func(value);
    node->data = my_value;
    return SUCCESS;
}

/**
 * Deletes the data in the Node.
 * @param Node Node a pointer to Node.
 */
void clear_node(Node *node){
    if (node == NULL || node->elem_free_func == NULL){
        return;
    }
    node->elem_free_func(&(node->data));
    node->data = NULL;
}

/**
 * Gets the number of data values in the hashtable that would have been hashed
 * to this node
 * @param node The current node
 * @return the number of data in the hashtable that would have been hashed
 * to this node or -1 in case of illegal input;
 * You cannot assume anything about the input.
 */
int get_hash_count(Node *node){
    if (node == NULL){
        return ERROR_EXIT;
    }
    return node->hashCount;
}

