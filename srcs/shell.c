#include "ft_shield.h"

static void handle_input(char *buffer, int userfd) {
	remove_nl(buffer);

	write(userfd, buffer, sizeof(buffer));
	if (strcmp(buffer, CMD_HELP) == 0) {
		write(userfd, HELP_MSG, strlen(HELP_MSG));
	} else if (strcmp(buffer, CMD_SHELL) == 0) {
		write(userfd, SHELL_MSG, strlen(SHELL_MSG));
	}
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