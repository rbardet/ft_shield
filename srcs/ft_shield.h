#ifndef FT_SHIELD_H
#define FT_SHIELD_H

#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/file.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#define LOCK_FILE "/var/lock/ft_shield.lock"
#define LOGIN "rbardet-"
#define PORT 4242
#define MAX_CLIENT 3
#define MAX_EVENT 10

typedef struct {
	int fd;
	struct epoll_event *event;
} EPOLL_STRUCT;

#define EPOLL_ERROR ((EPOLL_STRUCT){.fd = -1})

bool existing_lock();
void create_lock();
void delete_lock();

void run_server();

#endif