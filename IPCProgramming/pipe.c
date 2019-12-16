#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[]){
    int pipe_fds[2];
    int wstatus;
    pid_t pid;
    char buf[1024];

    printf("[%d] start of function\n", getpid());
    memset(buf, 0, sizeof(buf));

    if(pipe(pipe_fds)){
	perror("pipe()");
	return -1;
    }

    pid = fork();
    if (pid == 0) { // child process 
	close(pipe_fds[1]);
	read(pipe_fds[0], buf, sizeof(buf)); 
	printf("[%d] parent said...  %s\n", getpid(), buf);
	close(pipe_fds[0]);
    } else if (pid > 0) { // parent process
	close(pipe_fds[0]); 
	strncpy(buf, "hello child!", sizeof(buf) -1);
	write(pipe_fds[1], buf, strlen(buf)); 
	close(pipe_fds[1]);

	pid = wait(&wstatus);
    } else {
	perror("fork() err");
	goto err;
    }

    return 0;

err:
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    return -1;
}
