#include "ft_shield.h"

char password[PASS_SIZE];

bool set_password() {
	int fd = open(PASS_FILE, O_RDONLY);
	if (fd < 0) {
		return (false);
	}

	int len = read(fd, password, sizeof(password));
	if (len <= 0) {
		close(fd);
		return (false);
	}

	password[len] = '\0';
	close(fd);
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
	if (strcmp(buff, password) != 0) {
		return (false);
	}

	return (true);
}