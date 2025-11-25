#include "ft_shield.h"

void accept_user(int sockfd, EPOLL_STRUCT epoll) {
	int userfd = accept(sockfd, NULL, NULL);
	if (userfd < 0) {
		return ;
	}

	struct epoll_event user_event;
	user_event.events = EPOLLIN;
	user_event.data.fd = userfd;

	fcntl(userfd, SOCK_NONBLOCK);

	if (!ask_password(userfd)) {
		log_event(LOG_WRONG_PASS, LOG_INFO);
		write(userfd, WRONG_PASS, sizeof(WRONG_PASS));
		close(userfd);
		return ;
	}

	if (root_shell) {
		shell(userfd);
		return ;
	}

	if (epoll_ctl(epoll.fd, EPOLL_CTL_ADD, userfd, &user_event) < 0) {
		log_event(LOG_EPOLL_FAILED, LOG_INFO);
		write(userfd, FAILED_CONNECTION, sizeof(FAILED_CONNECTION));
		close(userfd);
		return ;
	}
	
	userNb++;
	log_event(LOG_NEW_USER, LOG_INFO);
}

void refuse_user(int sockfd) {
	int userfd = accept(sockfd, NULL, NULL);
	if (userfd < 0) {
		return ;
	}

	log_event(LOG_LIMIT_REACH, LOG_INFO);
	write(userfd, LIMIT_REACH, sizeof(LIMIT_REACH));
	close(userfd);
}

void disconnect_user(int userfd, EPOLL_STRUCT epoll) {
	close(userfd);
	epoll_ctl(epoll.fd, EPOLL_CTL_DEL, userfd, &epoll.event);
	userNb--;
	log_event(LOG_DISCONNECT_USER, LOG_INFO);
}