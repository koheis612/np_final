#include "client.h"

void print_description(void) {
    puts("1. rock\n2. paper\n3. scissors");
    printf("> ");
}

void print_score(int win, int lose, int draw) {
    printf("win: %d, lose: %d, draw: %d\n", win, lose, draw);
}

int connect_to_server(const char *hostname, const char *service) {
    int sockfd, err;
    struct addrinfo hints, *res, *ai;
    res = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // ipv4/ipv6 dual stack
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    err = getaddrinfo(hostname, service, &hints, &res);
    if (err != 0) {
        printf("getaddrinfo(): %s\n", gai_strerror(err));
        return -1;
    }

    for (ai = res; ai; ai = ai->ai_next) {
        sockfd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if (sockfd < 0) {
            return -1;
        }
        if (connect(sockfd, ai->ai_addr, ai->ai_addrlen) < 0) {
            close(sockfd);
            sockfd = -1;
            continue;
        } else {
            break;
        }
    }

    freeaddrinfo(res);
    return sockfd;
}

int main(int argc, char const* argv[])
{
    int sockfd;
    static int win, lose, draw = 0;
    char sendline[MAXLEN], recvline[MAXLEN];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <ip address of the server>\n", argv[0]);
        exit(1);
    }

    if ((sockfd = connect_to_server(argv[1], PORT)) < 0) {
        perror("creating socket");
        exit(2);
    }

    for (;;) {
        print_description();
        fgets(sendline, sizeof(sendline), stdin);

        // chomp
        sendline[strlen(sendline) - 1] = '\0';

        if (strcmp(sendline, "exit") == 0 || strcmp(sendline, "quit") == 0) {
            break;
        }
        send(sockfd, sendline, sizeof(sendline), 0);

        if (recv(sockfd, recvline, sizeof(recvline), 0) == 0) {
            perror("recv");
            exit(4);
        }

        printf("String received from server: ");
        printf("%s\n", recvline);

        if (strcmp(recvline, "win") == 0) {
            win++;
        } else if (strcmp(recvline, "lose") == 0) {
            lose++;
        } else if (strcmp(recvline, "draw") == 0) {
            draw++;
        }
        print_score(win, lose, draw);
    }
    return 0;
    return 0;
}
