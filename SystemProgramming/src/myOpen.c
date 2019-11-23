#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static int append_file(void)
{
    int fd;

    fd = open("datafile", O_WRONLY | O_APPEND);

    if (fd == -1 ) {
	printf("open error\n");
	return -1; 
    }

    dprintf(fd, "AGAIN APPEND!!");

    
    close(fd);
    return 0;
}

static int trunc_file(void)
{
    int fd;

    fd = open("datafile", O_WRONLY | O_CREAT | O_TRUNC, 0600);

    if (fd == -1 ) {
	printf("open error\n");
	return -1; 
    }

    dprintf(fd, "TRUNC!!");

    
    close(fd);
    return 0;
}

static int write_file(void)
{
    int fd;

    fd = open("datafile", O_WRONLY | O_CREAT, 0644);

    if (fd == -1 ) {
	printf("open error\n");
	return -1; 
    }

    dprintf(fd, "!man 2 open");

    
    close(fd);
    return 0;
}

int main (int argc, char *argv[])
{
    if (write_file()){
	printf("write_file_error\n");
	return -1;
    }
    if (trunc_file()){
	printf("trunc_file_error\n");
	return -1;
    }
    if (append_file()){
	printf("append_file_error\n");
	return -1;
    }

    return 0;
}
