// Assignment number 4
// Oren Arbel-Wood
// 251251876
// oarbelwo
// March 15, 2023

#include "headers.h"

int main(void) {
    //initialize the 3 structures to allocate spacy dynamically
    word w=word_ini();
    line l=line_ini();
    para p=para_ini();
    while (1) {//while loop to keep on getting new lines from user
        word w=word_ini();
        int c = getchar(), i = 0; //c gets character from user, i tracks to see if first character looked at is the newline char
        while (2) {//while looping through characters
            if ((i == 0) && (c=='\n')) {//the new line is just a new line character
                goto endloop; //double break
            }
            else if (c=='\n') { //if we have hit the end of the line
                word_add_null(w); //since it is the last word of line and end of word, add the null character to end
                line_add(l, w);//add the last word
                para_add(p,l); //add this completed line to the paragraph
                line_reset(l); //reset and clear line so we can look at next line
                break;// breaks out of inner while loop
            }
            else if (!isspace(c)) { //if the character is not whitespace, add it to the current word
                word_add(w,c); //add the character to the word to create string of characters
            }
            else if (w->size > 0) { // if the character is whitespace and a word has been started, add the word to the line
                word_add_null(w); //since it is the last word of line and end of word, add the null character to end
                line_add(l, w); //add the word to the line
                w = word_ini(); // reset the current word
            }
            c = getchar(); //keep on getting next character
            i++; //increase counter so that it knows to not add 
        }
    }
    endloop:
    para_print(p); //print each line and word in the order they were entered

    //prompt the user for a word to search for and report the results
    printf("enter a word to search paragraph for: ");

    while(3) {//repeating until only a newline input is entered
        int j = 0,c = getchar();
        word w=word_ini();
        while (4){ //creates the word
            if ((j == 0) && (c=='\n')) { //if it is only a newline input
                goto done;
            }
            else if (c=='\n'){ //if we are at the end of the line the user entered
                word_add_null(w); //since it is the last word of line and end of word, add the null character to end
                int found = para_search_print(p,w); //automatically prints if it is found and where
                if (found == 0) {//if it wasnt found
                    puts("the word you entered was not found");
                }
                break; //break to get next word from user
            }
            else if (!isspace(c)) { //if the character is not whitespace, add it to the current word
                word_add(w,c); //add the character to the word to create string of characters
            }
            c = getchar(); //keep on getting next char from user
            j++;
        }
    }
    
    done:
    //free the memory
    word_free(w);
    line_free(l);
    para_free(p);

    return 0;
    } 

