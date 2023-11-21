// CS2211b 2023
// Assignment number 5
// Oren Arbel-Wood
// 251251876
// oarbelwo
// April 5, 2023

#include "headers.h"

int main() {
    Matrix m = matrix_construction(); //initialize matrix
    //allocate memory for both indexes
    Index index1 = (Index)malloc(sizeof(Index)); 
    Index index2 = (Index)malloc(sizeof(Index));
    int result;
    while ( (result = scanf("%s %s", index1, index2)) == 2 ) { //while we keep on scanning for input, making sure input size is 2  
        if (result == EOF) {//eof triggered by ctrl+d or end of file
            break; // exit the loop on end-of-file
        }
        if (matrix_index_in(m, index1, index2) == 1) { //if the strings are already in the matrix
            Value v = matrix_get(m, index1, index2); //get the value already assigned to those indexes
            matrix_set(m, index1, index2, v+1); //add 1 to the occurance of value v
        } else { //if the strings arent in the matrix yet
            matrix_set(m, index1, index2, 1); //add to matrix and set value to 1 as it is the first occurance
        }
    }
    //free space allocated
    free(index1);
    free(index2);
    matrix_list(m); //list contents of matrix
    matrix_destruction(m); //free space and collapse matrix
    return 0;
}
