#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

void test_func(){
    printf("Test Func pid : %d\n", getpid());
}

int main (int argc, char *argv[])
{
    pid_t pid;

    printf("Origin process pid : %d\n", getpid());

    pid = fork();

    if (pid == 0) { // child process
	printf("Child process pid : %d\n", getpid());
    } else if (pid > 0) { // parent process
	printf("Parent process pid : %d, Child process pid : %d\n", getpid(), pid);
    } 

    test_func();
    return 0;
}

/*
Origin process pid : 41579
Parent process pid : 41579, Child process pid : 41580
Test Func pid : 41579
Child process pid : 41580
Test Func pid : 41580
*/
