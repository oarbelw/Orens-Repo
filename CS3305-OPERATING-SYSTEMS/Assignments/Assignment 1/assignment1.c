#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    //Initiate variables N,M,S that are passed as arguments
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    char *S = argv[3];

    //Initiate status variable for execl return, and PID variables
    int status;
    pid_t pid_child_1, pid_child_1_1, pid_child_1_2, pid_child_2;

    printf("parent (PID %d): process started\n\n", getpid());
   
    //Fork child_1
    printf("parent (PID %d): forking child_1\n", getpid());
    pid_child_1 = fork();
    if (pid_child_1 == 0) { //child1
        printf("parent (PID %d): fork successful for child_1 (PID %d)\n", getppid(), getpid());
        printf("parent (PID %d): waiting for child_1 (PID %d) to complete\n", getppid(), getpid());
        printf("child_1 (PID %d): process started from parent (PID %d)\n\n", getpid(), getppid());
        
        printf("child_1 (PID %d): forking child_1.1\n", getpid());
        pid_child_1_1 = fork();
        if (pid_child_1_1 == 0) { //child1.1
            printf("child_1.1 (PID %d): process started from child_1 (PID %d)\n", getpid(), getppid());
            printf("child_1.1 (PID %d): calling an external program [./external_program1.out]\n", getpid());

            status = execl("./external_program1.out", argv[1], NULL); //Pass N as argv[1]
            
        } else {
            wait(NULL); //wait for child_1.1 to complete
            printf("child_1 (PID %d): completed child_1.1\n\n", getpid());

            printf("child_1 (PID %d): forking child_1.2\n", getpid());
            pid_child_1_2 = fork();
            if (pid_child_1_2 == 0) { //child1.2
                printf("child_1.2 (PID %d): process started from child_1 (PID %d)\n", getpid(), getppid());
                printf("child_1.2 (PID %d): calling an external program [./external_program1.out]\n", getpid());

                status = execl("./external_program1.out", argv[2], NULL); //Pass M as argv[2]
            } else {
                wait(NULL); //wait for child1.2 to complete
                printf("child_1 (PID %d): completed child_1.2\n\n", getpid());
            }
        }

    } else {
        wait(NULL); //Wait for child_1 to be completed before creating child_2
        printf("parent (PID %d): forking child_2\n", getpid());
        pid_child_2 = fork();
        if (pid_child_2 == 0){ //child_2
            printf("parent (PID %d): fork successful for child_2 (PID %d)\n", getppid(), getpid());
            printf("child_2 (PID %d): process started from parent (PID %d)\n", getpid(), getppid());
            printf("child_2 (PID %d): calling an external program [./external_program2.out]\n", getpid());

            status = execl("./external_program2.out", S, NULL);
        } else {
            wait(NULL); //Wait for the completion of child_2
            printf("parent (PID %d): completed parent\n", getpid());
        }
    }
}