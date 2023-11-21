#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>   
#include <pthread.h> 

int input_array[4]; //initialize the input array to have size 4

void *sum(void *thread_id) { //function used by thread_1 to do summation and write to array
    printf("thread_1 (TID %lu) reads X = %d and Y = %d from input_array[]\n", pthread_self(), input_array[0], input_array[1]); //we use lu as it is a long unsigned integer
    int S = input_array[0] + input_array[1];
    input_array[2] = S; //writes sum to array in spot 2
    printf("thread_1 (TID %lu) writes X + Y = %d to the input_array[2]\n", pthread_self(), S);
}

void *even_odd(void *thread_id) { //function used by thread_2 to determine if element in array is even or odd
    printf("thread_2 (TID %lu) reads %d from input_array[2]\n", pthread_self(), input_array[2]);
    int S = input_array[2]; //gets summed value at index 2
    if (S%2 == 0) { //if it is even
        printf("thread_2 (TID %lu) identifies that %d is an even number \n", pthread_self(), S);
    } else { //result would be 1 for odd numbers
        printf("thread_2 (TID %lu) identifies that %d is an odd number \n", pthread_self(), S);
    }
}

void *multiplication(void *thread_id) { //function used by thread_2 to get the product of X and Y and store in array
    int M = input_array[0] * input_array[1];
    input_array[3] = M; //store product in index 3 of array
    printf("thread_2 (TID %lu) reads X and Y from input_array[], writes X * Y = %d to input_array[3]\n", pthread_self(), M);
}

void *reverse_num(void *thread_id) { //function used by thread_3 which gets value from array and reverses it
    int M = input_array[3]; //retrieves value at index 3
    printf("thread_3 (TID %lu) reads %d from input_array[3]\n", pthread_self(), M);
    int R = 0;
    int num = M; //copies M
    while (num !=0) { //while loop which gets slowly iterates through num and reverses it which is stored in R
        R = R * 10 + (num % 10);
        num = num/10;
        }
    printf("thread_3 (TID %lu) reverses the number %d -> %d\n", pthread_self(), M, R);
}

void *thread_2_tasks(void *thread_id) { //helper function for thread_2's execution so that the thread can execute both tasks in same thread
    even_odd(NULL);
    multiplication(NULL);
}

int main(int argc, char **argv) {
    //retrieves the commmand line arguments and store in X and Y 
    int X = atoi(argv[1]);
    int Y = atoi(argv[2]);

    printf("parent (PID %d) receives X = %d and Y = %d from the user \n", getpid(), X, Y);

    input_array[0] = X; input_array[1] = Y; //stores X and Y in first and second index of array

    printf("parent (PID %d) writes X = %d and Y = %d to input_array[]\n", getpid(), X, Y);

    pthread_t thread_1, thread_2, thread_3; //initializes threads

    //creates threads 1-3 and waits for it to execute before moving to next thread
    pthread_create(&thread_1, NULL, sum, NULL);
    pthread_join(thread_1, NULL);
    pthread_create(&thread_2, NULL, thread_2_tasks, NULL);
    pthread_join(thread_2, NULL);
    pthread_create(&thread_3, NULL, reverse_num, NULL);
    pthread_join(thread_3, NULL);

    //since we are waiting for threads to finish, the thread ids are the same for each since when one is done the new one is used right away, 
    //unless we do the 3 pthread_create first then the 3 pthread_join after, but it would not be in order and would screw up results

    return 0;

}