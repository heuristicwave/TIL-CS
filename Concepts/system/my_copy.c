#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	int input_fd;
	int output_fd;
	char buf[BUF_SIZE];

	if(argc!=3){
		printf("Usage :%s <org file> <dst file> \n", argv[0]);
		exit(0);
	}

	if((input_fd = open(argv[1],O_RDONLY))!=-1){
		if((output_fd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC))!=-1){
			int cnt;
			do{
				cnt = 0;
				cnt = read(input_fd, buf, BUF_SIZE);
				if(cnt = write(output_fd, buf, cnt)){
					continue;
				}
			}while(cnt!=0);
		}
	
		else {
			printf("Failed to open %s \n", argv[2]);
			close(input_fd);
			return -1;
		}
	close(output_fd);
	close(input_fd);
	}
	else {
		printf("Failed to open %s \n", argv[1]);
		return -1;
	}

	return 0;
}