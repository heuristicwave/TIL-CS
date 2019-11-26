#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char *argv[])
{
    struct stat statbuf;

    if (argc < 2) {
	printf("usage : %s file name\n",argv[0]);
	return -1;
    }

    if(stat(argv[1], &statbuf)){
	printf("stat fail()");
	return -1;
    }
   
    printf("file name %s\n",argv[1]);
    printf("size %ld\n",statbuf.st_size);

    if(S_ISDIR(statbuf.st_mode)){
	printf("It is directory\n");
    } else if (S_ISREG(statbuf.st_mode)) {
	printf("It is regular file\n");
    } else {
	printf("IDK\n");
    }

    return 0;
}
