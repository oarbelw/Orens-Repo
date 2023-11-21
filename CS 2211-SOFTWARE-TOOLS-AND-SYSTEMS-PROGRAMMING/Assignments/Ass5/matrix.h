// CS2211b 2023
// Assignment number 5
// Oren Arbel-Wood
// 251251876
// oarbelwo
// April 5, 2023

typedef BStree Matrix;
typedef char* Index;
typedef int Value;

Matrix matrix_construction(void);
unsigned char matrix_index_in(Matrix m, Index index1, Index index2);
Value matrix_get(Matrix m, Index index1, Index index2);
void matrix_set(Matrix m, Index index1, Index index2, Value value);
void matrix_list(Matrix m);
void matrix_destruction(Matrix m);