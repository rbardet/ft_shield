#include "ft_shield.h"

char *pass;

bool password_set() {
	pass = getenv("PASSWORD");
	if (!pass) {
		dprintf(STDERR_FILENO, UNDEFINED_PASSWORD);
		return (false);
	} else {
		return (true);
	}
}

bool ask_password(int userfd) {
	write(userfd, ASK_PASS, sizeof(ASK_PASS));
	char buff[BUFFER_SIZE];

	int len = read(userfd, buff, sizeof(buff));
	if (len <= 0) {
		return (false);
	}

	buff[len] = '\0';
	remove_nl(buff);
	if (strcmp(buff, pass) != 0) {
		return (false);
	}

	return (true);
}