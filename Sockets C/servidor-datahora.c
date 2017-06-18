#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define LISTENQ 1024 /* segundo argumento de listen() */
#define MAXLINE 4096 /* comprimento de linha de texto máx. */

int main() {

    int listenfd;
    int connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    printf("Servidor data hora rodando!\n");

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
		perror("Error Socket\n");
		exit(1);
	}

    // Inicializar a struct e seus membros zerados
    bzero(&servaddr, sizeof(servaddr));
    // Atribuir novos dados na struct
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(13);

    //bind(sockfd, (struct sockaddr *)&meu_end, sizeof(struct sockaddr));
    //int bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
    if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(struct sockaddr)) < 0) {
        perror("Error bind\n");
        exit(1);
    }

    if (listen(listenfd, LISTENQ) < 0 ) {
        perror("Error listen\n");
        exit(1);
    }

    // Loop infinito
    for ( ; ; ) {

        //int accept (int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);

        //snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        snprintf(buff, sizeof(buff), "%.24s - Servidor rodando\r\n", ctime(&ticks));

        write(connfd, buff, strlen(buff));

        close(connfd);

    }

    return 0;
}
