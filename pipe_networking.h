#ifndef PIPE_NETWORKING
#define PIPE_NETWORKING

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MESSAGE_BUFFER_SIZE 200

int server_handshake(int *c);

int client_handshake(int *s);

#endif
