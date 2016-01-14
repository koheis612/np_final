#include "server.h"

int get_random(void) {
    srand((unsigned int)time(NULL));
    return rand();
}

void judge(char *result, char *buf, int enemy) {
    /*
     * 1. rock
     * 2. paper
     * 3. scissors
     */
    int self = atoi(buf);
    
    printf("buf:%d, enemy:%d\n", atoi(buf), enemy);

    if (self == 1) {
        // rock
        switch (enemy) {
            case 1:
                strcpy(result, "draw");
                break;
            case 2:
                strcpy(result, "lose");
                break;
            case 3:
                strcpy(result, "win");
                break;
        }
    } else if (self == 2) {
        // paper
        switch (enemy) {
            case 1:
                strcpy(result, "win");
                break;
            case 2:
                strcpy(result, "draw");
                break;
            case 3:
                strcpy(result, "lose");
                break;
        }
    } else if (self == 3) {
        // scissors
        switch (enemy) {
            case 1:
                strcpy(result, "lose");
                break;
            case 2:
                strcpy(result, "win");
                break;
            case 3:
                strcpy(result, "draw");
                break;
        }
    } else {
        strcpy(result, "bad");
    }
}

int listen_tcp(const char *service) {
    int sockfd, err;
    struct addrinfo hints, *res, *ai;
    res = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    err = getaddrinfo(NULL, service, &hints, &res);

    if (err != 0) {
        fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(err));
        return -1;
    }

    ai = res;
    sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);

    if (sockfd < 0) {
        return -1;
    }

    if (bind(sockfd, ai->ai_addr, ai->ai_addrlen) < 0) {
        perror("bind");
        return -1;
    }

    if (listen(sockfd, 5) < 0) {
        perror("listen");
        return -1;
    }

    freeaddrinfo(res);
    return sockfd;
}

int main(int argc, char const* argv[]) {
    int listenfd, connfd, n;
    char buf[MAXLEN], result[MAXLEN];
    struct sockaddr_storage cliaddr;
    socklen_t clilen = sizeof(cliaddr);

    listenfd = listen_tcp(PORT);
    
    if (listenfd < 0) {
        perror("server");
    }

    printf("server running.\n");

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
