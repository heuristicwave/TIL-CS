#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void sigterm_handler(int signum){
    printf("got sigterm");
    // exit(-1); To terminate the app, need to exit
}

int main (int argc, char *argv[]){

    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    // not work, killall -s INT signal = ctrl + c
    // works, killall -s KILL signal
    sigprocmask(SIG_SETMASK, &set, NULL);

    signal(SIGTERM, sigterm_handler);
    printf("start of while(1)\n");

    while(1){
	sleep(1);
    }

    return 0;
}
