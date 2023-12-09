#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Structure to represent an account, it holds the account number and account balance for each account as well as the transaction used on it
typedef struct {
    int accountNumber;
    int balance;
    int transaction;
} Account;

int numAccounts() { //function to count the number of Accounts
    int count = 0;
    FILE* file = fopen("assignment_5_input.txt", "r");
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the line starts with 'A'
        if (line[0] == 'A') {
            count++;
        }
    }

    fclose(file);
    return count;
}

int numClients() { //function to count the number of Clients
    int count = 0;
    FILE* file = fopen("assignment_5_input.txt", "r");
    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        // Check if the line starts with 'A'
        if (line[0] == 'C') {
            count++;
        }
    }

    fclose(file);
    return count;
}

pthread_mutex_t lock;

void *deposit_or_withdraw_money(void *arg);

void *deposit_or_withdraw_money(void *arg) { //thread function, can either deduct or add money to our accounts
    Account *accounts = (Account *)arg; //gets only the specific account we are looking for

    pthread_mutex_lock(&lock);  // ENTRY

    int newBalance = accounts->balance + accounts->transaction; //computes the transaction

    if (newBalance >= 0) {
        accounts->balance = newBalance;
    }  //only if the withdrawal is possible do we complete the transaction
            
    pthread_mutex_unlock(&lock); // EXIT
}

int main() {

    FILE* file = fopen("assignment_5_input.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    //calls and stores values from helper functions that have the number of accounts and clients 
    int numA = numAccounts();
    int numC = numClients();

    //creates as many threads as there are clients
    pthread_t threads[numC];
    int err_thread;
    Account accounts[numA]; //creates several structures, each structure will hold an account

    int i = 0;
    int transaction;
    while ((read = getline(&line, &len, file)) != -1) { //while loop to iteratively go line by line
        line[strcspn(line, "\n")] = 0; //remove trailing newline
        if (line[0] == 'A') { //if we are looking at the account balances
            char accountType;
            sscanf(line, " %c%d balance %d", &accountType, &accounts[i].accountNumber, &accounts[i].balance); //store balance and account number in its structure
        } else {
            char *token = strtok(line, " ");  //split the string using space and parse
            token = strtok(NULL, " "); //skip the first part where it shows C#
            while (token != NULL) {
                char *transactionType = token; token = strtok(NULL, " "); //stores wether it was a withdrawal or deposit, goes to next
                char *accountNumber = token; token = strtok(NULL, " "); int accountNum; sscanf(accountNumber, "A%d", &accountNum); //stores account number, goes to next
                char *transAmount = token; int transactionAmount = atoi(transAmount); //stores the transaction amount
                
                if (strcmp(transactionType, "withdraw") == 0) { //if it is a withdrawal
                    transactionAmount *= -1; //make it a negative number
                }

                accounts[accountNum-1].transaction = transactionAmount; //in the account we are making the transaction to, we store the transaction we will perform later

                err_thread = pthread_create(&threads[i], NULL, &deposit_or_withdraw_money, &accounts[accountNum-1]); //creates a thread to compute transaction
                
                if (err_thread != 0) {
                    printf("\n Error creating thread %d", i);
                } 

                pthread_join(threads[i], NULL); //waits for thread to be done
                
                //get next process
                token = strtok(NULL, " ");
            }
        }
        i++;
    }

    fclose(file);
    pthread_mutex_destroy(&lock);

    // Final Output
    printf("No. of Accounts: %d\n", numA);
    printf("No. of Clients: %d\n", numC);
    for (int i = 0; i < numA; i++) { //goes through each account number, prints out its respective number and final balance. 
            printf("A%d balance %d\n", accounts[i].accountNumber, accounts[i].balance);
        }

    return 0;
}