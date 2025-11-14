#include "ft_shield.h"

int userNb = 0;

static int init_socket() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		return (-1);
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		return (-1);
	}

	if (listen(sockfd, MAX_USER) < 0) {
		return (-1);
	}
	
	return (sockfd);
}

static EPOLL_STRUCT init_epoll(int sockfd) {
	EPOLL_STRUCT epoll;

	epoll.fd = epoll_create1(0);
	if (epoll.fd < 0) {
		return (EPOLL_ERROR);
	}

	epoll.event.events = EPOLLIN;
	epoll.event.data.fd = sockfd;
	if (epoll_ctl(epoll.fd, EPOLL_CTL_ADD, sockfd, &epoll.event) < 0) {
		return (EPOLL_ERROR);
	}

	return (epoll);
}

void run_server() {
	int sockfd = init_socket();
	if (sockfd < 0) {
		return ;
	}

	EPOLL_STRUCT epoll = init_epoll(sockfd);
	if (epoll.fd < 0) {
		return;
	}

	// while (1) {
	// 	int eventNb = epoll_wait(epoll.fd, epoll.events, MAX_EVENT, -1);
	// 	if (eventNb == -1) {
	// 		continue ;
	// 	}

	// 	for (int i = 0; i < eventNb; i++) {
	// 		if (epoll.events[i].data.fd == sockfd && userNb < MAX_USER) {
	// 			accept_user(sockfd, epoll);
	// 		} else {
	// 			refuse_user(sockfd);
	// 		}

	// 		if (epoll.events->data.fd != sockfd) {
	// 			read_input(epoll.events[i].data.fd);
	// 		}
	// 	}
	// }
}