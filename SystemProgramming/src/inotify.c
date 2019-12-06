#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/inotify.h>

#if 0
struct inotify_event {
    int      wd;       /* Watch descriptor */
    uint32_t mask;     /* Mask describing event */
    uint32_t cookie;   /* Unique cookie associating related
                          events (for rename(2)) */
    uint32_t len;      /* Size of name field */
    char     name[];   /* Optional null-terminated name */
};
#endif

int main (int argc, char *argv[])
{
    int fd = -1;
    int wd1 = -1; // watch descriptor
    int wd2 = -1;
    char buf[1024];
    int ret;
    struct inotify_event *event;

    fd = inotify_init();

    if (fd == -1){
	perror("inotify_init() failed\n");
	return -1;
    }

    wd1 = inotify_add_watch(fd, ".", IN_CREATE | IN_DELETE);
    if (wd1 == -1){
	perror("inotify_add_watch() failed\n");
	goto err;
    }

    wd2 = inotify_add_watch(fd, "../test", IN_CREATE | IN_DELETE);
    if (wd2 == -1){
	perror("inotify_add_watch() failed\n");
	goto err;
    }

    while(1) {
	ret = read(fd, buf, sizeof(buf));
	if (ret == -1){
            perror("read() failed\n");
	    break;
	}
    

	event = (struct inotify_event *)&buf[0];

	while(ret > 0) {
	    if(event->mask & IN_CREATE){
	    printf("file %s is created\n", event->name);
	    } else if(event->mask & IN_DELETE){
	    	printf("file %s is deleted\n", event->name);
	    }
	    event = (struct inotify_event *)((char *)event + sizeof(struct inotify_event) + event->len);
	    ret -= (sizeof(struct inotify_event) + event->len);
	}
    }
    close(wd1);
    close(wd2);
    close(fd);

    return 0;

err:
    if (fd >=0){
	close(fd);
    }
    if (wd1 >=0){
	close(wd1);
    }
    if (wd2 >=0){
	close(wd2);
    }
    return -1;
}
