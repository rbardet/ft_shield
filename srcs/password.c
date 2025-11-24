#include "ft_shield.h"

char pass[BUFFER_SIZE];

bool set_password() {
	int fd = open(PASS_FILE, O_RDONLY);
	if (fd < 0) {
		write(STDOUT_FILENO, UNDEFINED_PASSWORD, strlen(UNDEFINED_PASSWORD));
		return (false);
	}

	int bytes = read(fd, pass, BUFFER_SIZE);
	if (bytes <= 0) {
		write(STDOUT_FILENO, UNDEFINED_PASSWORD, strlen(UNDEFINED_PASSWORD));
		return (false);
	}

	pass[bytes] = '\0';
	return (true);
}

bool ask_password(int userfd) {
	write(userfd, ASK_PASS, sizeof(ASK_PASS));
	char buff[BUFFER_SIZE];

	int len = read(userfd, buff, sizeof(buff));
	if (len <= 0) {
		return (false);
	}

	buff[len] = '\0';
	if (strcmp(buff, pass) != 0) {
		return (false);
	}

	return (true);
}