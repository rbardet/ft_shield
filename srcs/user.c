#include "ft_shield.h"

void accept_user(int sockfd, EPOLL_STRUCT epoll) {
	int userfd = accept(sockfd, NULL, NULL);
	if (userfd < 0) {
		return ;
	}

	if (epoll_ctl(epoll.fd, EPOLL_CTL_ADD, userfd, &epoll.event) < 0) {
		log_event(LOG_EPOLL_FAILED);
		write(userfd, FAILED_CONNECTION, sizeof(FAILED_CONNECTION));
		close(userfd);
		return ;
	}

	userNb++;
	log_event(LOG_NEW_USER);
}

void refuse_user(int sockfd) {
	int userfd = accept(sockfd, NULL, NULL);
	if (userfd < 0) {
		return ;
	}

	log_event(LOG_LIMIT_REACH);
	write(userfd, LIMIT_REACH, sizeof(LIMIT_REACH));
	close(userfd);
}

void disconnect_user(int userfd, EPOLL_STRUCT epoll) {
	close(userfd);
	epoll_ctl(epoll.fd, EPOLL_CTL_DEL, userfd, &epoll.event);
	userNb--;
	log_event(LOG_DISCONNECT_USER);
}

void read_input(int userfd, EPOLL_STRUCT epoll) {
	char buffer[BUFFER_SIZE];
	int len = read(userfd, buffer, sizeof(buffer));
	if (len == 0) {
		disconnect_user(userfd, epoll);
		return ;
	} else if (len < 0) {
		return ;
	}

	log_event(buffer);
}