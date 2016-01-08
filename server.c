#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAXLEN 4096
#define PORT 3333

int get_random(void) {
    srand((unsigned int)time(NULL));
    return rand() % 3 + 1;
}

void judge(char *result, char *buf, int enemy) {
    printf("buf:%d, enemy:%d\n", atoi(buf), enemy);
    if (atoi(buf) > 0 && atoi(buf) < 4) {
        if (atoi(buf) - enemy == 0) {
            strcpy(result, "draw");
        } else if (atoi(buf) - enemy == 1) {   
            strcpy(result, "lose");
        } else {
            strcpy(result, "win");
        }
    } else {
        strcpy(result, "bad");
    }
}

int main(int argc, char const* argv[]) {
    int listenfd, connfd, n;
    socklen_t clilen;
    char buf[MAXLEN], result[MAXLEN], score[MAXLEN];
    struct sockaddr_in cliaddr, servaddr;

    // create socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 5);

    printf("server running.\n");

    // accepting messages
    for (;;) {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        printf("received request\n");

        while ((n = recv(connfd, buf, sizeof(buf), 0)) > 0) {
            printf("String received from and resent to the client: ");
            printf("%s\n", buf);

            judge(result, buf, get_random());

            send(connfd, result, n, 0);
        }

        if (n < 0) {
            perror("Read error");
            exit(1);
        }
        close(connfd);
    }
    close(listenfd);
    return 0;
}
