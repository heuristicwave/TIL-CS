#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAX	100000000
int shared = 0;
pthread_mutex_t mutex;

// trial and error
// error: control reaches end of non-void function [-Werror=return-type]
void *child_thread_main(void *arg){
    unsigned int i;
    printf("child pthread_id %lu\n", pthread_self());


    for(i=0; i<MAX; i++){
	pthread_mutex_lock(&mutex);
	shared++;
	pthread_mutex_unlock(&mutex);
    }

    for(i=0; i<MAX; i++){
	pthread_mutex_lock(&mutex);
	shared--;
	pthread_mutex_unlock(&mutex);
    }

    return NULL;	// void pointer func need ret value
}

int main (int argc, char *argv[]){

    int ret;
    pthread_t child_threads[2];

    if(pthread_mutex_init(&mutex, NULL)){
	printf("mutex init fail\n");
	return -1;
    }

    printf("main pthread_id %lu\n", pthread_self());

    ret = pthread_create(&child_threads[0], NULL, child_thread_main, NULL);
    if(ret){
	printf("pthread_create() fail(%d)\n", ret);
	return -1;
    }

    ret = pthread_create(&child_threads[1], NULL, child_thread_main, NULL);
    if(ret){
	printf("pthread_create() fail(%d)\n", ret);
	return -1;
    }

    printf("join child_threads[0](%lu)\n", child_threads[0]);
    if(pthread_join(child_threads[0], NULL)){
	printf("pthread_join(%lu) fail\n", child_threads[0]);
    };

    printf("join child_threads[1](%lu)\n", child_threads[1]);
    if(pthread_join(child_threads[1], NULL)){
	printf("pthread_join(%lu) fail\n", child_threads[1]);
    };

    printf("shared : %d\n", shared);

    return 0;
}

/*
compile cmd & option : cc -Wall -Werror -pthread -o thread thread.c

Thread Off
main pthread_id 139860060731200
join child_threads[0](139860060727040)
child pthread_id 139860060727040
child pthread_id 139860052334336
join child_threads[1](139860052334336)
shared : -20749826

Thread On
main pthread_id 140092468389696
child pthread_id 140092468385536
join child_threads[0](140092468385536)
child pthread_id 140092459992832
join child_threads[1](140092459992832)
shared : 0
*/
