#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <strings.h>

#include "common.h"

typedef struct sockaddr SA;

int main(void)
{
    int                 listenfd, connfd;
    struct sockaddr_in  cliaddr, servaddr;
    socklen_t           clientlen;


    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_quit("socket error");
    }

#ifdef DEBUG
	printf("listenfd %d \n", listenfd);
#endif
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family         =   AF_INET;
    servaddr.sin_port           =   htons(SERV_PORT);
    servaddr.sin_addr.s_addr    =   htonl(INADDR_ANY);

    if (bind(listenfd, (SA *)&servaddr, sizeof(servaddr)) < 0) {
        err_quit("bind error");
    }

#ifdef DEBUG
	printf("bind success\n");
#endif
    if (listen(listenfd, 5) < 0) {
        err_quit("listen error");
    }


    fd_set rfds, allfd;
    int maxfd, maxi = -1;

//method one:
    //int maxfd;
    //if ((maxfd = sysconf(_SC_OPEN_MAX)) < 0) {
    //  err_sys("sysconf error");
    //} 
    //
    //int clinet[maxfd];
//-----------------------------------------------------

//method two:
//在sys/select.h中定义了一个FD_SETSIZE其表示fd_set描述符总数。
    int client[FD_SETSIZE];
//-----------------------------------------------------

    int nready;
    int i, nread;
    int sockfd;
    char buf[MAXLINE];

    FD_ZERO(&allfd);
    FD_SET(listenfd, &allfd);
    maxfd = listenfd;

    for (i=0; i<FD_SETSIZE; ++i) {
        client[i] = -1;
    }


    for ( ; ; ) {

        rfds = allfd;

        nready = select(maxfd+1, &rfds, NULL, NULL, NULL);
        if (nready < 0) {
            err_quit("select error");
        }

        if (FD_ISSET(listenfd, &rfds)) {
//编译的时候加-DDEBUG
#ifdef DEBUG
    printf("have descriptor....\n");
#endif

            clientlen = sizeof(cliaddr);
            connfd = accept(listenfd, (SA *)&cliaddr, &clientlen);
            if (connfd < 0) {
                err_quit("accept error");
            }

            for (i=0; i<FD_SETSIZE; ++i) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    break;
                }
            }

            if (i == FD_SETSIZE) {
                err_quit("too many clients");
            }

            FD_SET(connfd, &allfd);

            if (connfd > maxfd) {
                maxfd = connfd;
            }

            if (i > maxi) {
                maxi = i;
            }

            if (--nready <= 0) {
                continue;
            }
        }

        for (i=0; i<=maxi; ++i) {
            if ((sockfd = client[i]) < 0) {
                continue;
            }

            if (FD_ISSET(sockfd, &rfds)) {

#ifdef  DEBUG
    printf("fd: %d\n", sockfd);
#endif

                if ((nread = read(sockfd, buf, MAXLINE)) == 0) {
                    close(sockfd);
                    FD_CLR(sockfd, &allfd);
                    client[i] = -1;
                } else {
					buf[nread] = '\0';
					printf("recived:\n %s\n", buf);
                    if (write(sockfd, buf, nread) != nread) {
                        err_msg("fail to write...");
                    }
                }

                if (--nready <= 0) {
                    continue;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}
