#include "ft_shield.h"

static void init_daemon() {
	return ;
}

int main(void) {

	if (existing_lock()) {
		printf("EXISTING LOCK CANT START\n");
		return (EXIT_FAILURE);
	}

	create_lock();
	init_daemon();
	run_server();
	printf(LOGIN);
	return(EXIT_SUCCESS);
}