#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define IPC_KEY_FILENAME	"/proc"
#define IPC_KEY_PROJ_ID		'a'
#define MSGBUF_STR_SIZE		64

struct msgbuf {
    long mtype;
    char string[MSGBUF_STR_SIZE];
};

static void print_usage(char *progname) {
    printf("%s (send|recv)\n MTYPE", progname);
    return;
}

static int init_msgq(void) {
    int msgq;
    key_t key;

    key = ftok(IPC_KEY_FILENAME, IPC_KEY_PROJ_ID);

    if(key == -1){
	perror("ftok()\n");
	return -1;
    } 
    msgq = msgget(key, 0644 | IPC_CREAT);
    if(key == -1){
	perror("msgget()\n");
	return -1;
    }  
    return msgq;  
}


static int do_send(long mtype){
    int msgq;
    struct msgbuf mbuf;
    
    msgq = init_msgq();
    if(msgq == -1){
	perror("init_msgq()\n");
	return -1;
    }  

    memset(&mbuf, 0, sizeof(mbuf));
    mbuf.mtype = mtype;
    strncpy(mbuf.string, "Hello World", sizeof(mbuf.string) - 1);
    snprintf(mbuf.string, sizeof(mbuf.string),
	"hello world mtype %ld", mtype);
    if (msgsnd(msgq, &mbuf, sizeof(mbuf.string), 0) == -1) {
	perror("msgsnd()");
	return -1;
    }

    return 0;
}

static int do_recv(long mtype){
    int msgq;
    int ret;
    struct msgbuf mbuf;
    
    msgq = init_msgq();
    if(msgq == -1){
	perror("init_msgq()\n");
	return -1;
    }  

    memset(&mbuf, 0, sizeof(mbuf));
    ret = msgrcv(msgq, &mbuf, sizeof(mbuf.string), mtype, 0);
    if(ret == -1){
	perror("msgrcv()\n");
	return -1;
    }  
    printf("received msg: mtype %ld, msg [%s]\n", mbuf.mtype, mbuf.string);

    return 0;
}

int main (int argc, char *argv[]){

    int ret;
    long mtype;

    if(argc < 2){
	print_usage(argv[0]);
	return -1;
    }

    mtype = strtol(argv[2], NULL, 10);

    if (!strcmp(argv[1], "send")) {
	if(mtype < 0){
	    print_usage(argv[0]);
	    return -1;
	}
	ret = do_send(mtype);
    } else if (!strcmp(argv[1], "recv")) {
	ret = do_recv(mtype);
    } else {
	print_usage(argv[0]);
	goto err;
    }

    return ret;

err:
    return -1;
}
