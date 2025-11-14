#include "ft_shield.h"

FILE *logFile;

void create_log() {
	logFile = fopen(LOG_FILE, "w+");
}

void log_event(char *log) {
	write(logFile->_fileno, log, sizeof(log));
}