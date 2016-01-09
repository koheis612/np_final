#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLEN 256
#define PORT 3333

void print_description(void) {
    puts("1. rock\n2. paper\n3. scissors");
    printf("> ");
}

void print_score(int win, int lose, int draw) {
    printf("win: %d, lose: %d, draw: %d\n", win, lose, draw);
}

int main(int argc, char const* argv[]) {
    int sockfd;
    char sendline[MAXLEN], recvline[MAXLEN];
    struct sockaddr_in servaddr;
    static int win, lose, draw = 0;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <IP address of the server>\n", argv[0]);
        exit(1);
    }

    // create a socket for the client
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("creating socket");
        exit(2);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);
    servaddr.sin_port = htons(PORT);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connecting to the server");
        exit(3);
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
}
