#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int numprocesses(char * line) { //function to count the number of processes in a line
    int count = 0;
    for(int i = 0; line[i]; i++) {
        if (line[i] == 'p') { //count how many p's for processes
            count++;
        }
    }
    return count;
}

bool inarr(int n, int arr[n], int tofind) { //function that loops through a list to find if there is an occurance or not of an int in an array of ints
    for (int i = 0; i < n; i++) {
        if (arr[i] == tofind) { 
            return true;
        }
    }
    return false;
}

int main() {

    //initialize the file and pointers and length for reading lines from file
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("sjf_input.txt", "r"); //opens the file
    if (fp == NULL) //if it is empty trigger exit
        exit(EXIT_FAILURE);
    
    int testcasenum = 1;
    while ((read = getline(&line, &len, fp)) != -1) {
        line[strcspn(line, "\n")] = 0; //remove trailing newline
        printf("Test case #%d: %s\n", testcasenum++, line);
        int numberofprocesses = numprocesses(line); //calls function to determine number of processes in line
        printf("Number of Processes: %d\n", numberofprocesses);

        char *token = strtok(line, " ");  //split the string using space and parse

        int casearr[numberofprocesses][3]; //initialize the 2d array containing the case information

        int i = 0;
        while (token != NULL) {
            char *proc = token; token = strtok(NULL, " "); //the first element is the process number, save in proc and get next element
            char *arivtime = token; int arivaltime = atoi(arivtime); token = strtok(NULL, " "); //the second element is arrival time, save in arivtime and convert to integer and get next element
            char *burtime = token; int burstttime = atoi(burtime); //the third element is burst time, save in burtime and convert to integer
            
            //put into array
            casearr[i][0] = i+1; casearr[i][1] = arivaltime; casearr[i][2] = burstttime; 
            i++;

            //get next process
            token = strtok(NULL, " ");
        }

        //Sort according to burst time
        for (int i = 0; i < numberofprocesses - 1; i++) {
            for (int j = 0; j < numberofprocesses - i - 1; j++) {
                if (casearr[j][2] > casearr[j + 1][2]) { //compare burst time
                    int temp[3];
                    for (int k = 0; k < 3; k++) {//swap processes if needed, 3 for number of columns in casearr
                        temp[k] = casearr[j][k];
                        casearr[j][k] = casearr[j + 1][k];
                        casearr[j + 1][k] = temp[k];
                    }
                }
            }
        }

        //  // Print the process data array
        // for (int j = 0; j < numberofprocesses; j++) {
        //     printf("Process: %d, Arrival Time: %d, Burst Time: %d\n", casearr[j][0], casearr[j][1], casearr[j][2]);
        // }

        printf("Process Scheduling Started:\n");
        int cputime = 0, completedproc = 0, waitingvalueslist[numberofprocesses], turnaroundvalueslist[numberofprocesses], k = 0, curr_proc = -1, l = 0, p = 0, r = 0;
        //set up dynamically created arrays to store the lists of processes that arrived and processes that are completed, use to determine order of which processes to pick from sorted order
        int *arrivallist = NULL; 
        int *completedlist = NULL;
        arrivallist = (int *)malloc(k * sizeof(int));
        completedlist = (int *)malloc(k * sizeof(int));
        while (completedproc < numberofprocesses) {
            int empty = 0;
            printf("CPU Time %d: ", cputime);
            for (int j = 0; j < numberofprocesses; j++) {
                if (casearr[j][1] == cputime) { //Check if arrival time of a process is at that cputime
                    printf("[P%d Arrived] ", casearr[j][0]); empty = 1;//where casearr[j][0] is the process's number
                    // Resize the lists
                    arrivallist = (int *)realloc(arrivallist, (k+1) * sizeof(int));
                    completedlist = (int *)realloc(completedlist, (k+1) * sizeof(int));
                    arrivallist[k++] = casearr[j][0]; //adds process number to a list of all the processes that have arrived
                }
            }
            if (curr_proc == -1) { //if we do not have a current process
                for (int j = 0; j < numberofprocesses; j++) { //now that we know which processes arrived, we can select current process
                    if (inarr(k, arrivallist, casearr[j][0]) == true && inarr(k, completedlist, casearr[j][0]) == false) { //if it is found in arrival list and it is not already in the list of completed processes
                        curr_proc = j;
                        break;
                    }
                }
            } 

            if (curr_proc != -1) { //if we find a current process from above
                printf("P%d [%d/%d]\n", casearr[curr_proc][0], l, casearr[curr_proc][2]); empty = 1;
                if (l == casearr[curr_proc][2]) { //if we find that it just finished its process
                    completedlist[p++] = casearr[curr_proc][0]; //adds process number to a list of all the completed processes
                    int turntime = cputime - casearr[curr_proc][1]; //turnaround time is time from arrival to completion
                    int waittime = turntime - casearr[curr_proc][2]; //waiting time is time from arrival to start of process, or for this scheduling algorithm, the turnaround time minus the amount of time it took for the process to complete once it started
                    waitingvalueslist[r] = waittime;
                    turnaroundvalueslist[r] = turntime;
                    r++;
                    printf("Process P%d completed with Turnaround Time: %d, Waiting Time %d\n", casearr[curr_proc][0], turntime, waittime);
                    l = -1; //we set to minus 1 because we will have to add 1 to it right after this and we want to reset to 0
                    curr_proc = -1; //set curr_proc to look for next one
                    completedproc++; //indicate that we completed another process
                    cputime--; //since the next process will start at the same cpu time this one ended, we want to make sure the next process stays at this time
                }
                l++;
            }
            int turnaroundvals = 0, waittimevals = 0;
            if (completedproc == numberofprocesses) {//this will occur when all the processes are done
                for (int i = 0; i < numberofprocesses; i++) { //used to store sums of turnaroundtime and waittime
                    turnaroundvals += turnaroundvalueslist[i];
                    waittimevals += waitingvalueslist[i];
                }
                printf("Process scheduling completed with Avg Turnaround Time: %.2f, Avg Waiting Time: %.2f\n\n", turnaroundvals/(float)numberofprocesses, waittimevals/(float)numberofprocesses); //divide sums by numberofprocesses and make float, using .2f for 2 decimal points
            }

            if (empty == 0) { //if there is nothing to say about this point in cpu time, print None
                printf("None\n");
            }
            cputime++;
            if (cputime > 30) return 0;
        }
        //free created lists from above
        free(arrivallist);
        free(completedlist);
    }

    fclose(fp);
    return 0;
}