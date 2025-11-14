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
#define LOG_FILE "/var/log/ft_shield.log"
#define LOGIN "rbardet-"
#define PORT 4242
#define MAX_USER 3
#define MAX_EVENT 10
#define LIMIT_REACH "Too many user connected, retry later"
#define FAILED_CONNECTION "Failed to connect"
#define BUFFER_SIZE 256

#define LOG_LIMIT_REACH "[ERROR]: connection failed (reason: limit reached)\n"
#define LOG_EPOLL_FAILED "[ERROR]: connection failed (reason: failed to add to epoll)\n"
#define LOG_DISCONNECT_USER "[INFO]: user disconnected\n"
#define LOG_NEW_USER "[INFO]: new user connected\n"

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
void read_input(int userfd, EPOLL_STRUCT epoll);

void create_log();
void log_event(char *log);
void log_input(char *buffer, int userfd);

#endif