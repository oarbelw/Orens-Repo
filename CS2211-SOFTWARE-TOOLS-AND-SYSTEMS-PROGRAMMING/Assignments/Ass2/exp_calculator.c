//CS2211b 2023
//Assignment 2
//Oren Arbel-Wood
//251251876
//oarbelwo
//February 8, 2023

//exponential number calculator
#include <stdio.h>
#include <stdbool.h>
#include <math.h> //this is necessary for pow function, to use power of 2
double exponential_calc(double base, int exponent) {
	// we assume base is a non-zero double, and exponent is int
	double result;
	if (exponent == 0) {//this is the base case
		return 1;
	}
	if (exponent < 0) { //if it is negative exponent
		return 1/exponential_calc(base, -exponent);
	}
	if ((exponent % 2) == 0 ) //if it is positive
	{
		return pow((exponential_calc(base, exponent/2)), 2);
	}
	else //then it is odd
	{
		return pow((exponential_calc(base, (exponent-1)/2)), 2) * base;
	}
}

int main(void) 
{
	double base,result; //doubles to store the base and the output result
	int exp; //this is the integer exponent
	bool repeat = true; //to use for our while loop
	
	while (repeat == true) //stops when repeat is false
	{
		printf("Enter the base (non-zero double): ");
        	scanf(" %lf", &base);
        	printf("Enter the exponent (integer): ");
        	scanf(" %d", &exp);
		result = exponential_calc(base, exp); //this returns the recursive result
        	printf("Result is : %.20lf\n", result); //we use 20 to show up to 20 decimal places
		if (exp == 0) { //if it is 0, we terminate the program 
			repeat = false;
		}
	}
	return 0;
}
