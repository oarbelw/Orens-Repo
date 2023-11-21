//CS2211b 2023
//Assignment 3
//Oren Arbel-Wood
//251251876
//oarbelwo
//February 24, 2023

//lets import the necessary packages, math.h for fmod for modulo with float, stdlib.h for error, bool for the while loop, and ctype.h to determine if any letters would be in here to state an error
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//compile functions
char get_op(void);
float get_num(void);
float md_exp(void);
float md_sub_exp(float sub_exp);
float sim_sub_exp(float sub_exp);
float sim_exp(void);

int main() {
	char on; //initiate to repeat loop
	bool repeat = true; //initiate to true to repeat
	while (repeat == true) {
		printf("Simple Arithmetic Expression Calculator: Enter an expression\n");
		float result = sim_exp(); //begins recursive cycle, returns result
        	printf("Result: %f\n", result);
        	printf("Would you like to continue?\n");
        	printf("Enter Y to continue inputting a simple arithmetic expression, or enter N to quit\n");
        	scanf(" %c", &on);
        	if (on == 'Y'); //state Y will be to continue
        	else if (on == 'N') { //otherwise, terminate program by setting while loop off
			printf("Goodbye\n");
            		repeat = false;
        	}
		else { //if it is anything besides Y or N,
            		printf("Error: Entered a value that is not Y or N!\n");
            		exit(EXIT_FAILURE);
        	}
    	}
	return 0;
}

// Input: none, read from stdin
// Effect: get the next operator of the expression
// this operator can be +, -, *, /, or ’\n’
// ’\n’ indicates the end of the expression input
// leading spaces should skipped
// Output: return the next operator of the expression.
char get_op(void) {
	char c;
	while ((c = getchar()) == ' '); //shifts through spaces
	if (isalpha(c)) { //if a letter is somehow in equation, trigger error
		printf("Error: invalid input, please enter valid numbers only!\n");
            	exit(EXIT_FAILURE);
	}
	else if (c != '+' && c != '-' && c != '*' && c != '/' && c != '%' && c != '\n') {
		ungetc(c, stdin); //if it is none of the operators, unget to find operators
        	return ' ';
    	}
    return c;
}


// Input: none, read from stdin
// Effect: get the next numeric value of the expression
// Output: return the next numeric value of the expression.
float get_num(void) {
	float num;
	scanf("%f", &num);
	return num;
}

// Input: ’sub_exp’: the value of the current sub sim_expression
// to the left of the next operator, ’next_op’,
// located at the beginning of current stdin.
// ’next_op’: an operator, ’+’ or ’-’. ’next_op’
// could also be ’\n’ indicating the end
// of the sim_expression.
// the rest of the sim_expression will be read in
// from stdin
// Effect: the sim_expression is evaluated using recursion:
// get ’next_op’ with get_op()
// if ’next_op’ is ’\n’
// push back ’next_op’ to stdin
// return ’sub_exp’
// else (’next_op’ is ’+’ or ’-’)
// get ’next_md_exp’ with md_exp()
// use ’sub_exp next_op next_md_exp’ to do recursive call
// i.e. call sim_sub_exp()
// end if
// Output: this function returns the value of the current sim_expression
float sim_sub_exp(float sub_exp) {
	char next_op = get_op();
	if (next_op == '\n') {
		ungetc(next_op, stdin);
		return sub_exp;
	}
	else {//as in next_op is + or -
		float next_md_exp = md_exp();
		float next_sub_exp;
		if (next_op == '+') {//basic addition
			next_sub_exp = sub_exp + next_md_exp;
		}
		else if (next_op == '-') {//basic substitution
			next_sub_exp = sub_exp - next_md_exp;
		}
		return sim_sub_exp(next_sub_exp);
	}
}

// Input: none, the sim_expression will be read in from stdin
// Effect: the next sim_expression is evaluated using
// a function call.
// Output: this function returns the value of the next sim_expression
float sim_exp(void) {
	float m = md_exp();
	return sim_sub_exp(m);
}

// Input: ’sub_exp’: the value of the current sub md_expression
// to the left of the next operator, ’next_op’,
// located at the front of current stdin.
// ’next_op’: an operator, ’*’ or ’/’. ’next_op’
// could also be ’+’, ’-’, or ’\n’
// indicating the end of the md_expression.
// the rest of the md_expression will be read in
// from stdin
// Effect: the md_expression is evaluated using recursion:
// get ’next_op’ with get_op()
// if ’next_op’ is ’+’, ’-’, or ’\n’
// push back ’next_op’ to stdin
// return ’sub_exp’
// else (’next_op’ is ’*’ or ’/’)
// get ’next_num’ with get_num()
// use ’sub_exp next_op next_num’ to do recursive call
// i.e. call md_sub_exp()
// end if
// Output: this function returns the value of the current md_expression
float md_sub_exp(float sub_exp) {
	char next_op = get_op();
	if (next_op == '+' || next_op == '-' || next_op == '\n') {
		ungetc(next_op, stdin);
		return sub_exp;
	}
	else {
		float next_num = get_num();
		float next_sub_exp;
		if (next_op == '/') {//basic division
			next_sub_exp = sub_exp / next_num;
		}
		else if (next_op == '*') {//basic multiplication
			next_sub_exp = sub_exp * next_num;
		}
		else if (next_op == '%') {//basic modulo
			next_sub_exp = fmod(sub_exp,next_num); //since modulo with float is not possible, use fmod from math.h
		}
		return md_sub_exp(next_sub_exp);
	}
}

// Input: none, the md_expression will be read in from stdin
// Effect: the next md_expression is evaluated using
// a function call.
// Output: this function returns the value of the next md_expression
float md_exp(void) {
	float m = get_num();
	return md_sub_exp(m);
}

