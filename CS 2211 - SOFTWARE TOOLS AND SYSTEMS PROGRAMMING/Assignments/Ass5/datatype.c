// CS2211b 2023
// Assignment number 5
// Oren Arbel-Wood
// 251251876
// oarbelwo
// April 5, 2023

#include "headers.h"

//Create and initialize a key with dynamic memory allocation.
Key key_ini(void) {
    Key key;
    key = (Key) malloc(sizeof(Key_struct));
    key-> str1 = NULL;
    key-> str2 = NULL;
    return key;
}

//Set, i.e. copy string, key->str1 and key->str2 with str1 and str2.
void key_set(Key key, char *str1, char *str2) {
    key->str1 = string_dup(str1); //we call helper function string_dup to do this
    key->str2 = string_dup(str2);
}

// If key1->str1 and key2->str1 are different, then they determine the comparison result. 
// If key1->str1 and key2->str1 are the same, then key1->str2 and key2->str2 determine the comparison result.
int key_comp(Key key1, Key key2){
    int cmp1 = strcmp(key1->str1, key2->str1);
    if (cmp1 != 0) { //if they are different
        return cmp1; //then they determine comparison result so return it
    }
    else { //if above is the same, use below to detrmine result
        int cmp2 = strcmp(key1->str2, key2->str2);
        return cmp2;
    }
}

// Print a key.
void key_print(Key key) {
    printf("%-11s %-11s", key->str1, key->str2); //-11s so we can make it left aligned and maintain organized structure
}

// Free memory allocated for key.
void key_free(Key key) {
    free(key->str1);
    free(key->str2);
    free(key);
}

// Duplicate string pointed to by str with dynamic memory allocation.
char * string_dup(char *str){
    char *str_dup = (char*) malloc((strlen(str) + 1) * sizeof(char)); //allocate memory by using inputted str
    strcpy(str_dup, str); //copy inputted str into str_dup
    return str_dup;
}

// Create and initialize a data with dynamic memory allocation.
Data data_ini(void) {
    Data data;
    data = malloc(sizeof(int));
    *data = 0;
    return data;
}

// Assign value of data with intdata.
void data_set(Data data, int intdata) {
    *data = intdata;
}

// Print a data.
void data_print(Data data) {
    printf("%-11d", *data); //again, to maintain structure we do this formatting
}

// Free memory allocated for data.
void data_free(Data data) {
    free(data);
}