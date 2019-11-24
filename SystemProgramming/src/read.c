#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

struct person
{
    char name[16];
    int age;
};

static int write_info(struct person *p)
{
    int fd;
    ssize_t ret;

    fd = open("people info", O_CREAT | O_WRONLY | O_APPEND, 0644);

    if (fd == -1) {
	perror("open error\n");
	return -1;
    }
    // !man 2 write, check param & ret val
    ret = write(fd, p, sizeof(struct person)); 
    if (ret == -1){
	perror("write error\n");
	close(fd); 
	return -1;
    } else if (ret != sizeof(struct person)){
	perror("write error(partial write)\n");
	close(fd); 
	return -1;
    
    }

    close(fd);
    return 0;
} 

static int dump_info(void)
{
    int fd;
    ssize_t ret;
    struct person p;

    fd = open("people info", O_RDONLY);

    if (fd == -1) {
	perror("open error\n");
	return -1;
    }

    do {
    // !man 2 read, check param & ret val
    ret = read(fd, &p, sizeof(struct person)); 
    if (ret == -1){
	perror("read error\n   ");
	close(fd); 
	return -1;
    } else if (ret == 0){
	break;    
    } else if (ret != sizeof(struct person)){
	perror("read error(partial read)\n");
	close(fd); 
	return -1;
    }

    printf("name %s, age %d\n", p.name, p.age );
    } while(1);

    close(fd);
    return 0;
}

int main (int argc, char *argv[])
{
    struct person people[] = {
	{"kim", 40}, {"lee", 30}
    };
    write_info(&people[0]);
    write_info(&people[1]);

    dump_info();

    return 0;
}
