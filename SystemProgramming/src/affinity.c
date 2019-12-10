#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>

#define MAXCPU 2
static void print_cpuset(cpu_set_t *mask){
    int i;
    for(i=0; i<MAXCPU; i++){
	if(CPU_ISSET(i, mask)){
	    printf("cpu %d", i);
	}
    }
    printf("\n");
}

int main (int argc, char *argv[]){

    int cur_cpu;
    cpu_set_t mask;

    if(sched_getaffinity(getpid(), sizeof(cpu_set_t), &mask)){
	perror("sched_getaffinity()\n");
	return -1;
    }
    print_cpuset(&mask);
    
    cur_cpu = sched_getcpu();
    printf("run on CPU %d \n", cur_cpu);

    CPU_ZERO(&mask);
    CPU_SET(cur_cpu ^ 1, &mask);
    if(sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask)){
	perror("sched_setaffinity()\n");
	return -1;
    }

    sleep(1);
    
    cur_cpu = sched_getcpu();
    printf("run on CPU %d \n", cur_cpu);

    return 0;
}

/*
cpu 0cpu 1
run on CPU 1 
run on CPU 0
*/
