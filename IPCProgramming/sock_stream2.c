#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>

#define SOCK_PATH	"sock_stream_un"

static void print_usage (const char *progname){
    printf("%s (servel|client) \n", progname);
}

int stream_send(int sock, void *buf, size_t buflen, int flag){

    int written = 0;
    int ret;

    while(written < buflen){
	// void pointer -> char pointer casting
	ret += send(sock, (char *)buf + written, buflen - written, flag);
	if (ret == -1){
	    return ret;
	}
	written += ret;
    }
    return 0;
}

int stream_recv(int sock, void *buf, size_t buflen, int flag){

    int written = 0;
    int ret;

    while(written < buflen){
	// void pointer -> char pointer casting
	ret += recv(sock, (char *)buf + written, buflen - written, flag);
	if (ret == -1){
	    return ret;
	}
	written += ret;
    }
    return 0;
}

/*
    socket() -> bind() -> listen() ->
    accept() -> send/recv -> close()
*/
static int do_server(void){

    int ret;
    int sock;
    struct sockaddr_un addr;
    int peer;
    char buf[128];

    // int socket(int domain, int type, int protocol);
    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    if (sock == -1) {
	perror("socket()");
	return -1;
    }
    
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    
    if( bind(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1){
	perror("bind()");
	close(sock);
	return -1;
    };

    listen(sock, 5);

    peer = accept(sock, NULL, NULL);
    
    if (peer < 0) {
	perror("accept()");
	close(sock);
	return -1;
    }

    memset(buf, 0, sizeof(buf));
#if 0
    ret = recv(peer, buf, sizeof(buf), 0);
#else
    ret = stream_recv(peer, buf, sizeof(buf), 0);
#endif
    if (ret == -1) {
	perror("recv()");
	close(sock);
	return -1;
    }

    printf("client said [%s]\n", buf);
    close(peer);
    close(sock);
    
    return 0;
}

/// socket() -> connect() -> send() -> close()
static int do_client(void){

    int ret;
    int sock;
    char buf[128];
    struct sockaddr_un addr;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock < 0) {
	perror("socket()");
	return -1;
    }
    
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);
    
    if( connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1){
	perror("connect()");
	close(sock);
	return -1;
    };

    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "This is msg from sock_stream");
#if 0
    ret = send(sock, buf, sizeof(buf), 0);
#else
    // buf send leftovers
    // Sends the rest sequentially even when partial writes occur
    ret = stream_send(sock, buf, sizeof(buf), 0);
#endif
    if (ret == -1) {
	perror("send()");
	close(sock);
	return -1;
    }

    close(sock);
    return 0;
}

int main (int argc, char *argv[]){

    int ret;

    if(argc < 2){
	print_usage(argv[0]);
	return -1;
    } 

    if(!strcmp(argv[1], "server")){
	ret = do_server();
    } else if(!strcmp(argv[1], "client")) {
	ret = do_client();
    } else {
	print_usage(argv[0]);
	return -1;
    }

    return ret;
}
