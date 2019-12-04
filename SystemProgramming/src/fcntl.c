#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main (int argc, char *argv[])
{
    int fd;
    int ret;
    int flag;
    char buf[128];

    fd = STDIN_FILENO;

    // blocking operation test
    printf("trying to read \n");
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));
    printf("read() [%s] - %d bytes \n", buf, ret);
    
    // non-blocking operation test
    flag = fcntl(fd, F_GETFL);
    if (flag == -1){
	perror("fcntl(F_GETFL) failed\n");
	return -1;
    }

    ret = fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    if (ret == -1) {
	perror("fcntl(F_SETFL) failed\n");
	return -1;
    }

    printf("trying to read \n");
    memset(buf, 0, sizeof(buf));
    ret = read(fd, buf, sizeof(buf));
    printf("read() [%s] - %d bytes \n", buf, ret);

    if(ret == -1){
	printf("errno : %d, %s\n", errno, strerror(errno));
    }
    
    return 0;
}
