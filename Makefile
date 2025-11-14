NAME = ft_shield

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

PASSWORD_FILE = .password

SOURCES = srcs/ft_shield.c \
	srcs/lock.c \
	srcs/socket.c \
	srcs/user.c \
	srcs/log.c

OBJECTS = ${SOURCES:.c=.o}

all: ${NAME}

${NAME}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}
	@read -p "Enter a password " password; \
	echo $$password > ${PASSWORD_FILE};

clean:
	rm -f ${OBJECTS} ${PASSWORD_FILE}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re