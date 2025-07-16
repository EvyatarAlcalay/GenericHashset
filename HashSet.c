
#include <stdlib.h>
#include "Node.h"
#include "HashSet.h"
#define NEW_HASH_TABLE 1
#define FAIL 0
#define SUCCESS 1
#define ERROR_EXIT -1
#define HASHING_AFTER_INCREASE 1
#define HASHING_AFTER_DECREASE 2


/**
 * this function is making quadratic probing
 * @param hashset the hash set where we want to insert the new element
 * @param attempt_num the current try we are now
 * @return matching to index via quadratic probing
 */
size_t quadratic_probing(size_t attempt_num){
    size_t index = (attempt_num+(attempt_num*attempt_num))/2;
    return index;
}

/**
 * this function is calculate the next index to try to make hashing
 * @param hash_set the hash set where we want to insert the new element
 * @param value the value i want to hash
 * @param attempt_num the current index we are now
 * @return the index we are looking for
 */
size_t my_index(HashSet *hash_set,Value value,size_t attempt_num){
    size_t my_index = (hash_set->hash_func(value) + quadratic_probing
            (attempt_num)) & (hash_set->capacity-1);
    return my_index;
}

/**
 * this function is hashing all the values in the old hash table to a new
 * one, according to the new size of the new table
 * @param hash_set the hash set we will hash from zero
 * @param operation this argument will determine the size of the new hash
 * table, hence if operation is INCREASE we will hash to bigger new hash
 * table and if the operation is DECREASE we will hash to smaller new hash
 * table.
 */
void new_hashing(HashSet *hash_set, int operation){
    Node ** temp_list = NULL;
    unsigned int old_capacity = hash_set->capacity;
    if (operation == HASHING_AFTER_INCREASE){
        size_t new_capacity = (hash_set->capacity)*HASH_SET_GROWTH_FACTOR;
        hash_set->capacity = new_capacity;
        temp_list =  malloc(sizeof(Node*)*new_capacity);
    }
    else{
        size_t new_capacity = (hash_set->capacity)/HASH_SET_GROWTH_FACTOR;
        hash_set->capacity = new_capacity;
        temp_list =  malloc(sizeof(Node*)*new_capacity);
    }
    for (size_t i=0;i<hash_set->capacity;i++){
        temp_list[i] =node_alloc(hash_set->value_cpy,
                                 hash_set->value_cmp,
                                 hash_set->value_free);
    }


    for (size_t j =0;j<old_capacity;j++){
        if ((hash_set->NodesList[j])->data != NULL){
            Value my_new_value = (hash_set->NodesList[j])->data;
            //im going to hash this value to the new hash table
            for (size_t k =0;k<(hash_set->capacity);k++){
                size_t new_index = my_index(hash_set, my_new_value,k);
                Node* new_current_node = temp_list[new_index];
                if (k==0){
                    new_current_node->hashCount ++;
                }
                if (new_current_node->data == NULL){
                    set_node_data(new_current_node,my_new_value);
                    break; //put the data just one time
                }
            }
        }
    }
    for (size_t m =0;m<old_capacity;m++){
        node_free(&(hash_set->NodesList[m]));
    }
    free(hash_set->NodesList);
    hash_set->NodesList = temp_list;
}

/**
 * Allocates dynamically new hash set.
 * @param hash_func a function which "hashes" keys.
 * @param value_cpy a function which copies Values.
 * @param value_cmp a function which compares Values.
 * @param value_free a function which frees Values.
 * @return pointer to dynamically allocated HashSet.
 * @if_fail return NULL or if one of the function pointers is null.
 */
HashSet *hash_set_alloc(
        HashFunc hash_func, HashSetValueCpy value_cpy,
        HashSetValueCmp value_cmp, HashSetValueFree value_free){

    if (hash_func == NULL || value_cpy == NULL || value_cmp == NULL ||
        value_free == NULL){
        return NULL;
    }
    HashSet *my_hash_table = calloc(NEW_HASH_TABLE,sizeof(HashSet));
    my_hash_table -> hash_func = hash_func;
    my_hash_table -> value_cpy = value_cpy;
    my_hash_table -> value_cmp = value_cmp;
    my_hash_table -> value_free = value_free;
    my_hash_table -> capacity = HASH_SET_INITIAL_CAP;
    my_hash_table ->NodesList = malloc(HASH_SET_INITIAL_CAP*sizeof(Node*));
    for (size_t i =0;i<HASH_SET_INITIAL_CAP;i++){
        my_hash_table->NodesList[i] = node_alloc(value_cpy,value_cmp,
                                                 value_free);
    }
    return my_hash_table;
}

/**
 * Frees the hash set and all its elements.
 * @param p_hash_set pointer to pointer to a hash_set.
 */
