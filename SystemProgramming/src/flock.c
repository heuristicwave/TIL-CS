#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <errno.h>

static void print_usage(const char *progname){
    printf("usage: %s (ex|sh)\n", progname);
    exit(-1);
}
int main (int argc, char *argv[])
{
    int fd;
    int ops;

    if(argc <2) {
	print_usage(argv[0]);
    }

    if(!strcmp(argv[1], "sh")) {	// shared lock
	ops = LOCK_SH;
    } else if (!strcmp(argv[1], "ex")) { // exclusive lock
	ops = LOCK_EX;
    } else {
	print_usage(argv[0]);
    }

    fd = open("lockfile", O_RDWR | O_CREAT, 0644);
    if(fd < 0) {
	perror("file open error\n");
	return -1;
    }
    // I must study LOCK_NB
    // flock(fd, ops | LOCK_NB) 
    printf("trying to grab the lock \n");
    if(flock(fd, ops) !=0 ){
	printf("flocks(ops %d), error=%d(%s)\n", ops, errno, strerror(errno));
	goto out;
    }

    printf("grab the lock!! \n");
    getc(stdin);

    if(flock(fd, LOCK_UN)){
	printf("flocks(unlock)\n");
	goto out;
    }
    close(fd);

    return 0;

out:
    close(fd);
    return -1;
}
