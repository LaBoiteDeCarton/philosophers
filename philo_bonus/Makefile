NAME = philo_bonus
SRCS = ${wildcard *.c}
OBJS = ${SRCS:.c=.o}
FLAGS = -Wall -Wextra -Werror

.c.o:
	gcc ${FLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	gcc ${FLAGS} ${LIBFLAGS} ${OBJS}  -lpthread -o ${NAME}

all: ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean ${NAME}

.PHONY: all, clean, fclean, re, bonus