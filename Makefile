NAME = ft_shield

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

SOURCES = srcs/ft_shield.c \
	srcs/lock.c \
	srcs/socket.c \
	srcs/user.c \
	srcs/log.c \
	srcs/password.c \
	srcs/shell.c \
	srcs/systemd.c
	
OBJECTS = ${SOURCES:.c=.o}

all: ${NAME}

${NAME}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}

clean:
	rm -f ${OBJECTS} ${PASSWORD_FILE}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re