void hash_set_free(HashSet **p_hash_set){
    if (p_hash_set == NULL || (*p_hash_set) == NULL){
        return;
    }
    for(size_t i =0;i<((*p_hash_set)->capacity);i++){
        node_free((&((*p_hash_set)->NodesList[i])));
    }
    free((*p_hash_set)->NodesList);
    free(*p_hash_set);
    *p_hash_set = NULL;
    p_hash_set = NULL;
}

/**
 * Inserts a new Value to the hash set.
 * The function inserts *new*, *copied*, *dynamically allocated* Value,
 * @param hash_set the hash set where we want to insert the new element
 * @param value a Value we would like to add to the hashset
 * @return returns 1 for successful insertion, 0 otherwise.
 */
int hash_set_insert(HashSet *hash_set, Value value){
    if (hash_set == NULL || value == NULL || hash_set->hash_func == NULL ||
        hash_set->value_cpy == NULL || hash_set->value_cmp == NULL ||
        hash_set->value_free == NULL){
        return FAIL;
    }
    if (hash_set_contains_value(hash_set,value) == SUCCESS){
        //check if the data we want to add is already exist
        return FAIL;
    }
    //just now, I will insert the value (which be allocated)
    for (size_t i =0;i<hash_set->capacity;i++){
        size_t ind = my_index(hash_set,value,i);
        Node* current_node = (hash_set->NodesList[ind]);
        if (i==0){
            current_node->hashCount ++; //update the
            // hash count to be one more just in the first attempt
        }
        if (current_node->data == NULL){
            set_node_data(current_node,value);
            hash_set->size ++;
            if (hash_set_get_load_factor(hash_set)>=HASH_SET_MAX_LOAD_FACTOR){
                //we will make hashing from zero to a new big hash table
                new_hashing(hash_set,HASHING_AFTER_INCREASE);
            }
            break;
        }
    }
    return SUCCESS;
}

/**
 * The function checks if the given value exists in the hash set.
 * @param hash_set a hash set.
 * @param value the value to be checked.
 * @return 1 if the value is in the hash set, 0 otherwise.
 */
int hash_set_contains_value(HashSet *hash_set, Value value){
    if (hash_set == NULL || value == NULL){
        return FAIL;
    }
    for (size_t i =0;i<hash_set->capacity;i++){
        if(check_node(hash_set->NodesList[i],value) == SUCCESS){
            return SUCCESS;
        }
    }
    return FAIL;
}

/**
 * The function erases a Value.
 * @param hash_set a hash set.
 * @param value the value to be erased from the hashtable
 * @return 1 if the erasing was done successfully, 0 otherwise.
 */
int hash_set_erase(HashSet *hash_set, Value value){
    if (hash_set == NULL || value == NULL){
        return FAIL;
    }
    if (hash_set_contains_value(hash_set,value) == FAIL){
        //check if the value is located in the hash table
        return FAIL;
    }
    if (hash_set->hash_func == NULL){
        return FAIL;
    }
    for (size_t i =0;i<hash_set->capacity;i++){
        if (check_node(hash_set->NodesList[i],value) == SUCCESS){
            clear_node(hash_set->NodesList[i]);
            size_t index_to_erase = (hash_set->hash_func(value))
                                    & (hash_set->capacity-1);
            hash_set->NodesList[index_to_erase]->hashCount --;
            hash_set->size --;
            if (hash_set_get_load_factor(hash_set)<=HASH_SET_MIN_LOAD_FACTOR){
                new_hashing(hash_set,HASHING_AFTER_DECREASE);
            }
            break;
        }
    }
    return SUCCESS;
}

/**
 * This function returns the load factor of the hash set.
 * @param hash_set a hash set.
 * @return the hash set's load factor, -1 if the function failed.
 */
double hash_set_get_load_factor(HashSet *hash_set){
    if (hash_set == NULL){
        return ERROR_EXIT;
    }
    double load_factor = (double)(hash_set->size)/(hash_set->capacity);
    return load_factor;
}

/**
 * This function deletes all the values in the hash set.
 * @param hash_set a hash set to be cleared.
 */
void hash_set_clear(HashSet *hash_set){
    if (hash_set == NULL){
        return;
    }
    for(size_t i =0;i<hash_set->capacity;i++){
        if((hash_set->NodesList[i])->data != NULL){
            clear_node(hash_set->NodesList[i]);
            hash_set->NodesList[i]->hashCount = 0;
            hash_set->size --;
        }
    }
}

/**
 * This function gets the element in the hashset hashed to the indexed value
 * @param hash_set the hashset
 * @param value the index of the node in the hashtable that we would like to
 * have its value
 * @return the element in the hashset hashed to the indexed value
 * NULL in case of an error or an empty node or an unexpected value
 */
Value hash_set_at(HashSet *hash_set, int value){
    if (hash_set == NULL || value >= (int)hash_set->capacity || value <0 ||
        hash_set->NodesList == NULL || hash_set->NodesList[value] == NULL){
        return NULL;
    }
    return (hash_set->NodesList[value])->data;
}
