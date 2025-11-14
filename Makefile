NAME = ft_shield

CC = cc
CFLAGS = -Wall -Werror -Wextra

SOURCES = srcs/ft_shield.c
srcs/lock.c

OBJECTS = ${SOURCES:.c=.o}

all: ${NAME}

${NAME}: ${OBJECTS}
	${CC} ${CFLAGS} -o ${OBJECTS} 

clean:
	rm -f ${OBJECTS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY all clean fclean re