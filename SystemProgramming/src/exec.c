#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void test_func(){
    printf("Test Func pid : %d\n", getpid());
}

int main (int argc, char *argv[])
{
    pid_t pid;
    int exit_status;

    printf("Origin process pid : %d\n", getpid());

    pid = fork();

    if (pid == 0) { // child process
	printf("Child process pid : %d\n", getpid());
	if (execl("/bin/ls","ls", "-al", NULL) == -1){
	    printf("execl() failed\n");
	    return -1;
	}
    } else if (pid > 0) { // parent process
	printf("Parent process pid : %d, Child process pid : %d\n", getpid(), pid);
    } 

    test_func();

    pid = wait(&exit_status);
    if (WIFEXITED(exit_status)){
	printf("Child %d returns %d\n", pid, WEXITSTATUS(exit_status));
    } else {
	printf("Child is not exited\n");
    } 

    return 0;
}

/*
Origin process pid : 42807
Parent process pid : 42807, Child process pid : 42808
Test Func pid : 42807
Child process pid : 42808
total 420
*/
