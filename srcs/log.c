#include "ft_shield.h"

FILE *logFile;

void create_log() {
	logFile = fopen(LOG_FILE, "w+");
}

void close_log() {
	fclose(logFile);
}

void remove_nl(const char *buff) {
	char *i = strchr(buff, '\n');
	if (i) {
		i = 0;
	}
}

void log_event(char *log, LOG_TYPE __TYPE__) {
	if (__TYPE__ == LOG_INPUT) {
		remove_nl(log);
		write(logFile->_fileno, LOG_USER_INPUT, strlen(LOG_USER_INPUT));
		write(logFile->_fileno, log, strlen(log));
	} else {
		write(logFile->_fileno, log, strlen(log));
	}
}