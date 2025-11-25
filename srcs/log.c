#include "ft_shield.h"

int flog;

void create_log() {
	flog = open(LOG_FILE, O_RDWR | O_CREAT | O_APPEND);
}

void close_log() {
	close(flog);
}

void remove_nl(const char *buff) {
	char *i = strchr(buff, '\n');
	if (i) {
		*i = 0;
	}
}

void log_event(char *log, LOG_TYPE __TYPE__) {
	if (__TYPE__ == LOG_INPUT) {
		write(flog, LOG_USER_INPUT, strlen(LOG_USER_INPUT));
		write(flog, log, strlen(log));
	} else {
		write(flog, log, strlen(log));
	}
}