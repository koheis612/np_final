#ifndef _INCLUDE_CLIENT_H
#define _INCLUDE_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAXLEN 256
#define PORT "3333"

void print_description(void);
void print_score(int, int, int);
int connect_to_server(const char *, const char*);

#endif
