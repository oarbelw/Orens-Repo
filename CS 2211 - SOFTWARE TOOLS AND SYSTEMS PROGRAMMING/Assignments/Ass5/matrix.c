// CS2211b 2023
// Assignment number 5
// Oren Arbel-Wood
// 251251876
// oarbelwo
// April 5, 2023

#include "headers.h"

// Matrix construction using bstree ini();
Matrix matrix_construction(void) {
    BStree m = bstree_ini();
    return m;
}

// If location (index1, index2) is defined in Matrix m, then return 1. Otherwise, return 0.
unsigned char matrix_index_in(Matrix m, Index index1, Index index2){
    Key key = key_ini();
    key_set(key, index1, index2); //initializes key and puts the indexes in the key
    Data result = bstree_search(m, key); //check to see if key is in bstree_search
    key_free(key);
    if (result != NULL) { //if it is in in matrix m, meaning it isnt NULL, return 1
        return 1;
    } else {
        return 0; //otherwise return 0
    }
}

// If location (index1, index2) is defined in Matrix m, then return the associated value. Otherwise, report error and return -1
Value matrix_get(Matrix m, Index index1, Index index2) {
    unsigned char ch = matrix_index_in(m, index1, index2);
    if (ch == 1) { //if the indexes are in the matrix
        Key key = key_ini();
        key_set(key, index1, index2);
        Data result = bstree_search(m, key);
        Value v = *result; //assign the value to value v
        key_free(key);
        return v;
    }
    printf("Error, tried to get value of not found indexes in matrix.\n");
    return -1; //otherwise return -1
}

// Assign value to Matrix m at location (index1, index2). If that location already has value, then overwrite
void matrix_set(Matrix m, Index index1, Index index2, Value value) {
    unsigned char ch = matrix_index_in(m, index1, index2);
    Key key = key_ini();
    key_set(key, index1, index2);
    if (ch == 1) { //if it is in the matrix m
        Data data = bstree_search(m, key); //get the data its associated with
        data_set(data, value); //overwrite the data with Value value
        key_free(key);
        return;
    }
    else { //otherwise, need to assign its value
        Data d = data_ini();
        data_set(d, value); //initialize data and set value as data
        bstree_insert(m, key, d); //then, insert the key and data into the matrix
    }    
}

// Print indices and values in the Matrix m (with bstree traverse()).
void matrix_list(Matrix m) {
    //titles for the output
    char txt1[] = "String 1";
    char txt2[] = "String 2";
    char txt3[] = "Occurrence";
    printf("%-11s %-11s %-11s\n",txt1 , txt2, txt3); //- means left align
    bstree_traverse(m);
}

// Free allocated space (with bstree free()).
void matrix_destruction(Matrix m) {
    bstree_free(m);
}