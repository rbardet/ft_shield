#include "ft_shield.h"

int main(void) {

	if (existing_lock()) {
		return (EXIT_FAILURE);
	}

	create_lock();
	return(EXIT_SUCCESS);
}