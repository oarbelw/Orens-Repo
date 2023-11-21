#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

int summation(int start, int end)
{
	int sum = 0;
	if (start < end)
	{
		sum = ((end * (end + 1)) - (start * (start - 1))) / 2;
	}
	return sum;
}

int ith_part_start(int i, int N, int M)
{
	int part_size = N / M;
	int start = i * part_size;
	return start;
}
int ith_part_end(int i, int N, int M)
{
	int part_size = N / M;
	int end = (i < M - 1) ? ((i + 1) * part_size - 1) : N;
	return end;
}
int main(int argc, char **argv)
{
	// YOUR CODE GOES HERE
	int N = atoi(argv[1]);
    int M = atoi(argv[2]);
	int port[2];

	if (pipe(port) < 0){ //this is to initialize the pipe
		perror("pipe error");
		exit(0);
	} 

	pid_t child_1;
	
	printf("parent (PID %d): process started\n\n", getpid());

	//Step 1 - Forking child_1
	printf("parent (PID %d): forking child_1\n", getpid());
    child_1 = fork();
	if (child_1 == 0) { //Make sure we are in child_1 process
	    printf("parent (PID %d): fork successful for child_1 (PID %d)\n", getppid(), getpid());
		printf("parent (PID %d): waiting for child_1 (PID %d) to complete\n\n", getppid(), getpid());

        printf("child_1 (PID %d): process started from parent (PID %d)\n", getpid(), getppid());
		printf("child_1 (PID %d): forking child_1.1....child_1.%d\n\n", getpid(), M);
		for (int i = 0; i < M; i++) { //Loop generates M child processes
			//Step 3 - fork() function will be called M times
			pid_t child_1_i = fork();
			if (child_1_i == 0) {//Inside child_1.i
				printf("child_1.%d(PID %d): fork() successful\n", i+1, getpid());
				int start = ith_part_start(i, N, M);
                int end = ith_part_end(i, N, M);
				//Step 4 - child invokes summation function to calculate partial_sum
				int partial_sum = summation(start, end); 
				printf("child_1.%d(PID %d): partial sum: [%d - %d] = %d\n", i+1, getpid(), start, end, partial_sum);

				//Step 5 - writes partial_sum to a pipe
				write(port[1], &partial_sum, sizeof(partial_sum));

				exit(0); //exit to terminate child process
			} else {
				wait(NULL); 
			}
		}

		//Step 6 - read from pipe and compute the total sum
		int total_sum = 0;
		int partial_sum;
		for (int i = 0; i < M; i++) {
			read(port[0], &partial_sum, sizeof(partial_sum));
			// printf("Partial sum = %d", partial_sum);
			total_sum += partial_sum;
		}

		printf("\nchild_1 (PID %d): total sum = %d\n", getpid(), total_sum); //Step 7 - display total sum
		printf("child_1 (PID %d): child_1 completed\n\n", getpid());

	} else {
		wait(NULL); //Step 2- Wait for child_1 to be completed, pause parent process
		printf("parent (PID %d): parent completed\n", getpid()); //Step 8 - parent process will conclude
	}
}