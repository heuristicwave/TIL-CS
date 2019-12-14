#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void sigusr1_handler (int sig, siginfo_t *info, void *ucontext){
    printf("got sigusr1\n");

    if(info->si_code & SI_QUEUE){
	printf("sigqueue() send %d\n", info->si_int);
    } else {
	printf("kill() send\n");
    }
}

int main (int argc, char *argv[]){

    struct sigaction act;

    memset(&act, 0, sizeof(struct sigaction));
    act.sa_sigaction = sigusr1_handler;
    act.sa_flags = SA_SIGINFO;

    if(sigaction(SIGUSR1, &act, NULL)){
	printf("sigaction() fail\n");
	return -1;
    } 

    while(1){
	sleep(1);
    }
    return 0;
}
