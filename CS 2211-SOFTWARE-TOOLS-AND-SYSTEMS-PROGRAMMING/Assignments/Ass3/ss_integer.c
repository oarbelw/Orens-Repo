//CS2211b 2023
//Assignment 3
//Oren Arbel-Wood
//251251876
//oarbelwo
//February 26, 2023

//we are going to import our packages
#include <stdio.h>
#include <stdlib.h>

//compile the display function
void displaynum (char num[][3][3], int isneg, int len);

//this is a 3d array storing the 10 digits plus the negative symbol in the first 2d array spot
const char segements[11][3][3] = {
        {{ ' ', ' ', ' '}, { ' ', '_', ' '}, { ' ', ' ', ' '}}, //negative
        {{ ' ', '_', ' '}, { '|', ' ', '|'}, { '|', '_', '|'}}, //0
        {{ ' ', ' ', ' '}, { ' ', ' ', '|'}, { ' ', ' ', '|'}}, //1
        {{ ' ', '_', ' '}, { ' ', '_', '|'}, { '|', '_', ' '}}, //2
        {{ ' ', '_', ' '}, { ' ', '_', '|'}, { ' ', '_', '|'}}, //3
        {{ ' ', ' ', ' '}, { '|', '_', '|'}, { ' ', ' ', '|'}}, //4
        {{ ' ', '_', ' '}, { '|', '_', ' '}, { ' ', '_', '|'}}, //5
        {{ ' ', '_', ' '}, { '|', '_', ' '}, { '|', '_', '|'}}, //6
        {{ ' ', '_', ' '}, { ' ', ' ', '|'}, { ' ', ' ', '|'}}, //7
        {{ ' ', '_', ' '}, { '|', '_', '|'}, { '|', '_', '|'}}, //8
        {{ ' ', '_', ' '}, { '|', '_', '|'}, { ' ', '_', '|'}}, //9
    };

//takes in an array, a negative number indicator, and the length of the array
//it prints all the digits of the integer row by row
void displaynum (char num[][3][3], int isneg, int len) {//isneg = 1 if negative, 0 if positive
        if (isneg == 1) { //if it is negative, have to put top row of minus
		for (int val = 0; val < 3; val++) { 
                	printf("%c ", segements[0][0][val]); //prints top row of minus
		}
        }
	for (int i = 0; i < len; i++) { //prints top row of all numbers
                printf("%c", num[i][0][0]);
                printf("%c", num[i][0][1]);
                printf("%c ", num[i][0][2]);
        }
        printf("\n"); //goes to second line
	
	if (isneg == 1) { //prints middle row of minus
                for (int val = 0; val < 3; val++) {
                        printf("%c ", segements[0][1][val]);
                }
        }
        for (int i = 0; i < len; i++) { //prints middle row of numbers
                printf("%c", num[i][1][0]);
                printf("%c", num[i][1][1]);
                printf("%c ", num[i][1][2]);
        }
        printf("\n"); //goes to last line

	if (isneg == 1) {//prints bottom row of minus
                for (int val = 0; val < 3; val++) {
                        printf("%c ", segements[0][2][val]);
                }
        }
        for (int i = 0; i < len; i++) { //prints bottom row of numbers
                printf("%c", num[i][2][0]);
                printf("%c", num[i][2][1]);
                printf("%c ", num[i][2][2]);
        }
        printf("\n");
}

int main() {
        char opts = 'Y'; //to ask wether or not to repeat
        int inputint; //initiate the input integer
        while (opts == 'Y') { //while you want to repeat with Y
                printf("Please enter an integer:\n"); 
                scanf(" %d", &inputint); //stores user input in inputint
                int abs_int = abs(inputint); //gets absolute value of user input, so if there is a minus, disregards it
                int inp_len = 0; //used to track the length of the integer
		while(abs_int!=0) {//this is done to count length of integer
                    abs_int=abs_int/10; //keeps on dividing by 10, basically getting rid of a value, until it hits 0
                    inp_len++; //calculates length
                }

		abs_int = abs(inputint); //have to restate the absolute value as it was changed in while loop above
                if (abs_int == 0) {
                        inp_len = 1; //if the input is just 0, length is 1
                }
		int isneg = 0; //initiated as positive unless assigned otherwise
                int arr[inp_len]; //this will store each values in the integer
                if (inputint < 0) {
                        isneg=1; //if it is negative, trigger isneg to 1
                }

		int count = inp_len-1; //initiate the count to iterate through array backwards because it starts from right side and goes to left, when we need to it go from left ro right 
                
		if (abs_int == 0) {
                        arr[0] = 0;
                } //if input is just 0, only store 0
		
		while (abs_int > 0) {
                        arr[count] = abs_int % 10; //gets last value at end
                        abs_int /= 10; //drops its last element
                        count--; //decrease counter and keep going back until the first spot in array is full
                }

                char newseg[inp_len][3][3]; //this will store a 3d array of the corresponding 2d array of that element

		for (int num = 0; num < inp_len; num++) {
                        for (int row = 0; row < 3; row++) {
                            for (int col = 0; col < 3; col++) {
                                    newseg[num][row][col] = segements[arr[num]+1][row][col]; //stores in the new array the digit that corresponds to the element in the arr. +1 because to get number 9 in segements, you need to be at index 10.
                        }
                    }
                }

		displaynum((newseg), isneg, inp_len); //now, feed the newly made array, negative tracker, array length in function so it can print out each element of integer

                printf("\nWould you like to continue?\n Enter Y to continue inputting an integer, or\n Enter N to quit:\n");
                scanf(" %c", &opts); //if opts is not Y, while loop stops, program ends 
        }
        return 0;
}
