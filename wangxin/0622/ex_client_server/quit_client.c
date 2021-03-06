#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

enum{MSG_STR = 1, MSG_QUIT};

typedef struct msg_tag
{
    int type;
    int len;
}msg_t;

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("use ./client ip port\n");
	return 0;
    }

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    
    if(sockfd < 0)
    {
        perror(strerror(errno));
	close(sockfd);
	return 0;
    }
    
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    server.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(sockfd, (struct sockaddr*)&server, sizeof(server));
    if(ret < 0)
    {
        perror(strerror(errno));
	close(sockfd);
	return 0;
    }

    msg_t msg = {0};
    msg.type = MSG_QUIT;
    msg.len = 0;

    int num = write(sockfd, &msg, sizeof(msg));
    
    if(num != sizeof(msg))
    {
        perror(strerror(errno));
	close(sockfd);
	return 0;
    }
    
    printf("quit success!\n");
    
    close(sockfd);
    
    return 0;
}
