// CS2211b 2023
// Assignment number 4
// Oren Arbel-Wood
// 251251876
// oarbelwo
// March 15, 2023

#include "headers.h"

word word_ini(void) {//initiate line structure and create space for it, initially setting char pointer to null and size to 0, as the word is created empty
    word w;
    w = (word) malloc(sizeof(word_struct));
    w->cp = NULL;
    w->size = 0;
    return w;
}

void word_str_cp(word w, char* str) { //creates a word structure out of a string (used for testing)
    if (w->cp != NULL) free(w->cp); //frees the character pointer if its not already null
    w->size = strlen(str) + 1; //the size of the word is just the length of the string + 1
    w->cp = (char*) malloc(sizeof(char) * w->size); //the character pointer is created, dynamically creating space for character
    strncpy(w->cp, str, w->size); //copies this inputted string into the character pointer
}

void word_cp(word wdest, word wsrc) { //copies word from wsrc to wdest by adding wdest to word and updated its size
    wdest->cp = (char*) realloc(wdest->cp, (wsrc->size+1)*sizeof(char));
    strcpy(wdest->cp, wsrc->cp);
    wdest->size = wsrc->size;
}

void word_add(word w, char c) {
    w->cp = realloc(w->cp, (w->size+1) * sizeof(char)); //resize the allocated memory as characters are added
    w->cp[w->size] = c; //the character of the word at the end of the word is the character
    w->size++; //increase size
}

void word_add_null(word w) {
    w->cp = realloc(w->cp, (w->size+1) * sizeof(char)); //resize the allocated memory as characters are added
    w->cp[w->size] = '\0'; //add the null character to the end of the word
    w->size++; //increase size
}

int word_cmp(word w1, word w2) { 
    return strcmp(w1->cp, w2->cp); //returns 0 if equal, -1 if w1<w2, 1 if w1>w2
}

void word_print(word w) {
    printf("%s", w->cp);//prints the word pointed to by character pointer
}

void word_free(word wd) {//frees the memory created by word
    if (wd->cp != NULL) free(wd->cp);
    free(wd);
}
