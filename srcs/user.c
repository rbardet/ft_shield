#include "ft_shield.h"

void accept_user(int sockfd, EPOLL_STRUCT epoll) {
	int userfd = accept(sockfd, NULL, NULL);
	if (userfd < 0) {
		return ;
	}

	if (epoll_ctl(epoll.fd, EPOLL_CTL_ADD, sockfd, &epoll.event) < 0) {
		write(userfd, FAILED_CONNECTION, sizeof(FAILED_CONNECTION));
		close(userfd);
		return ;
	}

	userNb++;
}

void refuse_user(int sockfd) {
	int userfd = accept(sockfd, NULL, NULL);
	if (userfd < 0) {
		return ;
	}

	write(userfd, LIMIT_REACH, sizeof(LIMIT_REACH));
	close(userfd);
}

void disconnect_user(int userfd) {
	close(userfd);
	userNb--;
}

void read_input(int userfd) {
	(void)userfd;
}