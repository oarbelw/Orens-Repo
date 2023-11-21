// CS2211b 2023
// Assignment number 4
// Oren Arbel-Wood
// 251251876
// oarbelwo
// March 15, 2023

#include "headers.h"

line line_ini(void) {//initiate line structure and create space for it, initially setting word pointer to null and size to 0, as the line is created empty
    line l;
    l = (line) malloc(sizeof(line_struct));
    l->wp = NULL;
    l->size = 0;
    return l;
}

void line_add(line l, word w) {//reallocates space created by word and word is initalized at the wordpointer, and copies w into worder pointer, and increases size
    l->wp = (word*) realloc(l->wp, sizeof(word) * (l->size + 1));
    l->wp[l->size] = word_ini();
    word_cp(l->wp[l->size], w);
    l->size++;
}

void line_cp(line ldest, line lsrc) { //copies line from lsrc to ldest by adding ldest to line
    int i;
    for (i=0; i<lsrc->size; i++) {
        line_add(ldest, lsrc->wp[i]);
    }
}


void line_print(line l) {
    for (int i = 0; i < l->size; i++) {
        if ((i+1) == (l->size)){ //dont want space at end if last word in line, so checks if this is last word in line
            word_print(l->wp[i]); 
        }
        else {
        word_print(l->wp[i]);
        printf(" ");//otherwise adds spaces between words
        }
    }
    printf("\n");//ends line with newline char
}

int line_search(line l, word w) {//searches for inputted w in l, returns index if found, -1 if not found
    for (int i = 0; i < l->size; i++) {
            if (word_cmp(l->wp[i], w) == 0) {
                return i;
            } 
        }
    return -1; //default to -1, -1 if not found
}

void line_reset(line l) { //resets line by freeing words and line and resetting pointers to null and 0 so we can start a line again
    for (int i = 0; i < l->size; i++) {
        word_free(l->wp[i]);
    }
    free(l->wp);
    l->wp = NULL;
    l->size = 0;
}

void line_free(line l) {//frees the memory when done, loops through every word and frees that word
    int i;
    for (i=0; i<l->size; i++) {
        word_free(l->wp[i]);
    }
    free(l);
}
