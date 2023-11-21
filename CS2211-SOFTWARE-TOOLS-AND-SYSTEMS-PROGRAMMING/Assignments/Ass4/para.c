// CS2211b 2023
// Assignment number 4
// Oren Arbel-Wood
// 251251876
// oarbelwo
// March 15, 2023

#include "headers.h"

para para_ini(void) {//initiate para structure and create space for it, initially setting line pointer to null and size to 0, as the paragraph is created empty
    para p;
    p = (para) malloc(sizeof(para_struct));
    p->lp = NULL;
    p->size=0;
    return p;
}

void para_add(para p, line l) { 
    p->lp = (line*) realloc(p->lp, sizeof(line) * (p->size + 1));//reallocates the space created by line to have line pointer point to this line
    p->lp[p->size] = line_ini(); //adds a spot for the line to be added
    line_cp(p->lp[p->size], l); //copies the inputted line into this spot
    p->size++; //as a new line is added, increase the paragraph size by 1
}

void para_print(para p){
    for (int i = 0; i < p->size; i++) {//i is index of line pointer, so i is how many lines there are
        line_print(p->lp[i]); //print the line at the index i
    }
}

int para_search_print(para p, word w){
    int k,found = 0;
    for (int i = 0; i < p->size; i++) { //for line in paragraph
        k = line_search(p->lp[i], w); //searches for the inputted word in the line
        if (k == -1){ 
            continue; //if the word is not in this line, continue
        } 
        else { //word was found
            printf("Word found at line %d at word %d\n", i+1, k+1);
            found = 1;
        }
    }
    return found; //1 if found, 0 if not
}

void para_free(para p) { //frees the memory when done, loops through every line and frees that line
    int i;
    for (i=0; i<p->size; i++) {
        line_free(p->lp[i]);
    }
    free(p);
}

