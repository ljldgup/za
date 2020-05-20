#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include "common.h"

int main(int argc, char** argv)
{
	int    sockfd, n;
	char    recvline[4096], sendline[4096];
	struct sockaddr_in    servaddr;

	char host[128];
	u_short	port;
	
	memset(&servaddr, 0, sizeof(servaddr));
	printf("argc %d \n", argc);

	if( argc > 3){
		printf("usage: ./client host port\n");
		exit(0);
	}

	if(argc > 1) strcpy(host, argv[1]);
	else{
		strcpy(host, SERV_HOST);
		port = SERV_PORT;
	}


	if(argc > 2){
		if((port = atoi(argv[2])) < 0){
			printf("port not right\n");
			exit(0);
		}
	}


	if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
		exit(0);
	}
	printf("sockfd %d\n", sockfd);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);

	if( inet_pton(AF_INET, host, &servaddr.sin_addr) <= 0){
		printf("inet_pton error for %s\n", host);
		exit(0);
	}
	
	if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
		printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
	}

	printf("send msg to server: \n");
	while(1){

		fgets(sendline, 4096, stdin);
		//fgets 会自动追加换行
		if(strcmp(sendline, "0\n") == 0 ){
			close(sockfd);
			break;
		}

		if( send(sockfd, sendline, strlen(sendline), 0) < 0)
		{
			printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);
			exit(0);
		}
	}
}
