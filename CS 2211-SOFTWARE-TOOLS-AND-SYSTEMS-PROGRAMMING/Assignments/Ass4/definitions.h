// CS2211b 2023
// Assignment number 4
// Oren Arbel-Wood
// 251251876
// oarbelwo
// March 15, 2023

//structure definitions

typedef struct {
    char *cp;
    int size;
} word_struct;
typedef word_struct* word;

typedef struct {
    word *wp;
    int size;
} line_struct;
typedef line_struct* line;

typedef struct {
    line *lp;
    int size;
} para_struct;
typedef para_struct* para;

