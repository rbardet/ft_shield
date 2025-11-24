#include "ft_shield.h"

bool existing_lock() {
	if (access(LOCK_FILE, F_OK) == 0) {
		dprintf(STDERR_FILENO, EXISTING_LOCK);
		return (true);
	}
	
	return (false);
}

void create_lock() {
	FILE *file = fopen(LOCK_FILE, "w");
	flock(file->_fileno, LOCK_EX);
	fclose(file);
}

void delete_lock() {
	unlink(LOCK_FILE);
}
