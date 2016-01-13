#ifndef _INCLUDE_SERVER_H
#define _INCLUDE_SERVER_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <netdb.h>

#define MAXLEN 256
#define PORT "3333"

int get_random(void);
int listen_tcp(const char *);
void judge(char *, char *, int);

#endif
