//CS2211b 2023
//Assignment 2
//Oren Arbel-Wood
//251251876
//oarbelwo
//February 8, 2023

//this is our converter
//first lets declare the necessary libraries

#include <stdio.h>
#include <stdbool.h>

//next, lets define the universal constants
#define FREEZING_PT 32.0f
#define TEMP_SCALE_FACTOR (5.0f / 9.0f)
#define CM_INCH_SCALE_FACTOR 2.54f
#define KG_PD_SCALE_FACTOR 2.205f
#define M_FT_SCALE_FACTOR 3.281f

//next, the following 8 methods are used to convert between necessary options

void convert_celsius_to_fahrenheit(void) {
	float celsius, fahrenheit;
	printf("Enter temperature in Celsius: ");
	scanf("%f", &celsius);
	fahrenheit = (celsius/TEMP_SCALE_FACTOR) + FREEZING_PT;
	printf("Fahrenheit equivalent: %.1f\n", fahrenheit); //we want to print to 1 decimal place for temperature
}

void convert_fahrenheit_to_celsius(void) {
        float celsius, fahrenheit;
        printf("Enter temperature in Fahrenheit: ");
        scanf("%f", &fahrenheit);
        celsius = (fahrenheit - FREEZING_PT) * TEMP_SCALE_FACTOR;
        printf("Celsius equivalent: %.1f\n", celsius);
}

void convert_cm_to_inch(void) {
        float cm, inch;
        printf("Enter centimetres: ");
        scanf("%f", &cm);
	inch = cm/CM_INCH_SCALE_FACTOR;
        printf("Inches equivalent: %.2f\n", inch); //now, it is printed to 2 decimal places for more accuracy
}

void convert_inch_to_cm(void) {
        float cm, inch;
        printf("Enter inches: ");
        scanf("%f", &inch);
        cm = inch * CM_INCH_SCALE_FACTOR;
        printf("Centimetres equivalent: %.2f\n", cm);
}

void convert_kg_to_pd(void) {
        float kg, pd;
        printf("Enter Kilograms: ");
        scanf("%f", &kg);
        pd = kg * KG_PD_SCALE_FACTOR;
	printf("Pounds equivalent: %.2f\n", pd);
}

void convert_pd_to_kg(void) {
        float kg, pd;
        printf("Enter Pounds: ");
        scanf("%f", &pd);
        kg = pd/KG_PD_SCALE_FACTOR;
        printf("Kilograms equivalent: %.2f\n", kg);
}

void convert_meter_to_ft(void) {
        float m, ft;
        printf("Enter Meters: ");
        scanf("%f", &m);
        ft = m * M_FT_SCALE_FACTOR;
	printf("Feet equivalent: %.2f\n", ft);
}

void convert_ft_to_meter(void) {
        float m, ft;
        printf("Enter Feet: ");
        scanf("%f", &ft);
        m = ft/M_FT_SCALE_FACTOR;
        printf("Meter equivalent: %.2f\n", m);
}

//below is the main method to use and call conversion methods above

int main(void) 
{
	char option; //used for user input
	bool repeat = true; //this is used to work the main loop

	while (repeat == true) //this runs until repeat is switched off
	{
		printf("Please enter one of the following: \n");
		printf("1 for conversion between Celsius and Fahrenheit\n");
		printf("2 for conversion between Centimetre and Inch\n");
		printf("3 for conversion between Kilogram and Pound\n");
		printf("4 for conversion between Meter and Feet\n");
		printf("q or Q to quit\n");
		scanf(" %c", &option);

		if (option == '1') {
			char options; //this is used to track user input
			bool inner_repeat = true;
			while (inner_repeat == true) //now, we want another inner while loop to repeat asking the following question untill C or F is entered
			{
				printf("Please enter one of the following: \n");
				printf("C for conversion from Celsius to Fahrenheit\n");
				printf("F for conversion from Fahrenheit to Celsius\n");
				scanf(" %c", &options);

				if (options == 'C') { //if it is this option, we call the conversion method and turn off the while loop to bring back to main menu
					convert_celsius_to_fahrenheit();
					inner_repeat = false;
				}
				if (options == 'F') {
					convert_fahrenheit_to_celsius();
					inner_repeat = false;
				}
			}
		}

		if (option == '2') {
                        char options;
                        bool inner_repeat = true;
                        while (inner_repeat == true)
                        {
                                printf("Please enter one of the following: \n");
                                printf("C for conversion from Centimetre to Inch\n");
                                printf("I for conversion from Inch to Centimetre\n");
                                scanf(" %c", &options);

                                if (options == 'C') {
                                        convert_cm_to_inch();
                                        inner_repeat = false;
                                }
                                if (options == 'I') {
                                        convert_inch_to_cm();
                                        inner_repeat = false;
                                }
                        }
                }

		if (option == '3') {
                        char options;
                        bool inner_repeat = true;
                        while (inner_repeat == true)
                        {
                                printf("Please enter one of the following: \n");
                                printf("K for conversion from Kilogram to Pound\n");
                                printf("P for conversion from Pound to Kilogram\n");
                                scanf(" %c", &options);

                                if (options == 'K') {
                                        convert_kg_to_pd();
					inner_repeat = false;
                                }
                                if (options == 'P') {
                                        convert_pd_to_kg();
					inner_repeat = false;
                                }
                        }
                }

		if (option == '4') {
                        char options;
                        bool inner_repeat = true;
                        while (inner_repeat == true)
                        {
                                printf("Please enter one of the following: \n");
                                printf("M for conversion from Meter to Feet\n");
				printf("F for conversion from Feet to Meter\n");
                                scanf(" %c", &options);

                                if (options == 'M') {
                                        convert_meter_to_ft();
					inner_repeat = false;
                                }
                                if (options == 'F') {
                                        convert_ft_to_meter();
					inner_repeat = false;
                                }
                        }
                }

		if (option == 'q' || option == 'Q') {//if the user enters either q or Q, the main while loop can be turned off and stop asking
			repeat = false;
		}
	}
}
